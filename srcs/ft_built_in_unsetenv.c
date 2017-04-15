/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built-in_unsetenv.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 03:39:44 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/15 05:45:41 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**ft_find_env_value(t_env *env, char *variable)
{
	uint32_t	i;
	uint32_t	u;

	i = 0;
	u = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	while (env->env[u])
	{
		if (!ft_strncmp(variable, env->env[u], i) && env->env[u][i] == '=')
			return (env->env + u);
		else
			u++;
	}
	return (NULL);
}

static int32_t	ft_delete_env(char **argv, uint32_t count, t_env *env)
{
	uint32_t	i;
	char		**tmp;
	char		**tmp_env;

	i = 0;
	while (i < count)
	{
		if (!(tmp = ft_find_env_value(env, argv[i])))
			return (ft_error(3, (char*[]){"unsetenv: "
						, argv[i], ": environnement variable not found"}, 1));
		else
		{
			if (!(tmp_env = (char**)malloc(sizeof(char*)
										* env->variable_count)))
				exit(EXIT_FAILURE);
			tmp_env[env->variable_count - 1] = NULL;
			ft_memcpy(tmp_env, env->env, (tmp - env->env) * sizeof(char**));
			ft_memcpy(tmp_env + (tmp - env->env), tmp + 1
				, (env->variable_count - (tmp - env->env)) * sizeof(char**));
			free(*tmp);
			free(env->env);
			env->env = tmp_env;
		}
		i++;
	}
	return (0);
}

static uint32_t	ft_count_values(char **argv)
{
	uint32_t	i;

	i = 1;
	while (argv[i])
		i++;
	return (i - 1);
}

int32_t			ft_built_in_unsetenv(char **argv, t_env *env)
{
	uint32_t	count;

	if (!(count = ft_count_values(argv)))
		return (ft_error(1, (char*[]){"unsetenv: not enough arguments"}, 1));
	return (ft_delete_env(argv + 1, count, env));
}
