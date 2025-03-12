#include "pipex.h"

int ft_param_size(char *argv[])
{
	int	size;

	size = 0;
	while (argv[size])
		size++;
	return (size);
}

void	ft_files_check(char *argv[], int cmds)
{
	int	fd;
	int	i;
	int x;

	i = 0;
	x = 1;
	while (i < 2)
	{
		fd = open(argv[x], O_RDONLY);
		if (fd != -1)
			close(fd);
		else
		{
			fd = open(argv[x], O_CREAT | O_WRONLY, 0644);
			if (fd != -1)
				close(fd);
			else
				perror("Error creating the file");
		}
		i++;
		x = ft_param_size(argv) - 1;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int 	cmds;
	char	**paths;
	t_pipex	pipex;
	int here_doc;

	here_doc = 0;
	cmds = ft_param_size(argv) - 3;
	if (cmds < 2)
	{
		ft_printf("You need at least 2 commands");
		exit(0);
	}
	paths = ft_split(ft_get_path(envp), ':');
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		here_doc = 1;
		cmds = cmds - 1;
	}
	pipex = ft_init_pipex(argv, envp, cmds, paths, here_doc);
	// ft_files_check(argv, cmds);
	ft_create_proc(pipex, argc);
	ft_free_array(pipex.paths);
	ft_free_pipes(pipex.pipes, pipex.cmds);
	return (0);
}
 