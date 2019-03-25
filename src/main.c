/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/25 01:27:37 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
static t_built g_built[] = {
	{"echo", &ft_echo},
	{"cd", &ft_cd},
	{"setenv", &ft_setenv},
	{"unsetenv", &ft_unsetenv},
	{"env", &ft_env},
	{"exit", &ft_exit}
};

int		ft_echo(t_data *data)
{
	(void)data;
	ft_printf("commande echo\n");
	return (0);
}

int		ft_cd(t_data *data)
{
	(void)data;
	ft_printf("commande cd\n");
	return (0);
}

int		ft_setenv(t_data *data)
{
	(void)data;
	ft_printf("commande setenv\n");
	return (0);
}

int		ft_unsetenv(t_data *data)
{
	(void)data;
	ft_printf("commande unsetenv\n");
	return (0);
}

int		ft_env(t_data *data)
{
	(void)data;
	ft_printf("commande env\n");
	return (0);
}

int		ft_exit(t_data *data)
{
	(void)data;
	ft_printf("commande exit\n");
	exit(0);
	return (0);
}

char	*get_env(char *env)
{
	return (ft_strsub(env, ft_indexof(env, '=') + 1, ft_strlen(env)));
}

int		exec_command(t_data *data)
{
	ft_printf("non builtin cmd: %s\n", data->argv[0]);
	return (0);
}

int		find_built(t_data *data)
{
	int i;

	i = -1;
	while (++i < 6)
		if (!ft_strcmp(g_built[i].builtin, data->argv[0]))
		{
			g_built[i].function && g_built[i].function(data);
			return (1);
		}
	return (0);
}

int		handler(char *string, char **env)
{
	char	**commands;
	t_data	*data;

	(void)env;
	data = malloc(sizeof(t_data));
	commands = ft_strsplit(string, ';');
	while (*commands)
	{
		data->argv = ft_strsplit(*commands++, ' ');
		find_built(data) || exec_command(data);
	}
	return (1);
}

int		main(int ac, char **av, char **env)
{
	char	*input;
	int		ret;

	(void)ac;
	(void)av;
	ret = 1;
	while (ret == 1)
	{
		ft_printf("$%s %s>", get_env(env[12]), get_env(env[9]));
		//signal(SIGINT, sighandler);
		((ret = get_next_line(0, &input, '\n')) > 0) && handler(input, env);
		if (ret == -1)
			break ;
	}
	return (0);
}
