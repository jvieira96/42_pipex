/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:30:18 by joaovieira        #+#    #+#             */
/*   Updated: 2025/03/28 13:25:03 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		ft_putstr_fd("you need at least 6 parameters in this fashion: \n", 2);
		ft_putstr_fd("./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
		exit(EXIT_FAILURE);
	}
	if (cmds < 5 && here_doc == 1)
	{
		ft_putstr_fd("you need at least 5 parameters in this fashion: \n", 2);
		ft_putstr_fd(" ./pipex here_doc LIMITER cmd file\n", 2);
		exit(EXIT_FAILURE);
	}
	return (here_doc);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		cmds;
	t_pipex	*pipex;
	int		here_doc;
	int		err;
	int		last_exit_status;

	cmds = ft_param_size(argv);
	here_doc = ft_check_args(argv, cmds);
	cmds = cmds - 3 - here_doc;
	pipex = ft_init_pipex(argv, envp, cmds, here_doc);
	pipex->paths = ft_split(ft_get_path(envp, pipex), ':');
	pipex = ft_create_proc(pipex, argc);
	ft_close_parent_pipes(pipex);
	last_exit_status = ft_wait(pipex);
	ft_free_all(pipex);
	exit(last_exit_status);
	return (0);
}
