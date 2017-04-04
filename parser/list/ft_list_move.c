/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 04:12:19 by aalves            #+#    #+#             */
/*   Updated: 2016/03/07 00:37:03 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list.h>

void	ft_list_move(t_list_head *to_move, t_list_head *head)
{
	ft_list_del(to_move);
	ft_list_add(to_move, head);
}
