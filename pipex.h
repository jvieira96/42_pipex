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

// processes_pipes.c
void	ft_close_pipes(int	index, int cmds, int **pipes);
void	ft_create_proc(int cmds, int **pipes, char **argv, char **envp);
int **ft_create_pipes(int cmds);
void ft_middle_childs(char **argv, int **pipes, int index, char **paths);
// utils.c
void ft_close_main_pipes(int **pipes, int cmds);
void ft_read_from_file(char **argv, int **pipes, int cmds);
void ft_first_child(char **argv, int **pipes, int index, char **paths);
void ft_last_child(char **argv, int **pipes, int index, char **paths);
void	ft_wait(int *pids, int cmds);
int ft_param_size(char *argv[]);
char *ft_get_path(char *envp[]);
void	ft_exec_command(int index, char **argv, char **paths);
// erros.c
/* void 	ft_free_array(int *array);
void	ft_free_pinters_array(int **array); */

#endif