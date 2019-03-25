/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/25 01:15:10 by aben-azz         ###   ########.fr       */
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

char *get_env(char *env)
{
	return (ft_strsub(env, ft_indexof(env, '=') + 1, ft_strlen(env)));
}

void handler(char *string, char **env)
{
	(void)env;
	char **commands;
	t_data *datas;
	int i;

	i = -1;
	datas = malloc(sizeof(t_data));

	commands = ft_strsplit(string, ';');
	while (*commands)
	{
		datas->argv = ft_strsplit(*commands, ' ');
		while (++i < 6)
			if (!ft_strcmp(g_built[i].builtin, datas->argv[0]))
			{
				g_built[i].function(datas);
				break ;
			}
		(void)*commands++;
	}
}
int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)g_built;

	char *input;
	int ret;

	ret = 1;
	while (ret == 1)
	{
		ft_printf("$%s %s>", get_env(env[12]), get_env(env[9]));
		//signal(SIGINT, sighandler);
		if ((ret = get_next_line(0, &input, '\n')) > 0)
			handler(input, env);
		if (ret == -1)
			break ;
	}
	// char buf[2048];
	// int ret;
	// int exec;
	// pid_t	pid;
	// ft_printf("env: {%r}\n", env, 30, "\n");
	// //char **commands;
	// pid = 0;
	// while (19)
	// {
	// 	//pid = fork();
	// 	ft_printf("$%s %s>", get_env(env[12]), get_env(env[9]));
	// 	if (!~(ret = read(0, buf, sizeof(buf))))
	// 		exit(0);
	// 	if (!pid)
	// 	{
	//
	//
	//
	// 		if (!ft_strcmp(buf, "exit\n"))
	// 		{
	// 			ft_printf("exit done ! code: %d\n", pid);
	// 			exit (0);
	// 			if (pid > 0)
	// 				exit(0);
	// 		}
	// 		else
	// 		{
	// 			exec = 0;
	// 			char *argv[] = { "/bin/ls", "-l", NULL};
	// 			pid = fork();
	// 			exec = execve(argv[0], argv, NULL);
	// 		}
	// 	}
	// 	else if (pid < 0)
	// 	{
	// 		ft_printf("Fork failed to create a new process.\n");
	// 		exit(0);
	// 	}
	//
	// 	wait(&pid);
	// }
	return (0);
}
