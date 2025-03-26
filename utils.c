/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:36:06 by joaovieira        #+#    #+#             */
/*   Updated: 2025/03/26 19:04:01 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	exit(0);
}

void	ft_exec_command(int index, t_pipex pipex)
{
	char	full_path[1024];
	char	**cmds;
	int		i;

	i = 0;
	cmds = ft_split(pipex.arg[index + 2], ' ');
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

t_pipex	ft_init_pipex(char **argv, char **envp, int cmds)
{
	t_pipex	pipex;

	pipex.arg = argv;
	pipex.env = envp;
	pipex.cmds = cmds;
	pipex.paths = NULL;
	pipex.pipes = ft_create_pipes(cmds);
	return (pipex);
}
