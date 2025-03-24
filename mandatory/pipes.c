/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaovieira <joaovieira@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:28:55 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/03/15 11:33:55 by joaovieira       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**ft_create_pipes(int cmds)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * (cmds - 1));
	if (pipes == NULL)
		return (NULL);
	while (i < cmds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
		{
			ft_free_pipes(pipes, cmds);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			ft_free_pipes(pipes, cmds);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	ft_close_pipes(int index, t_pipex pipex)
{
	int	pip;

	pip = 0;
	while (pip < pipex.cmds - 1)
	{
		if (pip + 1 != index)
			close(pipex.pipes[pip][0]);
		if (pip != index)
			close(pipex.pipes[pip][1]);
		pip++;
	}
}

void	ft_close_parent_pipes(t_pipex pipex)
{
	int	i;

	i = 0;
	while (i < pipex.cmds - 1)
	{
		close(pipex.pipes[i][1]);
		close(pipex.pipes[i][0]);
		i++;
	}
}
