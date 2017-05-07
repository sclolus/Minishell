/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complete_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 13:51:12 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/28 14:00:28 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_completion.h"

static int32_t	ft_is_shell_reserved(t_string *buf, uint32_t i)
{
	if (ft_strchr("|&;<>()$`\"' \t\n", buf->string[i])
		&& !ft_is_quoted(buf->string, i))
		return (1);
	return (0);
}

static char		*ft_get_current_token(t_string *buf)
{
	char		*token;
	uint32_t	i;
	uint32_t	start;

	if (buf->offset > 0)
		i = buf->offset - 1;
	start = 0;
	while (buf->offset)
	{
		if (ft_is_shell_reserved(buf, i))
		{
			start = i + 1;
			break ;
		}
		else if (i == 0)
			break ;
		i--;
	}
	if (!(token = ft_strndup(buf->string + start, buf->offset - start)))
		exit(EXIT_FAILURE);
	return (token);
}

int32_t			ft_complete_argv(t_string *buf, t_shenv *shenv)
{
	char		**completions;
	char		*command_prefix;
	t_ltree		*ltree;
	char		*lol[2];
	uint32_t	ret;

	ltree = NULL;
	command_prefix = ft_get_current_token(buf);
	(void)shenv;
	if (!(lol[0] = ft_get_path_name(command_prefix))
		|| !ft_ltree_add_directory(&ltree, lol[0])
		|| !(lol[1] = ft_get_file_name(command_prefix))
		|| !(completions = ft_get_ltree_suffixes(ltree, lol[1])))
	{
		free(command_prefix);
		ft_putchar(7);
		return (0);
	}
	ret = ft_put_completion(ltree, completions, buf, lol[1]);
	ft_free_ltree(ltree);
	free(command_prefix);
	return (ret);
}

int32_t			ft_completion_normal_state(t_string *buf, t_shenv *shenv)
{
	if (buf && shenv)
		;
	ft_putchar(7);
	return (0);
}
