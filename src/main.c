/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/25 06:34:53 by aben-azz         ###   ########.fr       */
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

char	*get_env(char **env, char *name)
{
	int i;

	i = -1;
	while (env[++i])
		if (!ft_strcmp(ft_strsub(env[i], 0, ft_indexof(env[i], '=')), name))
			return (ft_strsub(env[i], ft_indexof(env[i], '=') + 1,
				ft_strlen(env[i])));
			return (NULL);
}

int		exec_valid_command(t_data *d, char **env, int m)
{
	pid_t pid;
	char **av;
	char **path;
	int i;

	path = ft_strsplit(get_env(env, "PATH"), ':');
	av = malloc(sizeof(char*) * 2048);
	if (!(pid = fork()))
	{
		(!m && *d->argv[0] == '\\' && *(d->argv[0] + 1) == '/') && ++d->argv[0];
		if (!m && ~execve(d->argv[0], d->argv, NULL))
			return (1);
		while (*path && (i = -1))
		{
			while (d->argv[++i])
				av[i] = i ? d->argv[i] : ft_strjoin(ft_strjoin(*path++, "/"),
					d->argv[0]);
			if (~execve(av[0], av, NULL))
				return (1);
		}
		ft_printf("minishell: no such file or directory: %s\n", d->argv[0]);
	}
	else if (pid < 0)
		return (ft_printf("Fork failed to create a new process.\n") ? -1 : -1);
	wait(&pid);
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
		if (!find_built(data))
		{
			while (ft_is_space(*data->argv[0]))
				(void)*data->argv[0]++;
			exec_valid_command(data, env, !(*data->argv[0] == '/' ||
				(*data->argv[0] == '\\' && *(data->argv[0] + 1) == '/')));
		}
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
		ft_printf("$%s \x1b[36m\x1b[0m\x1b[31m\x1b[1m%s\x1b[0m\x1b[36m\x1b[0m>",
			get_env(env, "PWD"), get_env(env, "USER"));
		//signal(SIGINT, sighandler);
		((ret = get_next_line(0, &input, '\n')) > 0) && handler(input, env);
		if (ret == -1)
			break ;
	}
	return (0);
}
