/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/01 08:12:27 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <unistd.h>

void	display_prompt_prefix(void)
{
	char *string;
	char *name;

	name = get_env("USER");
	name || (name = "aben-azz~");
	string = NULL;
	string = getcwd(string, 20);
	ft_printf("\x1b[32m➜ \x1b[0m\x1b[37m\x1b[1m");
	ft_printf("%s\x1b[0m \x1b[1m\x1b[31m%s\x1b[0m\x1b[32m> \x1b[0m", (string +
		ft_lastindexof(string, '/') + 1), name);
}

int		execute(char **cmd, int dir)
{
	(void)dir;
	t_stat	f;
	char	*s;
	char	*buff;


	buff = NULL;
	buff = getcwd(buff, 4096);
	s = (cmd[0] + ft_lastindexof(cmd[0], '/') + 1);
	if (!ft_strcmp(s, ".."))
		return (change_dir(ft_strsub(buff, 0, ft_lastindexof(buff, '/')), 0));
	else if (!ft_strcmp(s, "~"))
		return (change_dir(get_env("HOME"), 0));
	else if (lstat(cmd[0], &f) != -1)
	{
		if (f.st_mode & S_IFDIR)
			return (change_dir(cmd[0], 0));
		if (f.st_mode & S_IXUSR)
			return (execve(cmd[0], cmd, g_env));
	}
	else if (lstat(s, &f) != -1 && (f.st_mode & S_IFDIR))
	{
		ft_printf("lstat ok\n");
		return (change_dir(s, 0));
	}
	return (-1);
}

int		exec_valid_command(char **argv, int m)
{
	pid_t	pid;
	char	**av;
	char	**path;
	int		i;
	//char	*s;

	//s = (cmd[0] + ft_lastindexof(cmd[0], '/') + 1);
	path = ft_strsplit(get_env("PATH"), ':');
	av = malloc(sizeof(char*) * 2048);
	signal(SIGINT, signal_handler_command);
	pid = fork();
	if (pid == 0)
	{
		(!m && *argv[0] == '\\' && *(argv[0] + 1) == '/') && ++argv[0];
		if (!m && ~execute(argv, 0))
			return (1);
		while (*path && (i = -1))
		{
			while (argv[++i])
				av[i] = i ? argv[i] : ft_strjoin(ft_strjoin(*path++, "/"),
					argv[0]);
			if (~execute(av, 1))
				return (1);
		}
		ft_printf("minishell: command not found: %s\n", (av[0] + ft_lastindexof(av[0], '/') + 1));
		exit(0);
	}
	else if (pid < 0)
		return (ft_printf("Fork failed to create a new process.\n") ? -1 : -1);
	wait(&pid);
	return (1);
}

int		handler(char *string)
{
	char	**commands;
	char	**argv;

	commands = ft_strsplit(string, ';');
	while (*commands)
	{
		argv = ft_strsplit(*commands++, ' ');
		if (!~find_built(argv))
		{
			while (ft_is_space(*argv[0]))
				(void)*argv[0]++;
			exec_valid_command(argv, !(*argv[0] == '/' ||
				(*argv[0] == '\\' && *(argv[0] + 1) == '/')));
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
		//signal(SIGTSTP, signal_handler_stop);
		((ret = get_next_line(0, &input, '\n')) > 0) && handler(input);
		if (ret == -1)
			break ;
	}
	return (0);
}
