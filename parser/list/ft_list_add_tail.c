/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add_tail.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 03:52:48 by aalves            #+#    #+#             */
/*   Updated: 2016/03/07 00:37:12 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	ft_list_add_tail(t_list_head *new, t_list_head *head)
{
	ft_list_add_between(new, head->prev, head);
}
