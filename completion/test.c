/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 01:18:22 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/10 06:58:53 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_completion.h"
#include "libft.h"

void	ft_put_strings(char **strings)
{
	if (!strings)
	{
		ft_putstr("no match");
		return ;
	}
	while (*strings)
	{
		ft_static_put(*strings, ft_strlen(*strings), 0);
		ft_static_put("\n", 1, 0);
		strings++;
	}
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
}

int	main(int argc, char **argv)
{
	uint32_t	i;
	t_ltree		*ltree;
	char		**strings;

	i = 0;
	if (argc > 1)
	{
		ltree = ft_get_ltree_directory();
		strings = ft_get_ltree_suffixes(ltree, argv[1]);
		ft_ltree_put(ltree);
		ft_put_strings(strings);
		
/*		strings = ft_get_matching_filenames(argv[1]);*/
	}
	return (0);
}
