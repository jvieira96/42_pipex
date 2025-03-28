/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:51:31 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/03/28 12:43:41 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_wait(t_pipex *pipex)
{
	int		i;
	int		status;
	pid_t	child_id;
	int		last_status;

	last_status = 0;
	i = 0;
	while (i < pipex->cmds)
	{
		child_id = waitpid(pipex->pids[i], &status, 0);
		if (child_id == -1)
			perror("waitpid failed");
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	return (last_status);
}

int	ft_param_size(char *argv[])
{
	int	size;

	size = 0;
	while (argv[size])
		size++;
	return (size);
}

void	ft_check_args(int cmds)
{
	if (cmds != 5)
	{
		ft_putstr_fd("you need 5 parameters in this fashion: \n", 2);
		ft_putstr_fd("./pipex Infile cmd1 cmd2 Outfile\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		cmds;
	t_pipex	*pipex;
	int		err;
	int		last_exit_status;

	cmds = ft_param_size(argv);
	ft_check_args(cmds);
	cmds = cmds - 3;
	pipex = ft_init_pipex(argv, envp, cmds);
	pipex->paths = ft_split(ft_get_path(envp, pipex), ':');
	pipex = ft_create_proc(pipex, argc);
	ft_close_parent_pipes(pipex);
	last_exit_status = ft_wait(pipex);
	ft_free_all(pipex);
	exit(last_exit_status);
	return (0);
}
