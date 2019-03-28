/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 04:41:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/28 05:40:12 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		ft_setenv(t_data *data)
{
	int		index;
	char	*tmp;

	if (!data->argv[1])
		return (ft_env(data));
	else if (data->argv[2] && data->argv[3])
		return (ft_printf("setenv: Too many arguments.") > 0);
	tmp = ft_strjoin("=", data->argv[2]);
	if (~(index = get_env_index(data->argv[1])))
		free(g_env[index]);
	else if ((index = env_len(g_env)))
		g_env = realloc_env(index + 1);
	g_env[index] = ft_strjoin(data->argv[1], data->argv[2] ? tmp : "=");
	return (0);
}

char	**realloc_env(int new_size)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (g_env[++i] && i < new_size)
	{
		new[i] = ft_strdup(g_env[i]);
		free(g_env[i]);
	}
	free(g_env);
	return (new);
}
