/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 16:58:58 by aalves            #+#    #+#             */
/*   Updated: 2017/05/16 07:19:42 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	ft_built_in_echo(char **argv, t_shenv *shenv)
{
	uint32_t	i;
	uint32_t	argc;
	uint8_t		flags;

	i = 1;
	flags = 0;
	argc = 0;
	if (!(shenv))
		;
	while (argv[argc])
		argc++;
	if (argc >= 2 && !ft_strcmp(argv[1], "-n"))
	{
		flags = 1;
		i++;
	}
	while (i < argc)
	{
		ft_putstr(argv[i++]);
		if (i < argc)
			ft_putchar(' ');
	}
	if (!flags)
		ft_putchar('\n');
	return (0);
}
