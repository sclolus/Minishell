/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps_completion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 09:50:12 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/11 19:11:31 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	
	while (i > 0)
	{
		if (ft_is_shell_reserved(buf, i))
		{
			start = i + 1;
			break ;
		}
		i--;
	}
	if (!(token = ft_strndup(buf->string + start, buf->offset - start)))
		exit(EXIT_FAILURE);
	return (token);
}

int32_t		ft_put_completion(t_ltree *ltree, char **completions
							  , t_string *buf, char *prefix)
{
	char		*max_completion;
	uint32_t	i;
	uint32_t	n;

	n = 0;
	i = 0;
	while (completions[n])
		n++;
	if ((max_completion = ft_ltree_get_completion(ltree, prefix)))
		ft_t_string_insert(buf, max_completion);
	if (!n)
		return (0);
	else if (n > 1)
		return (ft_put_completions(buf, completions));
	return (1);
}

int32_t		ft_complete_command_name(t_string *buf, t_termcaps_state *state)
{
	char		**path;
	t_ltree		*ltree;
	char		*command_prefix;
	int32_t		ret;

    command_prefix = ft_get_current_token(buf);
	path = ft_get_env_value(env->env, "PATH");
	ltree = NULL;
	while (*path)
		ft_ltree_add_directory(&ltree, *path);
	free(path);
	ret = ft_put_completion(ltree, ft_get_ltree_suffixes(ltree, command_prefix)
							, buf, command_prefix);
	ft_free_ltree(ltree);
	return (ret);
}

int32_t		ft_completion(t_string *buf, t_env *env)
{
	static const t_comp_event	events[] = {
		&ft_complete_command_name;
	}
	t_termcaps_state			*state;
	t_ltree						*ltree;
	uint32_t					n_completions;

	state = ft_get_term_state();
	return (events[*state](buf, state));
}
