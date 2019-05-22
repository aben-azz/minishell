/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 06:57:16 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/22 16:02:17 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_len(char **env)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (env[++i])
		count++;
	return (count);
}

void	init_env(char **env)
{
	int		i;

	if (!(g_env = (char **)ft_memalloc(sizeof(char *) * (env_len(env) + 1))))
		exit(0);
	i = -1;
	while (env[++i])
		if (!(g_env[i] = ft_strdup(env[i])))
			exit(0);
}

char	*get_env(char *name)
{
	int i;

	if (!name)
		return (NULL);
	if (~(i = get_env_index(name)))
		return (g_env[i] + ft_indexof(g_env[i], '=') + 1);
	else
		return (NULL);
}

int		get_env_index(char *name)
{
	int i;
	char *string;

	i = -1;
	if (!name)
		return (-1);
	while (g_env[++i])
	{
		if (!(string = ft_strsub(g_env[i], 0, ft_indexof(g_env[i], '='))))
			return (-1);
		if (!ft_strcmp(string, name))
		{
			ft_strdel(&string);
			return (i);
		}
		ft_strdel(&string);
	}
	//ft_strdel(&string);
	return (-1);
}

void	signal_handler_empty(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, signal_handler_empty);
		ft_printf("\n");
		display_prompt_prefix();
	}
}
