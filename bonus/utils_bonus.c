/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaovieira <joaovieira@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:36:06 by joaovieira        #+#    #+#             */
/*   Updated: 2025/03/15 11:37:48 by joaovieira       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_get_path(char *envp[], t_pipex pipex)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	ft_putstr_fd("Path variable not found", 2);
	ft_free_all(pipex);
	exit(1);
}

void	ft_exec_command(int index, t_pipex pipex)
{
	char	full_path[1024];
	char	**cmds;
	int		i;

	i = 0;
	cmds = ft_split(pipex.arg[index + 2 + pipex.here_doc], ' ');
	while (pipex.paths[i])
	{
		ft_strlcpy(full_path, pipex.paths[i], sizeof(full_path));
		ft_strlcat(full_path, "/", sizeof(full_path));
		ft_strlcat(full_path, cmds[0], sizeof(full_path));
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, cmds, pipex.env);
			break ;
		}
		i++;
	}
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmds[0], 2);
	ft_putstr_fd("\n", 2);
	ft_free_array(cmds);
	exit(127);
}

t_pipex	ft_init_pipex(char **argv, char **envp, int cmds, int here_doc)
{
	t_pipex	pipex;

	pipex.arg = argv;
	pipex.env = envp;
	pipex.cmds = cmds;
	pipex.paths = NULL;
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
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	ft_here_doc_special(t_pipex pipex, int argc)
{
	int	fd_input;
	int	fd_output;

	fd_input = ft_handle_heredoc(pipex.arg[2]);
	dup2(fd_input, STDIN_FILENO);
	close(fd_input);
	fd_output = open(pipex.arg[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_output == -1)
	{
		perror(pipex.arg[argc - 1]);
		exit(3);
	}
	dup2(fd_output, STDOUT_FILENO);
	close(fd_output);
	ft_exec_command(0, pipex);
}
