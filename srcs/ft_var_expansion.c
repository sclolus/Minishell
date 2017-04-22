/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 06:23:22 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/22 06:49:59 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static uint32_t	ft_get_var_name_len(char *var_name)
{
	uint32_t	i;

	i = 0;
	while (var_name[i])
	{
		if (!ft_strchr(CHARSET_VAR_NAME, var_name[i]))
			return (i - 1);
		i++;
	}
	return (i);
}

static char		*ft_get_var_name(char *var_name)
{
	static char	buf[MAX_VAR_NAME];
	uint32_t	len;

	len = ft_get_var_name_len(var_name);
	ft_memcpy(buf, var_name, len);
	buf[len] = '\0';
	return (buf);
}

void			ft_var_expansion(char **word, t_shenv *shenv)
{
	char		*tmp;
	char		*var_name;
	char		*var_value;
	uint32_t	i;
	uint32_t	len;

	i = 0;
	while (word[0][i])
	{
		if (word[0][i] == '$' && ft_is_quoted(*word, i) != 1)
		{
			tmp = *word;
			var_name = ft_get_var_name(word[0] + i + 1);
			len = ft_strlen(var_name);
			if (!(var_value = *ft_find_var(shenv, var_name)))
			{
				i++;
				continue;
			}
			*word = ft_strreplace(tmp, i
								  , i + len + 1, var_value + len + 1);
			//		free(tmp);
		}
		i++;
	}
}

