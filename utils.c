/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:54:56 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/02/24 15:54:58 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *ft_get_path(char *envp[])
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	ft_printf("PATH VARIABLE NOT FOUND\n");
	exit(6);
}

void	ft_exec_command(int index, t_pipex pipex)
{
	char	full_path[1024];
	char	**cmds;
	int 	i;

	i = 0;
	cmds = ft_split(pipex.arg[index + 2 + pipex.here_doc], ' ');
	while(pipex.paths[i])
	{
		ft_strlcpy(full_path, pipex.paths[i], sizeof(full_path));
		ft_strlcat(full_path, "/", sizeof(full_path));
		ft_strlcat(full_path, cmds[0], sizeof(full_path));
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, cmds, pipex.env);
			perror("exec failed");
			exit(2);
		}
		i++;
	}
	ft_printf("Cant execute %s", full_path);
	exit(1);
}

void	ft_wait(int *pids, t_pipex pipex)
{
	int		i;
	int		status;
	pid_t	child_id;

	i = 0;
	while (i < pipex.cmds)
	{
		child_id = waitpid(pids[i], &status, 0);
		if (child_id == -1)
			perror("waitpid failed");
		else
			if (WIFEXITED(status))  // Child exited normally
				ft_printf("Child %d exited with status %d\n", pids[i], WEXITSTATUS(status));
			else if (WIFSIGNALED(status))  // Child was terminated by a signal
				ft_printf("Child %d was killed by signal %d\n", pids[i], WTERMSIG(status));
			else if (WIFSTOPPED(status))  // Child was stopped (not common in simple cases)
				ft_printf("Child %d was stopped by signal %d\n", pids[i], WSTOPSIG(status));
		i++;
	}
}

t_pipex	ft_init_pipex(char **argv, char **envp, int cmds, char **paths, int here_doc)
{
	t_pipex	pipex;

	pipex.arg = argv;
	pipex.env = envp;
	pipex.cmds = cmds;
	pipex.paths = paths;
	pipex.pipes = ft_create_pipes(cmds);
	pipex.here_doc = here_doc;
	return (pipex);
}

int	ft_handle_heredoc(char *delimiter)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("Error creating herdoc pipe");
		exit(1);
	}
	while (1)
	{
		write(1, "pipe here doc> ", 14);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
