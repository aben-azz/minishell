/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 05:59:29 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/11 23:26:32 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pth(char *path)
{
	if (!path)
		return ;
	ft_putstr(path);
}

int		change_dir(char *path, int print_path)
{
	char	*cwd;
	char	buff[4097];

	if (!(cwd = getcwd(buff, 4096)))
		return (0);
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
			ft_printf("cd: no such e file or directory: %s\n", path);
		else if (access(path, R_OK) == -1)
			ft_printf("cd: permission denied: %s\n", path);
		else
			ft_printf("cd: not a directory: %s\n", path);
	}
	return (1);
}

int		has_two_args(char **args)
{
	char	cwd[4096];
	char	*tmp;

	tmp = NULL;
	if (args[2])
	{
		if (args[3])
		{
			ft_putendl("cd: too many arguments\n");
			return (1);
		}
		if (!(getcwd(cwd, 4096)))
			return (0);
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

int		set_oldpwd(char *home_path)
{
	ft_strdel(&home_path);
	home_path = get_env("OLDPWD");
	change_dir(home_path, 1);
	ft_strdel(&home_path);
	return (1);
}

int		ft_cd(char **argv)
{
	char	*home_path;

	if ((home_path = get_env("HOME")) && !argv[1])
	{
		change_dir(home_path, 0);
		ft_strdel(&home_path);
		return (1);
	}
	!home_path ? exit(0) : 0;
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
			return (set_oldpwd(home_path));
		change_dir(argv[1], 0);
	}
	ft_strdel(&home_path);
	return (1);
}
