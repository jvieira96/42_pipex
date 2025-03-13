/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:50:12 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/03/11 14:50:14 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_array(char **array)
{
	int i;

	i = 0;
	if (array == NULL)
		return;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_pipes(int **pipes, int cmds)
{
	int i;

	i = 0;
	if (pipes == NULL)
		return;
	while (i < cmds - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	ft_file_check(t_pipex pipex, int argc)
{
	int	fd;
	int	ex;

	ex = 0;
	if (pipex.here_doc != 1)
	{
		fd = open(pipex.arg[1], O_RDONLY);
		if (fd == -1)
		{
			perror(pipex.arg[1 + pipex.here_doc]);
			ex++;
		}
		else
			close(fd);
	}
	fd = open(pipex.arg[argc - 1], O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		perror(pipex.arg[argc - 1]);
		ex++;
	}
	else
		close(fd);
	if (ex > 0)
		ft_free_all(pipex);
}

void	ft_cmds_check(int argc, t_pipex pipex)
{
	int		i;
	char	**cmds;
	int		inv;
	int		flag;

	flag = 0;
	inv = 0;
	i = 2 + pipex.here_doc;
	while (i < argc - 1)
	{
		cmds = ft_split(pipex.arg[i], ' ');
		if (!cmds[0])
		{
			ft_putstr_fd("command not found: \n", 2);
			inv++;
		}
		else
			if ((flag = ft_exec_check(pipex, cmds)) == 1)
				inv++;
		ft_free_array(cmds);
		i++;
	}
	if (inv > 0)
		ft_free_all(pipex);
}

int	ft_exec_check(t_pipex pipex, char **cmds)
{
	char	full_path[1024];
	int 	i;

	i = 0;
	while(pipex.paths[i])
	{
		ft_strlcpy(full_path, pipex.paths[i], sizeof(full_path));
		ft_strlcat(full_path, "/", sizeof(full_path));
		ft_strlcat(full_path, cmds[0], sizeof(full_path));
		if (access(full_path, X_OK) == 0)
			return (0);
		i++;
	}
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmds[0], 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void	ft_free_all(t_pipex pipex)
{
	ft_close_parent_pipes(pipex);
	ft_free_array(pipex.paths);
	ft_free_pipes(pipex.pipes, pipex.cmds);
	exit(1);
}