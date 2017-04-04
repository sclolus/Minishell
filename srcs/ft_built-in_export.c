/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built-in_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 03:23:56 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/30 03:38:52 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint32_t	ft_export(t_env *env, char **var)
{
	static char	buf[4096];
	uint32_t	name_len;
	uint32_t	value_len;
	char		**tmp;
	uint32_t	i;

	i = 0;
	name_len = ft_strlen(var[0]);
	value_len = ft_strlen(var[1]);
	if (name_len + value_len + 1 > 4096)
	{
		ft_putstr_fd("Max Local Variable length reached", 2);
		return (-1);
	}
	ft_memcpy(buf, var[0], name_len);
	buf[name_len] = '=';
	ft_memcpy(buf + name_len + 1, var[1], value_len);
	if (!(tmp = (char**)malloc(sizeof(char*) * (env->variable_count + 2))))
		exit(EXIT_FAILURE);
	tmp[env->variable_count + 1] = NULL;
	while (i < env->variable_count)
	{
		tmp[i] = env->env[i];
		i++;
	}
	if (!(tmp[i] = ft_strdup(buf)))
		exit(EXIT_FAILURE);
	free(env->env);
	env->env = tmp;
	return (0);
}
