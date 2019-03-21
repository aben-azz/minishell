/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:51:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/21 03:46:32 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char buf[2048];
	int cc;

	while (19)
	{
		ft_dprintf(1, PREFIX);
		cc = read(0, buf, sizeof(buf));
		//ft_dprintf(1, "|%s| => ret:|%d|\n", buf, ft_strcmp(buf, "exit"));
		if (!ft_strcmp(buf, "exit\n"))
			exit(0);
	}
	return (0);
}
