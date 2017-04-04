/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 03:26:22 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/28 01:21:05 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TERMSCAPS_H__
# define __TERMSCAPS_H__

# include <termios.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <term.h>
# include <stdint.h>
# include "libft.h"

# define ID_MOVE_START_LINE 0x1
# define ID_MOVE_END_LINE 0x5
# define ID_MOVE_DOWN_CURSOR 0xE
# define ID_MOVE_UP_CURSOR 0x10
# define ID_DELETE_CHAR 0x7F
# define ID_MOVE_LEFT_CURSOR 0x445B1B
# define ID_MOVE_RIGHT_CURSOR 0x435B1B
# define ID_KILL_LINE 0xB
# define ID_YANKING 0x15
# define ID_DIRECTION_KEY 0x5B1B
# define ID_HISTORIC_YANKING 0xA080E2
# define ID_HISTORY_DOWN 0x42
# define ID_HISTORY_UP 0x41

typedef	struct s_coord
{
	int64_t		x;
	int64_t		y;
}				t_coord;

typedef struct	s_cursor
{
	t_coord		pos;
	t_coord		pos_end;
	int64_t		buff_len;
}				t_cursor;

typedef struct	s_string
{
	uint64_t	capacity;
	uint64_t	len;
	int64_t		offset;
	char		*string;
}				t_string;

typedef struct	s_term_event
{
	uint32_t	id;
	void		(*f)(t_string*);
}				t_term_event;

int			ft_putterm(int c);

void		ft_termget(char **line);
void		ft_move_left_cursor(t_string *buf);
void		ft_move_right_cursor( t_string *buf);
void		ft_move_up_cursor(t_string *buf);
void		ft_move_down_cursor(t_string *buf);
void		ft_move_start_line(t_string *buf);
void		ft_move_end_line(t_string *buf);
void		ft_screen_clear(void);
void		ft_delete_char(t_string *buf);
void		ft_kill_line(t_string *buf, t_list **paste_history);
void		ft_paste_line(t_string *buf, char *command, t_list *paste_history);
void		ft_set_insert(void);
void		ft_unset_insert(void);
void		ft_set_am(void);
void		ft_print_history_len(t_list *list);
t_string	*ft_t_string_concat(t_string *string, char *str);
t_string	*ft_t_string_insert(t_string *string, char *str);
void		ft_get_history(t_list *history, char *command, t_string *buf);
int			ft_exec_special_event(t_list **history, t_string *buf
								  , t_list **paste_history, char *command);
void		ft_erase_line(void);
#endif
