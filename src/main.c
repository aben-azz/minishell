/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/21 05:36:54 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
int lol(void)
{
	exit(0);
	return (1);
}
int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char buf[2048];
	int ret;
	int exec;
	pid_t	pid;
	char *string;
	char **cmd;

	while (19)
	{
		pid = fork();
		if (!pid)
		{
			ft_dprintf(1, PREFIX);
			if (!~(ret = read(0, buf, sizeof(buf))))
				exit(0);
			if (!ft_strcmp(buf, "exit\n"))
			{
				ft_printf("ok: |%s|, %d\n", buf, ft_strcmp(buf, "exit\n"));
				exit(0);
			}
			else
			{
				ft_printf("pas ok: |%s|, %d\n", buf, ft_strcmp(buf, "exit\n"));
				exec = 0;
				cmd = ft_strsplit(buf, ' ');
				string = ft_strjoin("/bin/", cmd[0]);
				cmd[1][ft_strlen(cmd[0]) - 1] = '\0';
				ft_printf("cmd la vaut: |%s|\n", cmd[0]);
				++cmd;
				ft_printf("cmd la vaut: |%r|\n", cmd, 2, "-");
				exec = execve(string, cmd, NULL);
				free(string);
				if (~exec)
					ft_dprintf(1, "fail\n");
				else
					ft_dprintf(1, "success\n");
			}
		}
		else if (pid < 0)
		{
			ft_printf("Fork failed to create a new process.");
			exit(0);
		}
		wait(&pid);
	}
	return (0);
}
