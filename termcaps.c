/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 03:22:07 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/03 09:47:28 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	ft_move_left_cursor(t_string *buf)
{
	char	*res;

	if (buf->offset > 0)
	{
		buf->offset--;
		res = tgetstr("le", NULL);
		tputs(res, 1, &ft_putterm);
	}
}

void	ft_move_right_cursor(t_string *buf)
{
	char	*res;
	static struct winsize	window;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	if (buf->offset < buf->len)
	{
		if (window.ws_col == buf->offset + 10)
			res = tgetstr("do", NULL);
		else
			res = tgetstr("nd", NULL);
		buf->offset++;
		tputs(res, 1, &ft_putterm);
	}
}
// ctrl + whatever
void	ft_move_up_cursor(t_string *buf)
{
	char	*res;
	
	res = tgetstr("up", NULL);	
	tputs(res, 1, &ft_putterm);
}

void	ft_move_down_cursor(t_string *buf)
{
	char	*res;

	res = tgetstr("do", NULL);
	tputs(res, 1, &ft_putterm);
}

void	ft_move_start_line(t_string *buf)
{
	char	*res;

	while (buf->offset > 0)
		ft_move_left_cursor(buf);
//	res = tgetstr("cr", NULL);

}

void	ft_move_end_line(t_string *buf)
{
	char	*res;

	while (buf->offset < buf->len)
		ft_move_right_cursor(buf);
}

void	ft_screen_clear(void)
{
	char	*res;

	res = tgetstr("cl", NULL);
	tputs(res, 1, &ft_putterm);
}

void	ft_delete_char(t_string *buf)
{
	char	*res;

	if (buf->offset >= 0)
	{
		ft_move_left_cursor(buf);
		ft_strcpy(buf->string + buf->offset, buf->string + buf->offset + 1);
		res = tgetstr("dc", NULL);
		tputs(res, 1, &ft_putterm);
	}
}

void	ft_print_history_len(t_list *list)
{
	while (list)
	{
		ft_putnbr(ft_strlen(list->content));
		ft_putchar(' ');
		ft_putendl(list->content);
		list = list->next;
	}
}

void	ft_kill_line(t_string *buf, t_list **paste_history)
{
	char			*res;
	static t_list	*paste_base = NULL;
	t_list			*tmp;

	if (!paste_base)
		paste_base = *paste_history;
	res = tgetstr("ce", NULL);
	tputs(res, 1, &ft_putterm);
	if (!(tmp = ft_lstnew(buf->string + buf->offset
						  , ft_strlen(buf->string + buf->offset))))
		exit (EXIT_FAILURE);
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

void	ft_paste_line(t_string *buf, char *command, t_list *paste_history)
{
	char			*tmp;
	uint64_t		i;
	static t_list	*static_history = NULL;
	static t_list	*history_base = NULL;
	static t_list	*current_yanking = NULL;

	i = 0;
	if (history_base != paste_history)
	{
		history_base = paste_history;
		static_history = paste_history;
		current_yanking = paste_history;
	}
	tmp = NULL;
	if (history_base == NULL)
		return ;
	else if (*command == 20)
	{
		if (current_yanking->content)
			tmp = current_yanking->content;
		else
			return ;
	}
	else if (*(int*)command == 0xA080E2)
	{
		if (static_history->content)
		{
			tmp = static_history->content;
			i = ft_strlen(static_history->prev
						  ? static_history->prev->content
						  : static_history->content);
			current_yanking = static_history;
			while (i--)
						ft_delete_char(buf);
			static_history = static_history->next
				? static_history->next : history_base;
		}
		else
			return ;
	}
	ft_t_string_insert(buf, tmp);
	ft_putstr(tmp);
}

void	ft_erase_line(void)
{
	char	*res;

	res = tgetstr("dl", NULL);
	tputs(res, 1, &ft_putterm);
}

void	ft_set_am(void)
{
	char	*res;

	res = tgetstr("co", NULL);
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
		string->len = total_len;
		string->offset = total_len;
	}
	return (string);
}

t_string	*ft_t_string_insert(t_string *string, char *str)
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
	}
	ft_memmove(string->string + string->offset + str_len
			   , string->string + string->offset
			   , string->len - string->offset);
	ft_memcpy(string->string + string->offset, str, str_len);
	string->len += str_len;
	string->offset += str_len;
	string->string[string->len] = 0;
	return (string);
}

void	ft_get_history(t_list *history, char *command, t_string *buf)
{
	char			*tmp;
	static t_list	*static_history = NULL;
	static t_list	*history_base = NULL;

	if (history_base != history)
	{
		history_base = history;
		static_history = history;
	}
	tmp = NULL;
	if (history_base == NULL)
		return ;
	else
	{
		if (command[2] == 66)
		{
			if (static_history->content)
			{
				tmp = static_history->content;
				static_history = static_history->prev
					? static_history->prev : history_base;
			}
		}
		else
			if (static_history->content)
			{
				tmp = static_history->content;
				static_history = static_history->next
					? static_history->next : history_base;
			}
			
	}
	while (buf->offset > 0)
		ft_delete_char(buf);
	*buf->string = '\0';
	buf->len = 0;
	if (ft_strlen(tmp))
	{
		ft_t_string_concat(buf, tmp);
		ft_putstr(buf->string);
	}
}
