/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 13:53:21 by aalves            #+#    #+#             */
/*   Updated: 2017/04/17 08:03:27 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void		ft_move_start_line(t_string *buf)
{
	while (buf->offset > 0)
		ft_move_left_cursor(buf);
}

void		ft_move_end_line(t_string *buf)
{
	while (buf->offset < buf->len)
		ft_move_right_cursor(buf);
}

void		ft_erase_line(void)
{
	char	*res;

	res = tgetstr("dl", NULL);
	tputs(res, 1, &ft_putterm);
}

void		ft_kill_line(t_string *buf, t_list **paste_history)
{
	char			*res;
	static t_list	*paste_base = NULL;
	t_list			*tmp;

	if (!paste_base)
		paste_base = *paste_history;
	res = tgetstr("cd", NULL);
	tputs(res, 1, &ft_putterm);
	if (!(tmp = ft_lstnew(buf->string + buf->offset,
				ft_strlen(buf->string + buf->offset))))
		exit(EXIT_FAILURE);
	ft_strcpy(tmp->content, buf->string + buf->offset);
	ft_lstadd(paste_history, tmp);
	if (paste_base)
	{
		tmp->prev = paste_base;
		tmp->next->prev = tmp;
		paste_base->next = tmp;
	}
	buf->string[buf->offset] = '\0';
	buf->len = buf->offset;
}

void		ft_paste_line(t_string *buf, char *command, t_list *paste_history)
{
	char			*tmp;
	static t_list	*static_history = NULL;
	static t_list	*history_base = NULL;
	static t_list	*current_yanking = NULL;

	if (history_base != paste_history)
	{
		history_base = paste_history;
		static_history = paste_history;
		current_yanking = paste_history;
	}
	tmp = NULL;
	if (history_base == NULL)
		return ;
	else if (*command == ID_YANKING)
	{
		if (!current_yanking->content)
			return ;
		tmp = current_yanking->content;
	}
	else if (*(int*)command == ID_HISTORIC_YANKING)
	{
		if (!static_history->content)
			return ;
		ft_explore_paste_history(buf, &static_history, &history_base, &current_yanking);
	}
	ft_t_string_insert(buf, tmp);
	ft_putstr(tmp);
}
