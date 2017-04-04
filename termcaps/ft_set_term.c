/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 00:36:26 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/30 00:46:38 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int32_t		ft_set_term(void)
{	
	char					*name_term = "xterm-256color";
	static struct termios	term;
	static struct termios	default_term;
	static uint32_t			status = 0;

	if (status == 0)
	{
		if (tgetent(NULL, name_term) == -1)
			return (-1);
		if (tcgetattr(0, &term) == -1)
			return (-1);
		if (tcgetattr(0, &default_term) == -1)
			return (-1);
		term.c_lflag &= ~(ICANON);
		term.c_lflag &= ~(ECHO);
		if (tcsetattr(0, TCSADRAIN, &term) == -1)
			return (-1);
		ft_set_insert();
		status = 1;
	}
	else
	{
		ft_unset_insert();
		if (tcsetattr(0, TCSANOW, &default_term) == -1)
			return (-1);
		status = 0;
	}
	return (0);
}
