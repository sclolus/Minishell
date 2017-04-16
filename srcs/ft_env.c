/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 23:23:12 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/16 06:10:54 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t		ft_shenv_get_env_count(t_shenv *shenv)
{
	uint32_t	i;
	uint32_t	count;

	i = 0;
	count = 0;
	while (i < shenv->count)
	{
		if (shenv->attr[i])
			count++;
		i++;
	}
	return (count);
}

void		ft_free_t_env(t_env *env)
{
	uint32_t	i;

	i = 0;
	while (i < env->variable_count)
	{
		free(env->env[i]);
		i++;
	}
	free(env->env);
	free(env);
}

t_env		*ft_get_env(t_shenv *shenv)
{
	uint32_t	i;
	uint32_t	u;
	uint32_t	count;
	char		**env;
	t_env		*environ;

	if (!(count = ft_shenv_get_env_count(shenv)))
		return (NULL);
	if (!(environ = (t_env*)malloc(sizeof(t_env)))
		|| !(env = (char**)ft_memalloc(sizeof(char*) * (count + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	u = 0;
	while (i < shenv->count)
	{
		if (shenv->attr[i] && ft_strchr(shenv->var[i], '='))
			if (!(env[u++] = ft_strdup(shenv->var[i])))
				exit(EXIT_FAILURE);
		i++;
	}
	environ->variable_count = count;
	environ->env = env;
	return (environ);
}
