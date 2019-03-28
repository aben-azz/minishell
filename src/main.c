/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/28 07:07:43 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <termios.h>
#include <unistd.h>
#include <term.h>
#include <curses.h>

static t_built g_built[] = {
	{"echo", &ft_echo},
	{"cd", &ft_cd},
	{"setenv", &ft_setenv},
	{"unsetenv", &ft_unsetenv},
	{"env", &ft_env},
	{"exit", &ft_exit},
	{"clear", &ft_clear}
};

void display_prompt_prefix(void)
{
	char *string;

	string = NULL;
	string = getcwd(string, 20);
	ft_printf("\x1b[32m➜ \x1b[0m\x1b[37m\x1b[1m");
	ft_printf("%s\x1b[0m \x1b[1m\x1b[31m%s\x1b[0m\x1b[32m> \x1b[0m", (string +
		ft_lastindexof(string, '/') + 1), get_env("USER"));
}

int		ft_exit(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

void signal_handler_command(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, signal_handler_command);
		ft_printf("\n");
	}
}

void signal_handler_empty(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, signal_handler_empty);
		ft_printf("\n");
		display_prompt_prefix();
	}
}

int execute(char **cmd, int dir)
{
	t_stat f;
	char *s;
	char *buff;

	buff = NULL;
	buff = getcwd(buff, 4096);
	s = (cmd[0] + ft_lastindexof(cmd[0], '/') + 1);
	if (!ft_strcmp(s, ".."))
		return (change_dir(ft_strsub(buff, 0, ft_lastindexof(buff, '/')),0));
	else if(!ft_strcmp(s, "~"))
		return (change_dir(get_env("HOME"), 0));
	else if (lstat(cmd[0], &f) != -1)
	{
		if (f.st_mode & S_IFDIR)
			return (change_dir(cmd[0], 0));
		if (f.st_mode & S_IXUSR)
			return (execve(cmd[0], cmd, NULL));
	}
	else if (lstat(s, &f) != -1 && (f.st_mode & S_IFDIR))
		return (change_dir(s, 0));
	ft_printf("minishell: no such file or directory: %s\n", dir ? s : cmd[0]);
	return (0);
}

int		exec_valid_command(t_data *d, int m)
{
	pid_t	pid;
	char	**av;
	char	**path;
	int		i;

	path = ft_strsplit(get_env("PATH"), ':');
	av = malloc(sizeof(char*) * 2048);
	signal(SIGINT, signal_handler_command);
	if (!(pid = fork()))
	{
		(!m && *d->argv[0] == '\\' && *(d->argv[0] + 1) == '/') && ++d->argv[0];
		if (!m && ~execute(d->argv, 0))
			return (1);
		while (*path && (i = -1))
		{
			while (d->argv[++i])
				av[i] = i ? d->argv[i] : ft_strjoin(ft_strjoin(*path++, "/"),
					d->argv[0]);
			if (~execute(av, 1))
				return (1);
		}
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
	while (++i < 7)
		if (!ft_strcmp(g_built[i].builtin, data->argv[0]))
		{
			g_built[i].function && g_built[i].function(data);
			return (1);
		}
	return (0);
}

int		handler(char *string)
{
	char	**commands;
	t_data	*data;

	data = malloc(sizeof(t_data));
	commands = ft_strsplit(string, ';');
	while (*commands)
	{
		data->argv = ft_strsplit(*commands++, ' ');
		if (!find_built(data))
		{
			while (ft_is_space(*data->argv[0]))
				(void)*data->argv[0]++;
			exec_valid_command(data, !(*data->argv[0] == '/' ||
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
	init_env(env);
	ret = 1;
	while (ret == 1)
	{
		display_prompt_prefix();
		signal(SIGINT, signal_handler_empty);
		((ret = get_next_line(0, &input, '\n')) > 0) && handler(input);
		if (ret == -1)
			break ;
	}
	return (0);
}
