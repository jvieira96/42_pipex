#include "pipex.h"

void	ft_close_pipes(int	index, t_pipex	pipex)
{
	int	pip;

	pip = 0;
	while (pip < pipex.cmds - 1)
	{
		if (pip + 1 != index)
			close(pipex.pipes[pip][0]);
		if (pip != index)
			close(pipex.pipes[pip][1]);
		pip++;
	}
}

void	ft_handle_childs(int index, t_pipex pipex)
{
	if (index == 0)
		ft_first_child(index, pipex);
	else if (index == ft_param_size(pipex.arg) - 4)
		ft_last_child(index, pipex);
	else
		ft_middle_childs(index, pipex);
}

int **ft_create_pipes(int cmds)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int *) * (cmds - 1));
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

void	ft_create_proc(t_pipex	pipex)
{
	int	*pids;
	int i;

	i = 0;
	pids = malloc(sizeof(int) * (pipex.cmds));
	if (pids == NULL)
		exit(1);
	while (i < pipex.cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			// ft_free_array(pids);
			exit(1);
		}
		if (pids[i] == 0)
		{
			ft_close_pipes(i, pipex);
			ft_handle_childs(i, pipex);
			exit(1);
		}
		i++;
	}
	ft_close_parent_pipes(pipex);
	ft_wait(pids, pipex);
}
