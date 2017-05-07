/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 16:00:44 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/07 02:36:55 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t		ft_built_in_exit(char **argv, t_shenv *shenv)
{
	int32_t		exit_status;
	uint32_t	i;

	i = 0;
	ft_putendl("exit");
	(void)shenv;
	exit_status = 0;
	if (argv[2])
		return (ft_error(1, (char*[]){"exit: Too many arguments"}, 2));
	if (argv[1])
	{
		while (argv[1][i])
			if (!ft_isdigit(argv[1][i]))
			{
				ft_unset_term();
				ft_unset_insert();
				ft_error_exit(3, (char*[]){"exit: "
					, argv[1], ": numeric argument required"}, 255);
			}
		exit_status = ft_atoi(argv[1]);
	}
	ft_exit_shell(0);
	return (-1);
}
