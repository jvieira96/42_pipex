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

int ft_param_size(char *argv[])
{
	int	size;

	size = 0;
	while (argv[size])
		size++;
	return (size);
}

int	ft_check_args(char **argv, int cmds)
{
	int here_doc;

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
	if (cmds < 6 && here_doc == 1)
	{
		ft_putstr_fd("you need at least 6 parameters in this fashion: \n", 2);
		ft_putstr_fd(" ./pipex here_doc LIMITER cmd file\n", 2);
		exit(2);
	}
	return (here_doc);
}

int	main(int argc, char *argv[], char *envp[])
{
	int 	cmds;
	t_pipex	pipex;
	int 	here_doc;
	
	cmds = ft_param_size(argv);
	here_doc = ft_check_args(argv, cmds);
	cmds = cmds - 3 - here_doc;
	pipex = ft_init_pipex(argv, envp, cmds, here_doc);
	pipex.paths = ft_split(ft_get_path(envp, pipex), ':');
	ft_file_check(pipex, argc);
	ft_cmds_check(argc, pipex);
	ft_create_proc(pipex, argc);
	ft_free_array(pipex.paths);
	ft_free_pipes(pipex.pipes, pipex.cmds);
	return (0);
}
 