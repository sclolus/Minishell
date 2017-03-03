/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 13:55:17 by aalves            #+#    #+#             */
/*   Updated: 2017/03/03 13:55:37 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void		ft_screen_clear(void)
{
	char	*res;

	res = tgetstr("cl", NULL);
	tputs(res, 1, &ft_putterm);
}

void		ft_set_am(void)
{
	char	*res;

	res = tgetstr("co", NULL);
	tputs(res, 1, &ft_putterm);
}

void		ft_set_insert(void)
{
	char	*res;

	res = tgetstr("im", NULL);
	tputs(res, 1, &ft_putterm);
}

void		ft_unset_insert(void)
{
	char	*res;

	res = tgetstr("em", NULL);
	tputs(res, 1, &ft_putterm);
}
