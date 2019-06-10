/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:23:39 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/10 13:50:45 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_expansion_printable(char *s, int dollar_index, int i)
{
	return (!((s[dollar_index - 1] && s[dollar_index - 1] == '\'') &&
			(s[i] && s[i] == '\'')));
}

void	get_expansion(char *str, char *act_env, int length, char **replaced)
{
	char	*env;
	char	*env2;
	char	*copy;

	env = get_env(act_env + 1);
	if ((env2 = get_env(act_env + 1 + length)))
	{
		ft_strdel(&env2);
		if (!length)
			copy = ft_strreplace(str, act_env, env);
		else
			copy = ft_strreplace(str, act_env,
					ft_itoa((int)ft_strlen(env)));
	}
	else if (length)
		copy = ft_strreplace(str, act_env, "0");
	else
		copy = ft_strreplace(str, act_env, "");
	*replaced = ft_strdup(copy);
	ft_strdel(&copy);
	ft_strdel(&env);
}

void	set_variable(int *i, char *string, int dollar_index)
{
	i[0] = dollar_index + 1;
	i[1] = 0;
	if (string[i[0]] == '#')
	{
		i[1] = 1;
		i[0]++;
	}
	while (i[0] < (int)ft_strlen(string) && string[i[0]] && (string[i[0]] == '_'
	|| ft_isalpha(string[i[0]])))
		i[0]++;
}

char	*expansion_dollar(char *string)
{
	int		il[2];
	int		dollar_index;
	char	*replaced;
	char	*act_env;

	if (!string || (string && !(replaced = ft_strdup(string))))
	{
		ft_strdel(&replaced);
		return (NULL);
	}
	if (!~(dollar_index = ft_indexof(string, '$')))
	{
		ft_strdel(&replaced);
		return (ft_strdup(string));
	}
	set_variable(il, string, dollar_index);
	if (is_expansion_printable(string, dollar_index, il[0]))
	{
		act_env = ft_substr(string, dollar_index, il[0]);
		ft_strdel(&replaced);
		get_expansion(string, act_env, il[1], &replaced);
		ft_strdel(&act_env);
	}
	return (replaced);
}
