/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:28:46 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/03/11 14:28:48 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_first_child(int index, t_pipex pipex)
{
	int		fd;

	if (pipex.here_doc == 1)
		fd = ft_handle_heredoc(pipex.arg[2]);
	else
	{
		fd = open(pipex.arg[1], O_RDONLY);
		if (fd == -1)
		{
			perror("error opening the file");
			exit(1);
		}
	}
	dup2(fd, STDIN_FILENO);
	dup2(pipex.pipes[0][1], STDOUT_FILENO);	
	close(fd);
	close(pipex.pipes[0][1]);
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

void ft_last_child(int index, t_pipex pipex)
{
	int		fd;

	if (pipex.here_doc == 1)
		fd = open(pipex.arg[index + 3 + pipex.here_doc], O_APPEND);
	else
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

void	ft_handle_childs(int index, t_pipex pipex)
{
	if (index == 0)
		ft_first_child(index, pipex);
	else if (index == ft_param_size(pipex.arg) - 4)
		ft_last_child(index, pipex);
	else
		ft_middle_childs(index, pipex);
}

void	ft_create_proc(t_pipex	pipex)
{
	int	*pids;
	int i;

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
			ft_handle_childs(i, pipex);
			exit(1);
		}
		i++;
	}
	ft_close_parent_pipes(pipex);
	ft_wait(pids, pipex);
	free(pids);
}
