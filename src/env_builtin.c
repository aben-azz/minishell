/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 04:41:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/11 23:30:15 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_env(char *key, char *value)
{
	int		index;
	char	*tmp;

	if (!(tmp = ft_strjoin("=", value)))
		exit(0);
	if (~(index = get_env_index(key)))
		free(g_env[index]);
	else if ((index = env_len(g_env)))
		if (!(g_env = realloc_env(index + 1, -1)))
			exit(0);
	if (!(g_env[index] = ft_strjoin(key, value ? tmp : "=")))
		exit(0);
	ft_strdel(&tmp);
	return (0);
}

int		ft_setenv(char **argv)
{
	if (!argv[1])
		return (ft_env(argv));
	else if (argv[2] && argv[3])
		return (ft_printf("setenv: Too many arguments.\n") > 0);
	return (set_env(argv[1], argv[2]));
}

char	**realloc_env(int new_size, int exception)
{
	char	**new;
	int		i;
	int		j;

	if (!(new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (g_env[++i] && i < new_size)
	{
		(~exception && j == exception) && j++;
		if (!(new[i] = ft_strdup(g_env[j++])))
			exit(0);
		free(g_env[i]);
	}
	free(g_env);
	return (new);
}

int		ft_unsetenv(char **argv)
{
	int		index;

	if (!argv[1])
		return (ft_env(argv));
	else if (argv[2])
		return (ft_printf("setenv: Too many arguments.\n") > 0);
	if (~(index = get_env_index(argv[1])))
	{
		if (!(g_env = realloc_env(env_len(g_env) - 1, index)))
			return (0);
		return (0);
	}
	return (0);
}

int		ft_exit(char **argv)
{
	ft_splitdel(argv);
	exit(0);
	return (0);
}
