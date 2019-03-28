/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 06:13:46 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/28 06:19:41 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *str_replace(char *orig, char *rep, char *with) {
	char *result;
	char *ins;
	char *tmp;
	int len_rep;
	int len_with;
	int len_front;
	int count;

	if (!orig || !rep)
		return (NULL);
	len_rep = ft_strlen(rep);
	if (len_rep == 0)
		return (NULL);
	if (!with)
		with = "";
	len_with = ft_strlen(with);
	ins = orig;
	// count = 0;
	// while (tmp = ft_strstr(ins, rep))
	// {
	// 	ins = tmp + len_rep;
	// 	++count
	// }
	for (count = 0; tmp = ft_strstr(ins, rep); ++count) {
		ins = tmp + len_rep;
	}

	tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

	if (!result)
		return (NULL);
	while (count--)
	{
		ins = ft_strstr(orig, rep);
		len_front = ins - orig;
		tmp = ft_strncpy(tmp, orig, len_front) + len_front;
		tmp = ft_strcpy(tmp, with) + len_with;
		orig += len_front + len_rep;
	}
	ft_strcpy(tmp, orig);
	return result;
}
