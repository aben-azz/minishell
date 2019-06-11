/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:21:25 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/11 23:46:11 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler_command(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, signal_handler_command);
		ft_printf("\n");
	}
}

int		quick_cd(char **cmd)
{
	char	*s;
	t_stat	f;
	char	buff[4096];

	getcwd(buff, 4096);
	s = (cmd[0] + ft_lastindexof(cmd[0], '/') + 1);
	if (!ft_strcmp(s, ".."))
		return (change_dir(ft_strsub(buff, 0, ft_lastindexof(buff, '/')), 0));
	else if (!ft_strcmp(s, "~"))
		return (change_dir(NULL, 0));
	else if (lstat(cmd[0], &f) != -1)
	{
		if (f.st_mode & S_IFDIR)
			return (change_dir(cmd[0], 0));
		else
			return (-1);
	}
	else if (lstat(s, &f) != -1 && (f.st_mode & S_IFDIR))
	{
		return (change_dir(s, 0));
	}
	return (-1);
}

void	display_prompt_prefix(void)
{
	char	*string;
	char	*name;
	int		a;

	a = 1;
	name = get_env("USER");
	if (!name)
	{
		name = "aben-azz~";
		a = 0;
	}
	string = NULL;
	string = getcwd(string, 20);
	ft_printf(PREFIX);
	ft_printf(SUFFIX, (string + ft_lastindexof(string, '/') + 1), name);
	if (a)
		ft_strdel(&name);
	ft_strdel(&string);
}

int		execute(char **cmd, int dir, int fre)
{
	t_stat	f;

	(void)fre;
	(void)dir;
	if (lstat(cmd[0], &f) != -1)
		if (f.st_mode & S_IXUSR)
			if (execve(cmd[0], cmd, g_env))
				return (1);
	return (-1);
}

void	ft_error(char *string, char **path, char **av)
{
	ft_printf("minishell: command not found: %s\n", string);
	ft_splitdel(av);
	ft_splitdel(path);
	exit(0);
}
