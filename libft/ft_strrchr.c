/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:07:53 by aalves            #+#    #+#             */
/*   Updated: 2016/11/07 11:47:11 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (s[i])
	{
		if ((char)c == s[i])
			tmp = (char*)s + i;
		i++;
	}
	if ((char)c == s[i])
		tmp = (char*)s + i;
	return (tmp);
}
