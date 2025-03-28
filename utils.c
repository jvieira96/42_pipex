/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:52:38 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/03/28 16:02:39 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_get_path(char *envp[], t_pipex *pipex)
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
	exit(EXIT_FAILURE);
}

void	ft_exec_command(int index, t_pipex *pipex)
{
	char	full_path[1024];
	char	**cmds;
	int		i;

	i = 0;
	cmds = ft_split(pipex->arg[index + 2], ' ');
	if (!cmds || !cmds[0])
	{
		ft_comnmand_not_found(cmds);
		ft_free_cmds(cmds, pipex);
		exit (127);
	}
	while (pipex->paths[i])
	{
		ft_strlcpy(full_path, pipex->paths[i], sizeof(full_path));
		ft_strlcat(full_path, "/", sizeof(full_path));
		ft_strlcat(full_path, cmds[0], sizeof(full_path));
		if (access(full_path, X_OK) == 0)
			execve(full_path, cmds, pipex->env);
		i++;
	}
	ft_comnmand_not_found(cmds);
	ft_free_cmds(cmds, pipex);
	exit(127);
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

t_pipex	*ft_init_pipex(char **argv, char **envp, int cmds)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
	{
		perror("pipex malloc failed");
		exit(EXIT_FAILURE);
	}
	pipex->arg = argv;
	pipex->env = envp;
	pipex->cmds = cmds;
	pipex->paths = NULL;
	pipex->pipes = ft_create_pipes(cmds);
	pipex->pids = NULL;
	return (pipex);
}
