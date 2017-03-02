/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 03:22:07 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/02 06:29:55 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	ft_move_left_cursor(t_cursor *cursor)
{
	char	*res;

	if (cursor->pos.x > 0)
	{
		cursor->pos.x--;
		res = tgetstr("le", NULL);
		tputs(res, 1, &ft_putterm);
	}
}

void	ft_move_right_cursor(t_cursor *cursor)
{
	char	*res;

	if (cursor->pos.x == 80)
		res = tgetstr("do", NULL);
	else
		cursor->pos.x++;
	res = tgetstr("nd", NULL);
	tputs(res, 1, &ft_putterm);
}
// ctrl + whatever
void	ft_move_up_cursor(t_cursor *cursor)
{
	char	*res;
	
	cursor->pos.x--;
	res = tgetstr("up", NULL);	
	tputs(res, 1, &ft_putterm);
}

void	ft_move_down_cursor(t_cursor *cursor)
{
	char	*res;

	cursor->pos.x--;
	res = tgetstr("do", NULL);
	tputs(res, 1, &ft_putterm);
}

void	ft_move_start_line(t_cursor *cursor)
{
	char	*res;

//	cursor->pos.x = 0;
	cursor->pos.y = 0;
	while (cursor->pos.x > 0)
		ft_move_left_cursor(cursor);
//	res = tgetstr("cr", NULL);

}

void	ft_screen_clear(void)
{
	char	*res;

	res = tgetstr("cl", NULL);
	tputs(res, 1, &ft_putterm);
}

void	ft_delete_char(t_cursor *cursor)
{
	char	*res;

	if (cursor->pos.x > 0)
	{
		ft_move_left_cursor(cursor);
		res = tgetstr("dc", NULL);
		tputs(res, 1, &ft_putterm);
	}
}

void	ft_kill_line(t_cursor *cursor)
{
	char	*res;

	res = tgetstr("ce", NULL);
	tputs(res, 1, &ft_putterm);
}

void	ft_set_insert(void)
{
	char	*res;

	res = tgetstr("im", NULL);
	tputs(res, 1, &ft_putterm);
}

void	ft_unset_insert(void)
{
	char	*res;

	res = tgetstr("em", NULL);
	tputs(res, 1, &ft_putterm);
}

t_string	*ft_t_string_concat(t_string *string, char *str)
{
	uint64_t	total_len;
	uint64_t	str_len;
	char		*tmp;

	tmp = NULL;
	if (!str || !string)
		return (NULL);
	str_len = ft_strlen(str);
	total_len = string->len + str_len;
	if (total_len >= string->capacity)
	{
		if (!(tmp = ft_strnew(string->capacity * 2)))
			exit (EXIT_FAILURE);
		string->capacity *= 2;
		ft_strcpy(tmp, string->string);
		free(string->string);
		string->string = tmp;
		return (ft_t_string_concat(string, str));
	}
	else
	{
		ft_strcat(string->string, str);
		string->len += str_len;
	}
	return (string);
}
