/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaovieira <joaovieira@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:28:46 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/03/15 11:34:56 by joaovieira       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first_child(int index, t_pipex pipex)
{
	int		fd;

	if (pipex.here_doc == 1)
		fd = ft_handle_heredoc(pipex.arg[2]);
	else
	{
		fd = open(pipex.arg[1], O_RDONLY);
		if (fd == -1)
		{
			perror(pipex.arg[1]);
			exit(1);
		}
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipex.pipes[0][1], STDOUT_FILENO);
	close(pipex.pipes[0][1]);
	ft_exec_command(index, pipex);
}

void	ft_middle_childs(int index, t_pipex pipex)
{
	dup2(pipex.pipes[index - 1][0], STDIN_FILENO);
	dup2(pipex.pipes[index][1], STDOUT_FILENO);
	close(pipex.pipes[index - 1][0]);
	close(pipex.pipes[index][1]);
	ft_exec_command(index, pipex);
}

void	ft_last_child(int index, t_pipex pipex, int argc)
{
	int		fd;

	if (pipex.here_doc == 1)
		fd = open(pipex.arg[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(pipex.arg[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(pipex.arg[argc - 1]);
		exit(3);
	}
	dup2(pipex.pipes[index - 1][0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pipex.pipes[index - 1][0]);
	close(fd);
	ft_exec_command(index, pipex);
}

void	ft_handle_childs(int index, t_pipex pipex, int argc)
{
	if (pipex.cmds == 1)
		ft_here_doc_special(pipex, argc);
	if (index == 0)
		ft_first_child(index, pipex);
	else if (index == ft_param_size(pipex.arg) - 4 - pipex.here_doc)
		ft_last_child(index, pipex, argc);
	else
		ft_middle_childs(index, pipex);
}

void	ft_create_proc(t_pipex	pipex, int argc)
{
	int	*pids;
	int	i;

	i = 0;
	pids = malloc(sizeof(int) * (pipex.cmds));
	if (pids == NULL)
		exit(1);
	while (i < pipex.cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			free(pids);
			exit(1);
		}
		if (pids[i] == 0)
		{
			ft_close_pipes(i, pipex);
			ft_handle_childs(i, pipex, argc);
		}
		i++;
	}
	ft_close_parent_pipes(pipex);
	ft_wait(pids, pipex);
	free(pids);
}
