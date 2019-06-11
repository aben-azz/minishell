/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 06:57:16 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/11 23:28:33 by aben-azz         ###   ########.fr       */
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

	i = ft_split_count(env);
	if (!(g_env = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		exit(0);
	i = -1;
	while (env[++i])
		if (!(g_env[i] = ft_strdup(env[i])))
			exit(0);
	g_env[i] = NULL;
}

char	*get_env(char *name)
{
	int i;

	if (!name)
		return (NULL);
	if (~(i = get_env_index(name)))
		return (ft_strsub(g_env[i], ft_indexof(g_env[i], '=') + 1,
				ft_strlen(g_env[i])));
	else
		return (NULL);
}

int		get_env_index(char *name)
{
	int		i;
	char	*str;

	i = -1;
	if (!name)
		return (-1);
	while (g_env[++i])
	{
		if (!(str = ft_strsub(g_env[i], 0, ft_indexof(g_env[i], '='))))
			exit(0);
		if (!ft_strcmp(str, name))
		{
			ft_strdel(&str);
			return (i);
		}
		ft_strdel(&str);
	}
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
