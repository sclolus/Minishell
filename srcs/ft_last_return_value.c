/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_return_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 10:06:21 by aalves            #+#    #+#             */
/*   Updated: 2017/05/15 10:08:41 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint32_t	*ft_get_last_return_value(void)
{
	static uint32_t	last_return_value = 0;

	return (&last_return_value);
}
