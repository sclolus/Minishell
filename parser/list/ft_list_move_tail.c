/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_move_tail.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 04:17:06 by aalves            #+#    #+#             */
/*   Updated: 2016/03/07 00:36:59 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	ft_list_move_tail(t_list_head *to_move, t_list_head *head)
{
	ft_list_del(to_move);
	ft_list_add_tail(to_move, head);
}
