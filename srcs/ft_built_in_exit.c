/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 16:00:44 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/16 16:48:23 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t		ft_built_in_exit(char **argv, t_shenv *shenv)
{
	int32_t		exit_status;
	uint32_t	i;

	i = 0;
	ft_putendl("exit");
	exit_status = 0;
	ft_set_term();
	if (shenv)
		;
	if (argv[1])
	{
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
				ft_error_exit(3, (char*[]){"exit: "
							, argv[1], ": numeric argument required"}, 255);
			i++;
		}
		exit_status = ft_atoi(argv[1]);
	}
	exit(POSIX_EXIT_STATUS(exit_status));
	return (-1);
}