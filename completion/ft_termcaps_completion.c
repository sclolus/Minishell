/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps_completion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 09:50:12 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/08 17:35:15 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t			ft_put_completion(t_ltree *ltree, char **completions,
									t_string *buf, char *prefix)
{
	uint32_t	i;
	uint32_t	n;
	int32_t		ret;

	n = 0;
	i = 0;
	if (!completions)
	{
		ft_putchar(7);
		return (0);
	}
	while (completions[n])
		n++;
	if ((ret = ft_put_max_completion(ltree, buf, prefix, n)) > -1)
	{
		ft_free_argv(completions);
		return (ret);
	}
	if (n > 1)
		ft_put_completions(buf, completions, n, prefix);
	ft_free_argv(completions);
	return (1);
}

int32_t			ft_completion(t_string *buf, t_shenv *shenv)
{
	static const t_comp_event	events[] = {
		NULL,
		&ft_completion_normal_state,
		&ft_complete_command_name,
		&ft_complete_argv,
	};
	t_termcaps_state			*state;

	ft_set_term_state(buf);
	state = ft_get_term_state();
	return (events[*state](buf, shenv));
}
