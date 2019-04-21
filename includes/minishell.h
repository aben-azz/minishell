/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:25:27 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/21 11:26:22 by aben-azz         ###   ########.fr       */
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
# define PREFIX "\x1b[32m➜ \x1b[0m\x1b[37m\x1b[1m"
# define SUFFIX "%s\x1b[0m \x1b[1m\x1b[31m%s\x1b[0m\x1b[32m> \x1b[0m"

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
void			init_env(char **env);
void			display_prompt_prefix();
int				quick_cd(char **cmd);
#endif

/*

** $VAR => Get value of VAR
** $#VAR => Get length value of VAR
** $VAR[i] => Get ith element value of VAR
** $VAR[i,x] => Get element betwin i and x of value of VAR

$var[: i]
	As above, but now splitting occurs at the colon character.
$var[: i j]
	As above, but instead of returning just a string, it now returns a list of two strings. If the result is being interpolated into a larger string,
		this list will be flattened into one big string, with each element separated by a space.
$var["\\\\" i]
	Separate on backslash characters. Actually, the first argument – if it doesn't have the form of a number,
	or a plain variable name – can be any regular expression. So to split on numbers, use ‘$var["[0-9]+" 10 20]’.
$var[hello]
	Calls assoc on var with "hello", expecting it to be an alist (see Association Lists).
$#var[hello]
	Returns the length of the cdr of the element of var who car is equal to "hello".
*/
