/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built-in_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 13:23:24 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/31 14:35:28 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_history_list(void)
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

void	ft_built_in_history(t_env *env, char **argv)
{
	if (env)
		;
	if (argv[1] == NULL)
	{
		ft_print_history_list();
	}
}
