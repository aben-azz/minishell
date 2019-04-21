/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/21 11:26:15 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int		execute(char **cmd, int dir)
{
	t_stat	f;

	(void)dir;
	if (lstat(cmd[0], &f) != -1)
	{
		if (f.st_mode & S_IXUSR)
			return (execve(cmd[0], cmd, g_env));
	}
	return (-1);
}

int		exec_valid_command(char **argv, int m)
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
		ft_printf("minishell: command not found: %s\n",
			(av[0] + ft_lastindexof(av[0], '/') + 1));
		exit(0);
	}
	else if (pid < 0)
		return (ft_printf("Fork failed to create a new process.\n") ? -1 : -1);
	wait(&pid);
	return (1);
}

int		is_expansion_printable(char *s, int dollar_index, int i)
{
	return (!((s[dollar_index - 1] && s[dollar_index - 1] == '\'') &&
			(s[i] && s[i] == '\'')));
}

char	*get_expansion(char *string, char *act_env, int length)
{
	char	*replaced;

	if (get_env(act_env + 1 + length))
	{
		if (!length)
			replaced = ft_strreplace(string, act_env, get_env(act_env + 1));
		else
			replaced = ft_strreplace(string, act_env,
					ft_itoa((int)ft_strlen(get_env(act_env + 2))));
	}
	else if (length)
		replaced = ft_strreplace(string, act_env, "0");
	else
		replaced = ft_strreplace(string, act_env, "");
	return (replaced);
}

char	*expansion_dollar(char *string)
{
	int		i;
	int		length;
	int		dollar_index;
	char	*replaced;
	char	*act_env;

	if (!string || (string && !(replaced = ft_strdup(string))))
		return (NULL);
	dollar_index = ft_indexof(string, '$');
	if (!~dollar_index)
		return (string);
	i = dollar_index + 1;
	length = 0;
	(string[i] == '#') && ((length = 1) && (i++));
	while (i < (int)ft_strlen(string) && string[i] && (string[i] == '_' ||
		ft_isalpha(string[i])))
		i++;
	if (is_expansion_printable(string, dollar_index, i))
	{
		act_env = ft_substr(string, dollar_index, i);
		replaced = get_expansion(string, act_env, length);
	}
	return (replaced);
}

int		handler(char *string)
{
	char	**commands;
	char	**argv;
	char	*test;

	if ((test = expansion_dollar(string)))
		string = test;
	commands = ft_strsplit(string, ';');
	while (*commands)
	{
		argv = ft_strsplitwhitespace(*commands++);
		if (!~find_built(argv))
		{
			while (ft_is_space(*argv[0]))
				(void)*argv[0]++;
			if (!~quick_cd(argv))
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
		((ret = get_next_line(0, &input, '\n')) > 0) && handler(input);
		if (ret == -1)
			break ;
	}
	return (0);
}
