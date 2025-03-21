/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaovieira <joaovieira@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:44:58 by joaovieira        #+#    #+#             */
/*   Updated: 2025/03/15 11:47:11 by joaovieira       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_args(char **argv, int cmds)
{
	int	here_doc;

	here_doc = 0;
	if (cmds > 1)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			here_doc = 1;
	}
	if (cmds < 5 && here_doc == 0)
	{
		ft_putstr_fd("you need at least 5 parameters in this fashion: \n", 2);
		ft_putstr_fd("./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
		exit(1);
	}
	if (cmds < 5 && here_doc == 1)
	{
		ft_putstr_fd("you need at least 5 parameters in this fashion: \n", 2);
		ft_putstr_fd(" ./pipex here_doc LIMITER cmd file\n", 2);
		exit(2);
	}
	return (here_doc);
}

int	ft_file_check(t_pipex pipex, int argc)
{
	int	fd;
	int	err;

	err = 0;
	if (pipex.here_doc != 1)
	{
		fd = open(pipex.arg[1], O_RDONLY);
		if (fd == -1)
		{
			perror(pipex.arg[1 + pipex.here_doc]);
			err++;
		}
		else
			close(fd);
	}
	fd = open(pipex.arg[argc - 1], O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(pipex.arg[argc - 1]);
		err++;
	}
	else
		close(fd);
	return (err);
}

int	ft_cmds_check(int argc, t_pipex pipex)
{
	int		i;
	char	**cmds;
	int		err;
	int		flag;

	err = 0;
	i = 2 + pipex.here_doc;
	while (i < argc - 1)
	{
		cmds = ft_split(pipex.arg[i], ' ');
		flag = ft_exec_check(pipex, cmds);
		if (!cmds[0])
		{
			ft_putstr_fd("command not found: \n", 2);
			err++;
		}
		else
			if (flag == 1)
				err++;
		ft_free_array(cmds);
		i++;
	}
	return (err);
}

int	ft_exec_check(t_pipex pipex, char **cmds)
{
	char	full_path[1024];
	int		i;

	i = 0;
	while (pipex.paths[i])
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
