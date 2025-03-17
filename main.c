/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaovieira <joaovieira@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:30:18 by joaovieira        #+#    #+#             */
/*   Updated: 2025/03/15 11:48:31 by joaovieira       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_wait(int *pids, t_pipex pipex)
{
	int		i;
	int		status;
	pid_t	child_id;

	i = 0;
	while (i < pipex.cmds)
	{
		child_id = waitpid(pids[i], &status, 0);
		if (child_id == -1)
			perror("waitpid failed");
		i++;
	}
}

int	ft_param_size(char *argv[])
{
	int	size;

	size = 0;
	while (argv[size])
		size++;
	return (size);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		cmds;
	t_pipex	pipex;
	int		here_doc;
	int		err;

	cmds = ft_param_size(argv);
	here_doc = ft_check_args(argv, cmds);
	cmds = cmds - 3 - here_doc;
	pipex = ft_init_pipex(argv, envp, cmds, here_doc);
	pipex.paths = ft_split(ft_get_path(envp, pipex), ':');
	err = ft_file_check(pipex, argc);
	err = err + ft_cmds_check(argc, pipex);
	if (err > 0)
		ft_free_all(pipex);
	ft_create_proc(pipex, argc);
	ft_free_array(pipex.paths);
	ft_free_pipes(pipex.pipes, pipex.cmds);
	return (0);
}
