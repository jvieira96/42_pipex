/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:28:46 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/03/27 21:20:39 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
			close(pipex.pipes[0][1]);
			return ;
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
		close(pipex.pipes[index - 1][0]);
		return ;
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
	int	i;

	i = 0;
	pipex.pids = malloc(sizeof(int) * (pipex.cmds));
	if (pipex.pids == NULL)
		exit(1);
	while (i < pipex.cmds)
	{
		pipex.pids[i] = fork();
		if (pipex.pids[i] == -1)
		{
			free(pipex.pids);
			exit(1);
		}
		if (pipex.pids[i] == 0)
		{
			ft_close_pipes(i, pipex);
			ft_handle_childs(i, pipex, argc);
			ft_free_all(pipex);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
