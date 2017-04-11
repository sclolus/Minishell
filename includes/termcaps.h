/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 03:26:22 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/11 17:30:32 by sclolus          ###   ########.fr       */
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

# undef tab
# define ID_MOVE_START_LINE 0x1
# define ID_MOVE_END_LINE 0x5
# define ID_MOVE_DOWN_CURSOR 0xE
# define ID_MOVE_UP_CURSOR 0x10
# define ID_DELETE_CHAR 0x7F
# define ID_MOVE_LEFT_CURSOR 0x445B1B
# define ID_MOVE_RIGHT_CURSOR 0x435B1B
# define ID_KILL_LINE 0xB
# define ID_YANKING 0x14
# define ID_DIRECTION_KEY 0x5B1B
# define ID_HISTORIC_YANKING 0xA080E2
# define ID_HISTORY_DOWN 0x42
# define ID_HISTORY_UP 0x41
# define ID_TAB 0x9

typedef enum	s_termcaps_state
{
	NORMAL = 1,
	COMPLETION_SHOWN,
	COMMAND_NAME,
	ARGV,
}				t_termcaps_state;

/*typedef	struct s_coord
  {
	int64_t		x;
	int64_t		y;
	}				t_coord;
	
	typedef struct	s_cursor
	{
	t_coord		pos;
	t_coord		pos_end;
	int64_t		buff_len;
	}				t_cursor;*/

typedef int32_t (*t_comp_event)(t_string*, t_termcaps_state*);

typedef struct	s_term_event
{
	int32_t		id;
	void		(*f)(t_string*);
}				t_term_event;

int					ft_putterm(int c);
t_termcaps_state	*ft_get_term_state(void);

int32_t				ft_set_term(void);

uint32_t			ft_termget(char **line);
int32_t				ft_term_line_continuation(char *line);
uint32_t			ft_termget_complete_line(char **line);
void				ft_move_left_cursor(t_string *buf);
void				ft_move_right_cursor( t_string *buf);
void				ft_move_up_cursor(t_string *buf);
void				ft_move_down_cursor(t_string *buf);
void				ft_move_start_line(t_string *buf);
void				ft_move_end_line(t_string *buf);
void				ft_screen_clear(void);
void				ft_delete_char(t_string *buf);
void				ft_kill_line(t_string *buf, t_list **paste_history);
void				ft_paste_line(t_string *buf, char *command, t_list *paste_history);
void				ft_set_insert(void);
void				ft_unset_insert(void);
void				ft_set_am(void);
void				ft_print_history_len(t_list *list);
void				ft_print_history(t_string *buf, char *history);
t_string			*ft_t_string_concat(t_string *string, char *str);
t_string			*ft_t_string_insert(t_string *string, char *str);
t_list				**ft_get_history_list(void);
void				ft_get_history(t_list *history, char *command, t_string *buf);
void				ft_explore_paste_history(t_string *buf, t_list **static_history,
											 t_list **history_base, t_list **current_yanking);
int					ft_exec_special_event(t_list **history, t_string *buf
								  , t_list **paste_history, char *command);
void				ft_erase_line(void);
#endif
