/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 06:56:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/28 07:40:50 by aben-azz         ###   ########.fr       */
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
	{"clear", &ft_clear}
};

int		find_built(t_data *data)
{
	int i;

	i = -1;
	while (++i < 7)
		if (!ft_strcmp(g_built[i].builtin, data->argv[0]))
		{
			g_built[i].function && g_built[i].function(data);
			return (1);
		}
	return (0);
}

int		ft_echo(t_data *data)
{
	int i;

	(void)data;
	i = 0;
	while (data->argv[++i])
	{
		while (*data->argv[i])
		{
			if (!~ft_indexof("\"'", *data->argv[i]))
				ft_printf("%c", *data->argv[i]);
			(void)data->argv[i]++;
		}
		ft_printf(" ");
	}
	ft_printf(" \n");
	return (0);
}

int		ft_clear(t_data *data)
{
	(void)data;
	ft_printf("\033c");
	return (0);
}

int		ft_env(t_data *data)
{
	(void)data;
	ft_printf("%r\n", g_env, env_len(g_env), "\n");
	return (0);
}
