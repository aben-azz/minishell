/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 06:41:49 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/11 23:13:39 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strreplace(char *src, char *from, char *to)
{
	char		*f;
	char		*str;
	size_t		len1;
	size_t		len2;

	str = NULL;
	if ((f = strstr(src, from)))
	{
		len1 = f - src;
		len2 = ft_strlen(f + ft_strlen(from));
		str = ft_memalloc(sizeof(char) * (len1 + ft_strlen(to) + len2 + 1));
		if (str)
		{
			str = ft_strncpy(str, src, len1);
			str = ft_strcat(str, to);
			str = ft_strcat(str, f + ft_strlen(from));
		}
	}
	return (str);
}
