/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:10:37 by jpedro-f          #+#    #+#             */
/*   Updated: 2025/02/14 20:10:39 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
#define PIPEX_H

#define BUFFER_SIZE 1024

#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_pipex
{
	char	**env;
	char	**arg;
	char	**paths;
	int		**pipes;
	int		cmds;
}	t_pipex;

// processes_pipes.c
void	ft_close_pipes(int	index, t_pipex pipex);
void	ft_create_proc(t_pipex	pipex);
int **ft_create_pipes(int cmds);
void ft_middle_childs(int index, t_pipex pipex);
// utils.c
void ft_close_main_pipes(int **pipes, int cmds);
void ft_first_child(int index, t_pipex pipex);
void ft_last_child(int index, t_pipex pipex);
void	ft_wait(int *pids, t_pipex pipex);
int ft_param_size(char *argv[]);
char *ft_get_path(char *envp[]);
void	ft_exec_command(int index, t_pipex pipex);
void ft_close_parent_pipes(t_pipex pipex);
t_pipex	ft_init_pipex(char **argv, char **envp, int cmds, char **paths);
// erros.c
/* void 	ft_free_array(int *array);
void	ft_free_pinters_array(int **array); */

#endif
