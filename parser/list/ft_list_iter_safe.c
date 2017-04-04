/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_iter_safe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 05:16:10 by aalves            #+#    #+#             */
/*   Updated: 2016/03/07 00:37:05 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	ft_list_iter_safe(t_list_head *head, void (*f) (t_list_head *))
{
	t_list_head *entry;
	t_list_head *next;

	entry = head->next;
	while (entry != head)
	{
		next = entry->next;
		f(entry);
		entry = next;
	}
}
