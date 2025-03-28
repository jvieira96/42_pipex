/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:50:12 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/03/28 16:03:10 by jpedro-f         ###   ########.fr       */
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

void	ft_free_all(t_pipex *pipex)
{
	free(pipex->pids);
	ft_free_array(pipex->paths);
	ft_free_pipes(pipex->pipes, pipex->cmds);
	free(pipex);
}

void	ft_comnmand_not_found(char **cmds)
{
	if (!cmds || !cmds[0])
	{
		ft_putstr_fd("command not found: \n", 2);
		return ;
	}
	ft_putstr_fd("command not found: \n", 2);
	ft_putstr_fd(cmds[0], 2);
	ft_putstr_fd("\n", 2);
}

void	ft_free_cmds(char **cmds, t_pipex *pipex)
{
	ft_free_array(cmds);
	ft_free_all(pipex);
}
