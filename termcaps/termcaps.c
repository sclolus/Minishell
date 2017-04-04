/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 02:07:37 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/04 05:10:07 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include "minishell.h"
#include <stdio.h>

int	ft_exec_special_event(t_list **history, t_string *buf
						  , t_list **paste_history, char *command)
{
	t_list							*tmp;

	if (*command == '\n')
	{
		if (!(tmp = ft_lstnew(buf->string, buf->len)))
			exit (EXIT_FAILURE);
		ft_lstadd(history, tmp);
		ft_move_end_line(buf);
	}
	else if (*((short*)command) == ID_DIRECTION_KEY)
	{
		if (command[2] == ID_HISTORY_DOWN || command[2] == ID_HISTORY_UP)
			ft_get_history(*history, command, buf);
		return (1);
	}
	else if (*command == ID_KILL_LINE)
	{
		ft_kill_line(buf, paste_history);
		return (1);
	}
	else if (*command == ID_YANKING || *(int*)command == ID_HISTORIC_YANKING)
	{
		ft_paste_line(buf, command, *paste_history);
		return (1);
	}
	return (0);
}

int	ft_exec_term_event(char	*command, t_string *buf)
{
	uint32_t						i;
//	static t_list					*history = NULL;
	static t_list					*paste_history = NULL;
	static const t_term_event		term_events[7] = {
		{ID_MOVE_START_LINE, &ft_move_start_line},
		{ID_MOVE_END_LINE, &ft_move_end_line},
		{ID_MOVE_DOWN_CURSOR, &ft_move_down_cursor},
		{ID_MOVE_UP_CURSOR, &ft_move_up_cursor},
		{ID_DELETE_CHAR, &ft_delete_char},
		{ID_MOVE_LEFT_CURSOR, &ft_move_left_cursor},
		{ID_MOVE_RIGHT_CURSOR, &ft_move_right_cursor}};

	i = 0;
	while (i < 7)
	{
		if (term_events[i].id == *(int*)command)
		{
			term_events[i].f(buf);
			return (1);
		}
		i++;
	}
	return (ft_exec_special_event(ft_get_history_list(), buf, &paste_history, command));
}

int32_t	ft_term_line_continuation(char *line)
{
	int32_t		ret;

	if ((ret = ft_is_unbalanced(line))
		|| ft_is_line_backslash_terminated(line))
	{
		if (ret >= 4)
		{
			ft_putstr("dquote>");
			return (ret);
		}
		else if (ret == 2)
		{
			ft_putstr("quote>");
			return (ret);
		}
		else
		{
			ft_putstr(">");
			return (1);
		}
	}
	return (0);
}

uint32_t	ft_termget(char **line)
{
	static t_string	buf = {256, 0, 0, NULL};
	static char		tmp[8] = "\0\0\0\0\0\0\0\0";

	buf.len = 0;
	buf.offset = 0;
	if (buf.string == NULL)
		if (!(buf.string = ft_strnew(255)))
			exit(EXIT_FAILURE);
	*buf.string = 0;
	while (1)
	{
		if (read(0, tmp, 8) == -1)
			exit(EXIT_FAILURE);
		if (!ft_exec_term_event(tmp, &buf))
		{
			if (*tmp == '\n')
			{
				ft_putchar('\n');
				break;
			}
			if (ft_isprint(*tmp))
			{
				ft_putchar(*tmp);
				tmp[1] = 0;
				if (buf.offset == buf.len)
					ft_t_string_concat(&buf, tmp);
				else
					ft_t_string_insert(&buf, tmp);
			}
		}
		ft_memset(tmp + 1, 0, 3);
	}
	*line = buf.string;
	return (buf.len);
}

uint32_t	ft_termget_complete_line(char **line)
{
	uint32_t	len;
	uint32_t	ret;
	char		*line_tmp;

	len = ft_termget(line);
	while ((ret = ft_term_line_continuation(*line)))
	{
		if (ret != 1)
		{
			if (!(line_tmp = ft_strnew(len + 1)))
				exit(EXIT_FAILURE);
			ft_memcpy(line_tmp, *line, len);
			line_tmp[len] = '\n';
			len += ft_termget(line) + 1;
			if (!(*line = ft_strjoin_f(line_tmp, *line, 0)))
				exit(EXIT_FAILURE);
			continue ;
		}
		if (!(line_tmp = ft_strnew(len)))
			exit(EXIT_FAILURE);
		ft_memcpy(line_tmp, *line, len);
		len += ft_termget(line);
		if (!(*line = ft_strjoin_f(line_tmp, *line, 0)))
			exit(EXIT_FAILURE);
	}
	return (len);
}
