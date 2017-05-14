/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_completion_tab.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 00:23:47 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/14 00:24:29 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_new_completion.h"

void	ft_free_completion_tab(char **tab)
{
	uint32_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
