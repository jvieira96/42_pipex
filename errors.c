/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:52:03 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/03/27 23:27:41 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
