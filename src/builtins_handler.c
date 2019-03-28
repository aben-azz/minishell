/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 06:56:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/28 20:10:10 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static t_built g_built[] = {
	{"echo", &ft_echo},
	{"cd", &ft_cd},
	{"setenv", &ft_setenv},
	{"unsetenv", &ft_unsetenv},
	{"env", &ft_env},
	{"exit", &ft_exit},
};

int		find_built(char **argv)
{
	int i;

	i = -1;
	while (++i < 7)
		if (!ft_strcmp(g_built[i].builtin, argv[0]))
		{
			g_built[i].function && g_built[i].function(av);
			return (1);
		}
	return (0);
}

int		ft_echo(char **argv)
{
	int i;

	(void)data;
	i = 0;
	while (argv[++i])
	{
		while (*argv[i])
		{
			if (!~ft_indexof("\"'", *argv[i]))
				ft_printf("%c", *argv[i]);
			(void)argv[i]++;
		}
		ft_printf(" ");
	}
	ft_printf(" \n");
	return (0);
}

int		ft_clear(char **argv)
{
	(void)data;
	ft_printf("\033c");
	return (0);
}

int		ft_env(char **argv)
{
	(void)data;
	ft_printf("%r\n", g_env, env_len(g_env), "\n");
	return (0);
}
