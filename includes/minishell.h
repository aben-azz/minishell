/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:25:27 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/28 07:05:02 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/includes/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
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
	int				(*function)(t_data *data);
}				t_built;
int				ft_echo(t_data *data);
int				ft_cd(t_data *data);
int				ft_setenv(t_data *data);
int				ft_unsetenv(t_data *data);
int				ft_env(t_data *data);
int				ft_exit(t_data *data);
int				ft_clear(t_data *data);
void			init_env(char **env);
char			*get_env(char *name);
int				env_len(char **env);
int				ft_setenv(t_data *data);
char			**realloc_env(int new_size, int exception);
int				set_env(char *key, char *value);
int				get_env_index(char *name);
int				change_dir(char *path, int print_path);
#endif
