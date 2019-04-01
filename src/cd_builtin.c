/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 05:59:29 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/28 20:10:12 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void		print_pth(char *path)
{
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
	}
	else
	{
		ft_putstr("cd: ");
		if (access(path, F_OK) == -1)
			ft_putstr("no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_putstr("permission denied: ");
		else
			ft_putstr("not a directory: ");
		ft_putendl(path);
	}
	return (1);
}

static int		has_two_args(char **args)
{
	char	*cwd;
	char	buff[4096 + 1];
	char	*tmp;

	tmp = NULL;
	if (args[2])
	{
		if (args[3])
		{
			ft_putendl("cd: too many arguments");
			return (1);
		}
		cwd = getcwd(buff, 4096);
		if (!(tmp = ft_strreplace(cwd, args[1], args[2])))
		{
			ft_putstr("cd: string not in pwd: ");
			ft_putendl(args[1]);
			free(tmp);
			return (1);
		}
		change_dir(tmp, 1);
		free(tmp);
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
		return (1);
	}
	if (has_two_args(argv))
		return (1);
	else
	{
		if (ft_strequ(argv[1], "--") || ft_strequ(argv[1], "~"))
		{
			change_dir(home_path, 0);
			return (1);
		}
		else if (argv[1][0] == '-' && !argv[1][2])
		{
			change_dir(get_env("OLDPWD"), 1);
			return (1);
		}
		change_dir(argv[1], 0);
	}
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
