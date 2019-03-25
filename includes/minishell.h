/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:25:27 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/25 01:08:26 by aben-azz         ###   ########.fr       */
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
# define PREFIX "\x1b[36m$\x1b[0m\x1b[31m\x1b[1m"
# define SUFFIX "\x1b[0m\x1b[36m>\x1b[0m"

typedef struct	s_data
{
	int				xd;
	char 			**argv;
}				t_data;
int				get(int n, int iter_max);
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
#endif
