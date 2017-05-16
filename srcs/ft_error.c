/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 04:57:34 by aalves            #+#    #+#             */
/*   Updated: 2017/04/26 11:33:18 by aalves           ###   ########.fr       */
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
	ft_unset_term();
	ft_unset_insert();
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
