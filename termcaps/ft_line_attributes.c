/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_attributes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 12:21:35 by aalves            #+#    #+#             */
/*   Updated: 2017/05/12 12:25:01 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

t_line_attributes	*ft_get_line_attributes(void)
{
	static t_line_attributes	attributes;

	return (&attributes);
}
