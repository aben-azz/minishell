/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 06:56:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/10 11:22:00 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_built(char **argv)
{
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(argv));
	else if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd(argv));
	else if (!ft_strcmp(argv[0], "setenv"))
		return (ft_setenv(argv));
	else if (!ft_strcmp(argv[0], "unsetenv"))
		return (ft_unsetenv(argv));
	else if (!ft_strcmp(argv[0], "env"))
		return (ft_env(argv));
	else if (!ft_strcmp(argv[0], "exit"))
		return (ft_exit(argv));
	return (-1);
}

int		ft_echo(char **argv)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!~ft_indexof("\"'", argv[i][j]))
				ft_printf("%c", argv[i][j]);
			j++;
		}
		i++;
		ft_printf(" ");
	}
	ft_printf(" \n");
	return (0);
}

int		ft_env(char **argv)
{
	(void)argv;
	ft_printf("%r\n", g_env, env_len(g_env), "\n");
	return (0);
}
