/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 05:59:29 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/21 11:26:18 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_pth(char *path)
{
	if (!path)
		return ;
	ft_putstr(path);
}

int				change_dir(char *path, int print_path)
{
	char	*cwd;
	char	buff[4097];

	cwd = getcwd(buff, 4096);
	if (!chdir(path))
	{
		if (print_path)
		{
			print_pth(path);
			ft_putchar('\n');
		}
		set_env("OLDPWD", cwd);
		set_env("PWD", getcwd(buff, 4096));
	}
	else
	{
		if (access(path, F_OK) == -1)
			ft_putstr("cd: no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_putstr("cd: permission denied: ");
		else
			ft_putstr("cd: not a directory: ");
		ft_putendl(path);
	}
	//ft_strdel(&path);
	return (1);
}

static int		has_two_args(char **args)
{
	char	cwd[4096];
	//char	buff[4096 + 1];
	char	*tmp;

	tmp = NULL;
	if (args[2])
	{
		if (args[3])
		{
			ft_putendl("cd: too many arguments\n");
			return (1);
		}
		getcwd(cwd, 4096);
		if (!(tmp = ft_strreplace(cwd, args[1], args[2])))
		{
			ft_putstr("cd: string not in pwd: ");
			ft_putendl(args[1]);
			return (1);
		}
		change_dir(tmp, 1);
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

int				ft_cd(char **argv)
{
	char	*home_path;

	home_path = get_env("HOME");
	if (!argv[1])
	{
		change_dir(home_path, 0);
		ft_strdel(&home_path);
		return (1);
	}
	if (has_two_args(argv))
		return (1);
	else
	{
		if (ft_strequ(argv[1], "--") || ft_strequ(argv[1], "~"))
		{
			change_dir(home_path, 0);
			ft_strdel(&home_path);
			return (1);
		}
		else if (argv[1][0] == '-' && !argv[1][2])
		{
			change_dir(get_env("OLDPWD"), 1);
			ft_strdel(&home_path);
			return (1);
		}
		change_dir(argv[1], 0);
	}
	ft_strdel(&home_path);
	return (1);
}

void			signal_handler_command(int sig)
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
		return (change_dir(get_env("HOME"), 0));
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
