/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:25:27 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/01 08:55:13 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# include <sys/stat.h>
# define PREFIX "\x1b[36m$\x1b[0m\x1b[31m\x1b[1m"
# define SUFFIX "\x1b[0m\x1b[36m>\x1b[0m"

typedef struct	s_data
{
	int				xd;
	char			**argv;
}				t_data;
char					**g_env;
typedef struct stat	t_stat;
typedef struct	s_built
{
	char			*builtin;
	int				(*function)(char **argv);
}				t_built;
int				ft_echo(char **argv);
int				ft_cd(char **argv);
int				ft_unsetenv(char **argv);
int				ft_env(char **argv);
int				ft_exit(char **argv);
int				ft_clear(char **argv);
char			*get_env(char *name);
int				env_len(char **env);
int				ft_setenv(char **argv);
char			**realloc_env(int new_size, int exception);
int				set_env(char *key, char *value);
int				get_env_index(char *name);
int				change_dir(char *path, int print_path);
int				find_built(char **argv);
void			signal_handler_command(int sig);
void			signal_handler_empty(int sig);
void	init_env(char **env);
void			display_prompt_prefix();
#endif
