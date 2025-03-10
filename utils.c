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

void ft_first_child(int index, t_pipex pipex)
{
	int		fd;

	fd = open(pipex.arg[1], O_RDONLY);
	if (fd == -1)
	{
		perror("error opening the file");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	dup2(pipex.pipes[0][1], STDOUT_FILENO);	
	close(fd);
	close(pipex.pipes[0][1]);
	ft_exec_command(index, pipex);
}

void ft_last_child(int index, t_pipex pipex)
{
	int		fd;

	fd = open(pipex.arg[index + 3], O_WRONLY);
	if (fd == -1)
	{
		perror("error opening the file\n");
		exit(3);
	}
	dup2(pipex.pipes[index - 1][0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pipex.pipes[index - 1][0]);
	close(fd);
	ft_exec_command(index, pipex);
}

void ft_middle_childs(int index, t_pipex pipex)
{
	dup2(pipex.pipes[index - 1][0], STDIN_FILENO);
	dup2(pipex.pipes[index][1], STDOUT_FILENO);
	close(pipex.pipes[index - 1][0]);
	close(pipex.pipes[index][1]);
	ft_exec_command(index, pipex);
}

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
	cmds = ft_split(pipex.arg[index + 2], ' ');
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
	printf("Cant execute %s", full_path);
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
			printf("waited for child %d\n", pids[i]);

			if (WIFEXITED(status))  // Child exited normally
				printf("Child %d exited with status %d\n", pids[i], WEXITSTATUS(status));
			else if (WIFSIGNALED(status))  // Child was terminated by a signal
				printf("Child %d was killed by signal %d\n", pids[i], WTERMSIG(status));
			else if (WIFSTOPPED(status))  // Child was stopped (not common in simple cases)
				printf("Child %d was stopped by signal %d\n", pids[i], WSTOPSIG(status));
		i++;
	}
}

void ft_close_parent_pipes(t_pipex pipex)
{
	int i;

	i = 0;
	while (i < pipex.cmds - 1)
	{
		close(pipex.pipes[i][1]);
		close(pipex.pipes[i][0]);
		i++;
	}
}

t_pipex	ft_init_pipex(char **argv, char **envp, int cmds, char **paths)
{
	t_pipex	pipex;

	pipex.arg = argv;
	pipex.env = envp;
	pipex.cmds = cmds;
	pipex.paths = paths;
	pipex.pipes = ft_create_pipes(cmds);
	return (pipex);
}