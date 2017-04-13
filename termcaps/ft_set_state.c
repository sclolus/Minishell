/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 08:16:44 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/13 08:30:21 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

static int32_t	ft_is_shell_reserved(t_string *buf, uint32_t i)
{
	if (ft_strchr("|&;<>()$`\"' \t\n", buf->string[i])
		&& !ft_is_quoted(buf->string, i))
		return (1);
	return (0);
}

t_termcaps_state	*ft_get_term_state(void)
{
	static t_termcaps_state	state = NORMAL;

	return (&state);
}

void				ft_set_term_state(t_string *buf)
{
	t_termcaps_state	*state;
	uint32_t			i;
	int32_t				command_pos;
	int8_t				bool;

	state = ft_get_term_state();
	command_pos = 0;
	i = 0;
	bool = 0;
	while (i < buf->offset)
	{
		if (ft_is_shell_reserved(buf, i))
		{
			command_pos = -1;
			bool = 0;
		}
		else if (!bool && ft_strchr(" \t\n", buf->string[i])
			&& !ft_is_quoted(buf->string, i))
		{
			i++;
			continue ;
		}
		else if (!bool && (!ft_strchr(" \t\n", buf->string[i])
						   || ft_is_quoted(buf->string, i)))
			bool = 1;
		else if (bool && ft_strchr(" \t\n", buf->string[i])
			&& !ft_is_quoted(buf->string, i))
		{
			command_pos++;
			bool = 0;
		}
		i++;
	}
	if (command_pos == 0)
		*state = COMMAND_NAME;
	else if (command_pos > 0)
		*state = ARGV;
	else
		*state = NORMAL;
}
