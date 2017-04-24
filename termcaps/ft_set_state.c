/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 08:16:44 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/23 10:09:14 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

# if 0
static int32_t	ft_is_shell_reserved(t_string *buf, uint32_t i)
{
	if (ft_strchr("|&;<>()$`\"' \t\n", buf->string[i])
		&& !ft_is_quoted(buf->string, i))
		return (1);
	return (0);
}
#endif
t_termcaps_state	*ft_get_term_state(void)
{
	static t_termcaps_state	state = NORMAL;

	return (&state);
}

void				ft_put_term_state(t_termcaps_state *state)
{
	ft_putchar('\n');
	if (*state == NORMAL)
		ft_putendl("NORMAL");
	else if (*state == COMMAND_NAME)
		ft_putendl("COMMAND_NAME");
	else if (*state == ARGV)
		ft_putendl("ARGV");
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
		while (i < buf->offset && ft_strchr(" \t\n", buf->string[i])
			   && !ft_is_quoted(buf->string, i))
		{
			i++;
			bool = 0;
		}
		if (i == buf->offset)
			break ;
		if (ft_strchr("&;|", buf->string[i]) && !ft_is_quoted(buf->string, i))
		{			
			command_pos = 0;
			bool = 0;
		}
		else if (!bool && (!ft_strchr(" \t\n", buf->string[i])
						   || ft_is_quoted(buf->string, i)))
		{
			bool = 1;
			command_pos++;
		}
		else if (bool && ft_strchr(" \t\n", buf->string[i])
			&& !ft_is_quoted(buf->string, i))
			bool = 0;
		i++;
	}
	if (command_pos == 1 && bool)
		*state = COMMAND_NAME;
	else if (command_pos > 1 && bool)
		*state = ARGV;
	else
		*state = NORMAL;
}
