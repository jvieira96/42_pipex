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
	int		here_doc;
	int		cmds;
}	t_pipex;

// main.c
void	ft_wait(int *pids, t_pipex pipex);
int		ft_param_size(char *argv[]);

// processes.c
void	ft_first_child(int index, t_pipex pipex, int argc);
void	ft_middle_childs(int index, t_pipex pipex);
void	ft_last_child(int index, t_pipex pipex, int argc);
void	ft_handle_childs(int index, t_pipex pipex, int argc);
void	ft_create_proc(t_pipex	pipex, int argc);

// pipes.c
int		**ft_create_pipes(int cmds);
void	ft_close_pipes(int	index, t_pipex	pipex);
void	ft_close_parent_pipes(t_pipex pipex);

// utils.c
char	*ft_get_path(char *envp[], t_pipex pipex);
void	ft_exec_command(int index, t_pipex pipex);
t_pipex	ft_init_pipex(char **argv, char **envp, int cmds, int here_doc);
int		ft_handle_heredoc(char *delimiter);
void	ft_here_doc_special(t_pipex pipex, int argc);

// erros.c
void	ft_free_array(char **array);
void	ft_free_pipes(int **pipes, int cmds);
void	ft_file_check(t_pipex pipex, int argc);
void	ft_cmds_check(int argc, t_pipex pipex);
int		ft_exec_check(t_pipex pipex, char **cmds);
void	ft_free_all(t_pipex);

#endif
