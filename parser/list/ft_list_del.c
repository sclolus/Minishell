/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 04:06:56 by aalves            #+#    #+#             */
/*   Updated: 2016/03/07 00:37:10 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	ft_list_del(t_list_head *link)
{
	link->prev->next = link->next;
	link->next->prev = link->prev;
	link->prev = (void *)0;
	link->next = (void *)0;
}
