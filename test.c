/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 23:53:31 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/03 09:40:20 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include <stdio.h>


int	ft_putterm(int c)
{
	return (write(1, &c, 1));
}

int	ft_exec_term_event(char	*command, t_string *buf)
{
//	static t_cursor	cursor = {{0, 0}, {0, 0}, 0};
	static t_list			*history = NULL;
	static t_list			*paste_history = NULL;
	t_list			*tmp;

	if (*command == '\n')
	{
		if (!(tmp = ft_lstnew(buf->string, buf->len)))
			exit (EXIT_FAILURE);
		ft_lstadd(&history, tmp);
		ft_move_end_line(buf);
	}
	else if (*((short*)command) == 0x5B1B)
	{
		if (command[2] == 68)
			ft_move_left_cursor(buf);
		else if (command[2] == 67)
			ft_move_right_cursor(buf);
		else if (command[2] == 66 || command[2] == 65)
		{
			ft_get_history(history, command, buf);
		}
		return (1);
	}
	else if (*command == 1)
	{
		ft_move_start_line(buf);
		return (1);
	}
	else if (*command == 3)
		exit (EXIT_FAILURE);
	else if (*command == 5)
	{
		ft_move_end_line(buf);
		return (1);
	}
	else if (*command == 11)
	{
		ft_kill_line(buf, &paste_history);
		return (1);
	}
	else if (*command == 20 || *(int*)command == 0xA080E2)
	{
		ft_paste_line(buf, command, paste_history);
		return (1);
	}
	else if (*command == 127)
	{
		ft_delete_char(buf);
		return (1);
	}
	return (0);
}

void	ft_putcommand_nb(char *command)
{
	ft_putchar('{');
	while (*command)
	{
		ft_putnbr(*command++);
		ft_putchar(' ');
	}
	ft_putchar('}');
}

void	ft_termget(char **line)
{
	static t_string	buf = {256, 0, 0, NULL};
	static char		tmp[4] = "\0\0\0\0";

	buf.len = 0;
	buf.offset = 0;
	if (buf.string == NULL)
		if (!(buf.string = ft_strnew(255)))
			exit(EXIT_FAILURE);
	*buf.string = 0;
	while (1)
	{
		if (read(0, tmp, 3) == -1)
			exit (EXIT_FAILURE);
//		ft_putcommand_nb(tmp);
		if (!ft_exec_term_event(tmp, &buf))
		{
			if (*tmp == '\n')
			{
				ft_putchar('\n');
				break;
			}
			ft_putchar(*tmp);
			tmp[1] = 0;
			if (buf.offset == buf.len)
				ft_t_string_concat(&buf, tmp);
			else
				ft_t_string_insert(&buf, tmp);
		}
		ft_memset(tmp + 1, 0, 3);
	}
	*line = buf.string;
}

int	main(int argc, char **argv)
{
	char			*line;
	char			*buffer;
	char			*name_term = "xterm-256color";
	int				i;
	struct termios	term;

	if (!(line = malloc(4)))
		return (EXIT_FAILURE);
	line[3] = 0;
	if (tgetent(NULL, name_term) == -1)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	ft_screen_clear();
	ft_set_insert();
# if 1
	buffer = ft_strnew(0);
	while (1)
	{
		ft_putstr("sclolus?>");
		ft_termget(&line);
		*line = 0;
	}
	ft_unset_insert();
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
		return (-1);
#endif

}
