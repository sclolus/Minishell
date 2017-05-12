/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 02:07:37 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/12 11:53:02 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include "minishell.h"
#include <stdio.h>

int			ft_exec_special_event(t_shenv *shenv, t_string *buf,
							t_list **paste_history, char *command)
{
	t_list							*tmp;

	if ((*(long*)command == '\n' || *(long*)command == 4))
	{
		if (!buf->len)
			return (0);
		if (!(tmp = ft_lstnew(buf->string, buf->len + 1)))
			exit(EXIT_FAILURE);
		ft_lstadd(ft_get_history_list(), tmp);
		ft_move_end_line(buf);
	}
	else if (*((short*)command) == ID_DIRECTION_KEY)
	{
		if (command[2] == ID_HISTORY_DOWN || command[2] == ID_HISTORY_UP)
			ft_get_history(*ft_get_history_list(), command, buf);
		return (1);
	}
	else if (*command == ID_KILL_LINE && (ft_kill_line(buf, paste_history)))
		return (1);
	else if ((*command == ID_YANKING || *(int*)command == ID_HISTORIC_YANKING)
								&& ft_paste_line(buf, command, *paste_history))
		return (1);
	else if (*command == ID_TAB)
		return (ft_completion(buf, shenv));
	return (0);
}

int			ft_exec_term_event(char *command, t_string *buf, t_shenv *shenv)
{
	uint32_t						i;
	static t_list					*paste_history = NULL;
	static const t_term_event		term_events[11] = {
		{ID_MOVE_START_LINE, &ft_move_start_line},
		{ID_MOVE_START_LINE_HOME, &ft_move_start_line},
		{ID_MOVE_END_LINE, &ft_move_end_line},
		{ID_MOVE_END_LINE_END, &ft_move_end_line},
		{ID_MOVE_DOWN_CURSOR, &ft_move_down_cursor},
		{ID_MOVE_UP_CURSOR, &ft_move_up_cursor},
		{ID_DELETE_CHAR, &ft_delete_char},
		{ID_MOVE_LEFT_CURSOR, &ft_move_left_cursor},
		{ID_MOVE_RIGHT_CURSOR, &ft_move_right_cursor},
		{ID_MOVE_PREV_WORD, &ft_move_prev_word},
		{ID_MOVE_NEXT_WORD, &ft_move_next_word}};

	i = -1;
	while (++i < 11)
	{
		if (term_events[i].id == *(int*)command)
		{
			term_events[i].f(buf);
			return (1);
		}
	}
	return (ft_exec_special_event(shenv, buf, &paste_history, command));
}

int32_t		ft_term_line_continuation(char *line)
{
	int32_t							ret;

	if ((ret = ft_is_unbalanced(line)))
	{
		if (ret >= 4)
		{
			if (*ft_get_current_prompt() == DOUBLE_QUOTE)
			    return (0);
			ft_set_and_put_prompt(DOUBLE_QUOTE);
			return (ret);
		}
		else if (ret == 2)
		{
			if (*ft_get_current_prompt() == SINGLE_QUOTE)
			    return (0);
			ft_set_and_put_prompt(SINGLE_QUOTE);
			return (ret);
		}
	}
	else if (ft_is_line_backslash_terminated(line))
	{
		ft_set_and_put_prompt(LINE_CONTINUATION);
		return (1);
	}
	if (*ft_get_current_prompt() != NORMAL_PROMPT && *ft_get_current_prompt() != LINE_CONTINUATION)
	{
	    ft_set_and_put_prompt(*ft_get_current_prompt());
	    return (2);
	}
	return (0);
}

int64_t		ft_termget(char **line, t_shenv *shenv)
{
	static t_string	buf = {256, 0, 0, NULL};
	static char		tmp[8] = "\0\0\0\0\0\0\0\0";

	ft_termget_buf_setup(&buf);
	while (1)
	{
		if ((read(0, tmp, 8)) == -1)
			exit(EXIT_FAILURE);
		if (*(long*)tmp == 3)
			break ;
		if (!ft_exec_term_event(tmp, &buf, shenv))
		{
			if (*(long*)tmp == '\n' || *(long*)tmp == 4)
			{
				if (*(long*)tmp == 4 && !buf.len && *ft_get_current_prompt()
					== NP)
					ft_exit_shell(0);
				break ;
			}
			ft_buf_update(&buf, tmp);
		}
		ft_memset(tmp + 1, 0, 7);
	}
	return (ft_termget_cleanup(tmp, &buf, line));
}

void		ft_append_line(char **line, char **final, uint32_t type)
{
    char		*tmp;
    char		*tmp_str;

    if (!*final)
	*final = ft_strdup(*line);
    else
    {
	tmp = *final;
	if (type)
	{
	    if (!(tmp_str = ft_strjoin(*line, "\n")))
		exit(EXIT_FAILURE);
	    if (!(*final = ft_strjoin_f(*final, tmp_str, 1)))
		exit(EXIT_FAILURE);
	}
	else
	{
	    if (!(*final = ft_strjoin(*final, *line)))
		exit(EXIT_FAILURE);
	}
	free(tmp);
    }

}

uint32_t	ft_termget_complete_line(char **line, t_shenv *shenv)
{
	int64_t							len;
	uint32_t						ret;
	char							*final;

	if ((len = ft_termget(line, shenv)) == -1)
		return (ft_strlen(*line));
	final = NULL;
	while ((ret = ft_term_line_continuation(*line)))
	{
	    if (!final)
		ft_append_line(line, &final, 0);
		if (ret != 1)
		{
			len += ft_termget(line, shenv) + 1;
			ft_append_line(line, &final, 1);
			continue ;
		}
		len += ft_termget(line, shenv);
		ft_append_line(line, &final, 0);
	}
	if (final)
	    *line = final;
	return (len);
}
