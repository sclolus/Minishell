/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built-in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 07:46:43 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/05 17:00:21 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	ft_built_in(char **argv, t_env *env)
{
	uint32_t	i;
	static const t_built_in	f_built_in[BUILT_IN_COUNT] = {
		{"cd", NULL},
		{"echo", &ft_built_in_echo},
		{"exit", &ft_built_in_exit},
		{"env", NULL},
		{"setenv", NULL},
		{"unsetenv", NULL},
		{"history", &ft_built_in_history},
		{"unset", NULL},
		{"export", NULL}};

	i = 0;
	while (i < BUILT_IN_COUNT)
	{
		if (!ft_strcmp(argv[0], f_built_in[i].id))
			return (f_built_in[i].f(argv, env));
		i++;
	}
	return (EXIT_ILLEGAL_CMD);
}
