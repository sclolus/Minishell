/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built-in_setenv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 03:31:37 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/16 07:02:37 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t				ft_built_in_setenv(char **argv, t_shenv *shenv)
{
	uint32_t	i;
	uint32_t	count;

	i = 1;
	if (!argv || !env)
		return (1);
	while (argv[i])
	{
		ft_modify_var(argv[i], shenv);
		ft_set_var_to_export(shenv, argv[i]);
		i++;
	}
	return (0);
}
