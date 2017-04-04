/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_iter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 04:49:41 by aalves            #+#    #+#             */
/*   Updated: 2016/03/07 00:37:07 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	ft_list_iter(t_list_head *head, void (*f) (t_list_head *))
{
	t_list_head *entry;

	entry = head->next;
	while (entry != head)
	{
		f(entry);
		entry = entry->next;
	}
}
