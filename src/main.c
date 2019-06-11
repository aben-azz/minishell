/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/11 23:46:05 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int		exec(char **argv, char **av, int m, char **path)
{
	int i;
	int j;

	(!m && *argv[0] == '\\' && *(argv[0] + 1) == '/') && ++argv[0];
	if (!m && ~execute(argv, 0, 0))
		return (1);
	j = 0;
	while (path[j] && (i = -1))
	{
		while (argv[++i])
		{
			if (i)
				av[i] = argv[i];
			else
			{
				ft_strdel(&av[i]);
				if (!(av[i] = ft_strcjoin(path[j++], argv[0], '/')))
					return (0);
			}
		}
		if (~execute(av, 1, 1))
			return (1);
	}
	ft_error((av[0] + ft_lastindexof(av[0], '/') + 1), path, av);
	return (1);
}

int		exec_valid_command(char **argv, int m)
{
	pid_t	pid;
	char	**av;
	char	**path;
	char	*leak;

	if (!(leak = get_env("PATH")))
		exit(0);
	if (!(path = ft_strsplit(leak, ':')))
		exit(0);
	ft_strdel(&leak);
	if (!(av = malloc(sizeof(char*) * 2048)))
		exit(0);
	signal(SIGINT, signal_handler_command);
	if (!(pid = fork()))
		exec(argv, av, m, path);
	else if (pid < 0)
		return (ft_printf("Fork failed to create a new process.\n") ? -1 : -1);
	wait(&pid);
	ft_splitdel(av);
	ft_splitdel(path);
	return (1);
}

void	exec_handler(char **av, int *ij)
{
	if (!~find_built(av))
	{
		while (ft_is_space(av[0][ij[1]]))
			ij[1]++;
		(!~quick_cd(av)) && exec_valid_command(av, !(av[0][ij[1]] == '/' ||
				(av[0][ij[1]] == '\\' && av[0][ij[1] + 1] == '/')));
	}
}

int		handler(char **string)
{
	char	**cmd;
	char	**av;
	char	*test;
	int		ij[2];

	ij[0] = 0;
	if (!(test = expansion_dollar(*string)))
		exit(0);
	if (!(cmd = ft_strsplit(test, ';')))
		exit(0);
	while (cmd[ij[0]])
	{
		ij[1] = 0;
		if (!(av = ft_strsplitwhitespace(cmd[ij[0]++])) || !ft_split_count(av))
			return (-1);
		exec_handler(av, ij);
		ft_splitdel(av);
	}
	ft_splitdel(cmd);
	ft_strdel(&test);
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
		if ((ret = get_next_line(0, &input, '\n')) > 0)
		{
			handle_input(&input);
			ft_strdel(&input);
		}
		if (ret == -1)
			break ;
	}
	ft_splitdel(g_env);
	return (0);
}
