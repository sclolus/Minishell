/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built-in_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 13:23:24 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/05 08:03:42 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_print_history_list(void)
{
	t_list		*history_list;
	uint32_t	i;

	i = 0;
	history_list = *ft_get_history_list();
	while (history_list)
	{
		ft_putstr("    ");
		ft_putnbr(i);
		ft_putstr("    ");
		ft_putstr(history_list->content);
		ft_putchar('\n');
		i++;
		history_list = history_list->next;
	}
}

static int32_t	ft_delete_history_list(t_env *env, char *offset)
{
	int32_t		offset_nbr;
	int32_t		i;
	t_list		*history_list;
	t_list		*base;

	if (env) //
		;
	offset_nbr = ft_atoi(offset);
	if (offset_nbr < 0)
		return (ft_error(2, (char*[]){"history: ", "offset out of range"}, -1));
	history_list = *ft_get_history_list();
	base = history_list;
	i = 0;
	while (history_list && history_list->next != base && i < offset_nbr)
	{
		history_list = history_list->next;
		i++;
	}
	if (i == offset_nbr && history_list)
	{
		base = history_list;
		history_list->prev->next = history_list->next;
		free(history_list->content);
		free(history_list);
		return (1);
	}
	else
		return (ft_error(2, (char*[]){"history: ", "offset out of range"}, -1));
}

int32_t			ft_built_in_history(char **argv, t_env *env)
{
	int32_t		fd;

	fd = 0; //
	if (env && fd)
		;
	if (argv[1] == NULL)
	{
		ft_print_history_list();
	}
	else
		ft_delete_history_list(env, 0);
	return (0);
}
