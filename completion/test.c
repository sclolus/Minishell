/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 01:18:22 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/08 03:21:15 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_completion.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	uint32_t	i;
	t_ltree		*ltree;

	i = 1;
	if (argc > 2)
	{
		ltree = ft_get_ltree_dictionary(argc - 2, argv + 1);
		ft_putnbr(ft_ltree_search(ltree, argv[argc - 1]));
		ft_free_ltree(ltree);
		ltree = NULL;
	}
	return (0);
}
