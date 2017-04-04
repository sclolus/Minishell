/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add_between.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 03:46:32 by aalves            #+#    #+#             */
/*   Updated: 2016/03/07 00:37:14 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	ft_list_add_between(t_list_head *new, t_list_head *prev,
							t_list_head *next)
{
	new->prev = prev;
	new->next = next;
	prev->next = new;
	next->prev = new;
}
