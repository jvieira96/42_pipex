#include "pipex.h"

void	ft_close_pipes(int	index, int cmds, int **pipes)
{
	int	pip;

	pip = 0;
	while (pip < cmds - 1)
	{
		if (pip + 1 != index)
		{
			close(pipes[pip][0]);
			printf("pipe[%d][0] closed in process %d\n", pip, index);
		}
		if (pip != index)
		{
			close(pipes[pip][1]);
			printf("pipe[%d][1] closed in process %d\n", pip, index);
		}
		pip++;
	}
}

void	ft_handle_childs(int index, int **pipes, char **argv, char **paths)
{
	if (index == 0)
		ft_first_child(argv, pipes, index, paths);
	else if (index == ft_param_size(argv) - 4)
		ft_last_child(argv, pipes, index, paths);
	else
		ft_middle_childs(argv, pipes, index, paths);
}

int **ft_create_pipes(int cmds)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * cmds - 1);
	if (pipes == NULL)
		return (NULL);
	while (i < cmds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
		{
			// ft_free_pinters_array(pipes);
			return NULL;
		}
		if(pipe(pipes[i]) == -1)
		{
			// ft_free_pinters_array(pipes);
			return NULL;
		}
		else
			printf("Pipe number %d created\n", i + 1);
		i++;
	}
	return (pipes);
}

void	ft_create_proc(int cmds, int **pipes, char **argv, char **paths)
{
	int	*pids;
	int i;

	i = 0;
	pids = malloc(sizeof(int) * cmds);
	if (pids == NULL)
		exit(1);
	while (i < cmds) 
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			// ft_free_array(pids);
			exit(1);
		}
		if (pids[i] == 0)
		{
			printf("child created %d\n", i);
			ft_close_pipes(i, cmds, pipes);
			printf("all pipes closed in process %d\n", i);
			printf("\n");
			ft_handle_childs(i, pipes, argv, paths);
			// printf("%d returned from hand\n", i);
			printf("\n");
			exit(1);
		}
		i++;
	}
	ft_wait(pids, cmds);
}
