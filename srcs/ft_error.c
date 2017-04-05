/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 04:57:34 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/05 07:37:43 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_exit(uint32_t n, char **str, int32_t exit_status)
{
	uint32_t	i;

	i = 0;
	ft_putstr_fd(SHELL_NAME, 2);
	while (i < n)
	{
		ft_putstr_fd(str[i], 2);
		i++;
	}
	ft_putstr_fd("\n", 2);
	exit(exit_status);
}

int32_t	ft_error(uint32_t n, char **str, int32_t return_status)
{
	uint32_t	i;

	i = 0;
	ft_putstr_fd(SHELL_NAME, 2);
	while (i < n)
	{
		ft_putstr_fd(str[i], 2);
		i++;
	}
	ft_putstr_fd("\n", 2);
	return (return_status);
}
