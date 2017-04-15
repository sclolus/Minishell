/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 05:47:06 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/15 01:05:41 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


int main(int argc, char **argv)
{
	uint32_t	i;

	char	*string = ft_strdup("salut les gens");
	i = 0;
	while (i < 10)
	{
		ft_static_put(string, ft_strlen(string), 0);
		i++;
	}
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
	return (0);
}
