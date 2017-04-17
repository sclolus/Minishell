/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 20:47:23 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/17 05:07:22 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	ft_move_prev_word(t_string *buf)
{
	t_bool	in_word;

	if (buf->offset == 0)
	{
		ft_putchar(7);
		return ;
	}
	if (ft_isalnum(buf->string[buf->offset - 1])
		|| ft_is_quoted(buf->string, buf->offset - 1))
		in_word = 1;
	else
		in_word = 0;
	while (buf->offset - 1 >= 0)
	{
		if (!ft_isalnum(buf->string[buf->offset - 1]) && in_word)
			break ;
		else if (ft_isalnum(buf->string[buf->offset - 1])
			|| ft_is_quoted(buf->string, buf->offset - 1))
			in_word = 1;
		else
			in_word = 0;
		ft_move_left_cursor(buf);
	}
}

void	ft_move_next_word(t_string *buf)
{
	t_bool	in_word;

	if (buf->offset == buf->len)
	{
		ft_putchar(7);
		return ;
	}
	if (ft_isalnum(buf->string[buf->offset])
		|| ft_is_quoted(buf->string, buf->offset))
		in_word = 1;
	else
		in_word = 0;
	while (buf->offset < buf->len)
	{
		if ((ft_isalnum(buf->string[buf->offset]) && !in_word)
			|| (in_word && !ft_isalnum(buf->string[buf->offset])))
			break ;
		else if (ft_isalnum(buf->string[buf->offset])
			|| ft_is_quoted(buf->string, buf->offset))
			in_word = 1;
		else
			in_word = 0;
		ft_move_right_cursor(buf);
	}
}

void	ft_termcaps_putstr(t_string *buf, char *str)
{
	static struct winsize	window;
	char					*res;
	uint32_t				len;
	uint32_t				len_print;
	uint32_t				len_to_restore;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	len = ft_strlen(str);
	len_print = 0;
	while (len > len_print)
	{
		if (buf->offset / window.ws_col == 0)
			len_to_restore = window.ws_col - (buf->offset + PROMPT_LEN);
		else
			len_to_restore = window.ws_col - buf->offset;
		write(1, str + len_print, (len - len_print) % len_to_restore);
		len_print += (len - len_print) % len_to_restore;
		if (len > len_print)
		{
			res = tgetstr("do", NULL);
			tputs(res, 1, &ft_putterm);
		}
	}
	len_print = 0;
	while (len > len_print)
	{
		if (buf->offset / window.ws_col == 0)
			len_to_restore = window.ws_col - (buf->offset + PROMPT_LEN);
		else
			len_to_restore = window.ws_col - buf->offset;
		write(1, buf->string + buf->offset + len_print, (len - len_print) % len_to_restore);
		len_print += (len - len_print) % len_to_restore;
		res = tgetstr("do", NULL);
		tputs(res, 1, &ft_putterm);
	}
}
