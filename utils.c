/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:54:56 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/02/24 15:54:58 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_first_child(char **argv, int **pipes, int index, char **paths)
{
	char	buffer[BUFFER_SIZE];
	int		fd;
	int		bytesread;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("error opening the file");
		exit(1);
	}
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread == -1)
	{
		perror("error reading file\n");
		close(fd);
		exit(2);
	}
	close(fd);
	dup2(pipes[0][1], STDOUT_FILENO);
	close(pipes[0][1]);
	ft_exec_command(index, argv, paths);
}

void ft_last_child(char **argv, int **pipes, int index, char **paths)
{
	char	buffer[BUFFER_SIZE];
	int		bytesread;
	int		fd;

	fd = open(argv[index + 3], O_WRONLY);
	if (fd == -1)
	{
		perror("error opening the file\n");
		exit(3);
	}
	bytesread = read(pipes[index - 1][0], buffer, BUFFER_SIZE);
	if (bytesread == -1)
	{
		perror("error reading from pipe\n");
		close(fd);
		exit(4);
	}
	dup2(fd, STDOUT_FILENO);
	close(pipes[index - 1][0]);
	close(fd);
	ft_exec_command(index, argv, paths);
}

void ft_middle_childs(char **argv, int **pipes, int index, char **paths)
{
	char	buffer[BUFFER_SIZE];
	int		bytesread;

	bytesread = read(pipes[index - 1][0], buffer, BUFFER_SIZE);
	if (bytesread == -1)
	{
		perror("error reading file\n");
		exit(5);
	}
	dup2(pipes[index][1], STDOUT_FILENO);
	close(pipes[index - 1][0]);
	close(pipes[index][1]);
	ft_exec_command(index, argv, paths);
}

char *ft_get_path(char *envp[])
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	ft_printf("PATH VARIABLE NOT FOUND\n");
	exit(6);
}

void	ft_exec_command(int index, char **argv, char **paths)
{
	char	full_path[1024];
	char	**cmds;
	int 	i;

	i = 0;
	cmds = ft_split(argv[index + 2], ' ');
	while(paths[i])
	{
		ft_strlcpy(full_path, paths[i], sizeof(full_path));
		ft_strlcat(full_path, "/", sizeof(full_path));
		ft_strlcat(full_path, cmds[0], sizeof(full_path));
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, cmds, NULL);
			perror("exec failed");
			exit(2);
		}
		i++;
	}
}

void	ft_wait(int *pids, int cmds)
{
	int		i;
	int		status;
	pid_t	child_id;

	i = 0;
	while (i < cmds)
	{
		child_id = waitpid(pids[i], &status, 0);
		if (child_id == -1)
			perror("waitpid failed");
		else
			printf("waited for child %d\n", pids[i]);

			if (WIFEXITED(status))  // Child exited normally
				printf("Child %d exited with status %d\n", pids[i], WEXITSTATUS(status));
			else if (WIFSIGNALED(status))  // Child was terminated by a signal
				printf("Child %d was killed by signal %d\n", pids[i], WTERMSIG(status));
			else if (WIFSTOPPED(status))  // Child was stopped (not common in simple cases)
				printf("Child %d was stopped by signal %d\n", pids[i], WSTOPSIG(status));
		i++;
	}
}
