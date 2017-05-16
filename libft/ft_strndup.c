/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 04:58:30 by aalves            #+#    #+#             */
/*   Updated: 2017/05/13 23:08:55 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, uint32_t len)
{
	char	*tmp;

	if (!(tmp = ft_strnew(len)))
		exit(EXIT_FAILURE);
	ft_memcpy(tmp, str, len);
	return (tmp);
}
