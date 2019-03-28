/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 06:56:10 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/28 05:46:38 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		ft_echo(t_data *data)
{
	int i;

	(void)data;
	i = 0;
	while (data->argv[++i])
	{
		while (*data->argv[i])
		{
			if (!~ft_indexof("\"'", *data->argv[i]))
				ft_printf("%c", *data->argv[i]);
			(void)data->argv[i]++;
		}
		ft_printf(" ");
	}
	ft_printf(" \n");
	return (0);
}

int		ft_clear(t_data *data)
{
	(void)data;
	ft_printf("\033c");
	return (0);
}

void			change_dir(char *path, int print_path)
{
	char	*cwd;
	char	buff[4097];

	(void)print_path;
	cwd = getcwd(buff, 4096);
	if (!chdir(path))
	{
		// if (print_path)
		// {
		// 	print_pth(path);
		// 	ft_putchar('\n');
		// }
		//set_env_var("OLDPWD", cwd);
	}
	else
	{
		ft_printf("cd: ");
		if (access(path, F_OK) == -1)
			ft_printf("no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_printf("permission denied: ");
		else
			ft_printf("not a directory: ");
		ft_putendl(path);
	}
}

int		ft_cd(t_data *data)
{
	(void)data;
	return (0);
}

int		ft_env(t_data *data)
{
	(void)data;
	ft_printf("%r\n", g_env, env_len(g_env), "\n");
	return (0);
}
