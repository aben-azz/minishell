/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 09:25:27 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/21 03:43:10 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# define USER "aben-azz"
# define PREFIX "\x1b[36m$\x1b[0m\x1b[31m\x1b[1m"USER"\x1b[0m\x1b[36m>\x1b[0m"

typedef struct	s_map
{
	int				**board;
	int				x;
	int				y;
}				t_map;
int				get(int n, int iter_max);
#endif
