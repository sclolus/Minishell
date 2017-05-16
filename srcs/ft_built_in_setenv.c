/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built-in_setenv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 03:31:37 by aalves            #+#    #+#             */
/*   Updated: 2017/04/16 18:14:57 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t				ft_built_in_setenv(char **argv, t_shenv *shenv)
{
	uint32_t	i;

	i = 1;
	if (!argv || !shenv)
		return (1);
	while (argv[i])
	{
		ft_modify_var(shenv, argv[i]);
		ft_set_var_to_export(shenv, argv[i]);
		i++;
	}
	return (0);
}
