/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 17:38:56 by aalves            #+#    #+#             */
/*   Updated: 2016/11/06 16:47:25 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (*s1 == *s2 && *s1 && n)
		return (ft_strncmp((char*)s1 + 1, (char*)s2 + 1, n - 1));
	else if (!n)
		return (0);
	else
		return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
