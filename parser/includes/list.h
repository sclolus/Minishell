/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 01:13:14 by aalves            #+#    #+#             */
/*   Updated: 2017/03/08 04:15:25 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

struct	s_list_head
{
	struct s_list_head	*prev;
	struct s_list_head	*next;
};

typedef struct s_list_head	t_list_head;

# define LIST_HEAD_INIT(name) { &(name), &(name) }
# define LIST_HEAD(name) t_list_head name = LIST_HEAD_INIT(name)
# define OFST(type, member) (unsigned long)(&((type *)0)->member)
# define GR(ptr, type) (type *)((char *)(ptr)-
# define LIST_ENTRY(ptr, type, member) (GR(ptr, type)OFST(type, member)))

void	init_list_head(t_list_head *list);
void	ft_list_add_between(t_list_head *new, t_list_head *prev,
							t_list_head *next);
void	ft_list_add(t_list_head *new, t_list_head *head);
void	ft_list_add_tail(t_list_head *new, t_list_head *head);
void	ft_list_del(t_list_head *link);
void	ft_list_move(t_list_head *to_move, t_list_head *head);
void	ft_list_move_tail(t_list_head *to_move, t_list_head *head);
int		ft_list_empty(t_list_head *head);
void	ft_list_splice_init(t_list_head *to_add, t_list_head *head);
void	ft_list_iter(t_list_head *head, void (*f) (t_list_head *));
void	ft_list_iter_safe(t_list_head *head, void (*f) (t_list_head *));

#endif
