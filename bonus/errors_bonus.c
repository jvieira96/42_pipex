/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:50:12 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/03/27 21:41:45 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_pipes(int **pipes, int cmds)
{
	int	i;

	i = 0;
	if (pipes == NULL)
		return ;
	while (i < cmds - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	ft_free_all(t_pipex pipex)
{
	free(pipex.pids);
	ft_free_array(pipex.paths);
	ft_free_pipes(pipex.pipes, pipex.cmds);
}

void	ft_comnmand_not_found(char **cmds)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmds[0], 2);
	ft_putstr_fd("\n", 2);
}
