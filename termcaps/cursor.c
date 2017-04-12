/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 13:51:53 by aalves            #+#    #+#             */
/*   Updated: 2017/04/12 20:14:02 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void		ft_move_up_cursor(t_string *buf)
{
	char					*res;
	static struct winsize	window;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	if ((buf->offset + 10) / window.ws_col)
	{
		if ((buf->offset + 10) % window.ws_col < 10)
			ft_move_start_line(buf);
		else
		{
			buf->offset -= window.ws_col;
			res = tgetstr("up", NULL);
			tputs(res, 1, &ft_putterm);
		}
	}
	else
		ft_putchar(7);
}

void		ft_move_down_cursor(t_string *buf)
{
	static struct winsize	window;
	uint64_t				i;

	i = 0;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	while (i++ < window.ws_col)
		ft_move_right_cursor(buf);
}

void		ft_move_left_cursor(t_string *buf)
{
	char	*res;

	if (buf->offset > 0)
	{
		buf->offset--;
		res = tgetstr("le", NULL);
		tputs(res, 1, &ft_putterm);
	}
	else
		ft_putchar(7);
}

void		ft_move_right_cursor(t_string *buf)
{
	char					*res;
	static struct winsize	window;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	if (buf->offset < buf->len)
	{
		if (0 == (buf->offset + 10) % window.ws_col)
		{
			res = tgetstr("do", NULL);
			buf->offset++;
		}
		else
		{
			res = tgetstr("nd", NULL);
			buf->offset++;
		}
		tputs(res, 1, &ft_putterm);
	}
	else
		ft_putchar(7);
}
