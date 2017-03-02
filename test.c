/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 23:53:31 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/02 06:28:18 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int	ft_putterm(int c)
{
	return (write(1, &c, 1));
}

int	ft_exec_term_event(char	*command)
{
	static t_cursor	cursor = {{0, 0}, {0, 0}, 0};

	if (*command == '\n')
	{
		cursor.pos.x = 0;
		cursor.pos.y = 0;
	}
	else if (*((short*)command) == 0x5B1B)
	{
		if (command[2] == 68)
			ft_move_left_cursor(&cursor);
		else if (command[2] == 67)
			ft_move_right_cursor(&cursor);
		else if (command[2] == 66)
			ft_move_down_cursor(&cursor);
		else if (command[2] == 65)
			ft_move_up_cursor(&cursor);
		return (1);
	}
	else if (*command == 1)
	{
		ft_move_start_line(&cursor);
		return (1);
	}
	else if (*command == 11)
	{
		ft_kill_line(&cursor);
		return (1);
	}
	else if (*command == 127)
	{
		ft_delete_char(&cursor);
		return (1);
	}
	else
		cursor.pos.x++;
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
	char			*tmp;
	static t_string	buf = {1, 0, NULL};

	buf.len = 0;
	if (buf.string == NULL)
		if (!(buf.string = ft_strnew(0)))
			exit(EXIT_FAILURE);
	*buf.string = 0;
	if (!(tmp = ft_strnew(3)))
		exit (EXIT_FAILURE);
	while (1)
	{
		if (*tmp == '\n')
		{
			*line = buf.string;
			break ;
		}
		if (read(0, tmp, 3) == -1)
			exit (EXIT_FAILURE);
	   	if (!ft_exec_term_event(tmp))
		{
			ft_putchar(*tmp);
			tmp[1] = 0;
			ft_t_string_concat(&buf, tmp);
		}
		ft_memset(tmp + 1, 0, 3);
	}
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
	ft_putstr("sclolus?>");
	buffer = ft_strnew(0);
	while (1)
	{
#if 0
		i = 0;
		if (*line == '\n')
			ft_putstr("sclolus?>");
		read(0, line, 3);
		if (*line == 'q')
			break ;
//		ft_putcommand_nb(line);
	   	if (!ft_exec_term_event(line))
		{
			ft_putchar(*line);
			line[1] = 0;
			buffer = ft_strjoin(buffer, line);
		}
		ft_memset(line + 1, 0, 3);
#endif
		ft_termget(&line);
		if (*line == 'q')
			break ;
		ft_putchar('-');
		ft_putendl(line);
		*line = 0;
		ft_putstr("_______");

	}
	ft_unset_insert();
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
		return (-1);
	ft_putendl("______");
	ft_putstr(buffer);
#endif

}
