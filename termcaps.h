/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 03:26:22 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/03 09:35:14 by sclolus          ###   ########.fr       */
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
void		ft_erase_line(void);
#endif
