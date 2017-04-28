/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:38:07 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/28 12:40:01 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int32_t	ft_is_shell_reserved(char *buf, uint32_t i)
{
	if (ft_strchr("|&;<>$ \t\n", buf[i])
		&& !ft_is_quoted(buf, i))
		return (1);
	return (0);
}

void			ft_add_token_to_list(t_list **token_list
							, char *input, uint32_t start, uint32_t i)
{
	t_list	*tmp;
	char	*tmp_token;

	if (!(tmp = ft_lstnew(0, 0)))
		exit(EXIT_FAILURE);
	if (!(tmp_token = ft_strsub(input, start, i - start)))
		exit(EXIT_FAILURE);
	tmp->content = tmp_token;
	ft_lstadd(token_list, tmp);
}

char			**ft_token_list_to_tab(t_list *token_list)
{
	char		**tab;
	t_list		*tmp;
	uint32_t	i;
	uint32_t	size;

	size = ft_lstlen(token_list);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (size + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		tab[size - i - 1] = token_list->content;
		tmp = token_list;
		token_list = token_list->next;
		free(tmp);
		i++;
	}
	return (tab);
}

uint32_t		ft_is_part_of_op(char *input, uint32_t index)
{
	uint32_t	i;

	i = index;
	if (i > 0 && !ft_is_quoted(input, index - 1)
		&& ft_strchr("|&;<>", input[index - 1]))
		return (1);
	else
		return (0);
}

char			**ft_lexer(char *input)
{
	t_list		*token_list;
	uint32_t	i;
	uint32_t	start;
	uint32_t	last_unquoted_point;
	t_bool		bool_word;

	i = 0;
	last_unquoted_point = 0;
	start = 0;
	bool_word = 0;
	token_list = NULL;
	while (input[i])
	{
		if (!ft_is_quoted(input + last_unquoted_point, i - last_unquoted_point))
			last_unquoted_point = i;
		if (!bool_word && !ft_strchr(CHARSET_WHITESPACES, input[i]))
		{
			bool_word = 1;
			start = i;
		}
		else if (bool_word && ((ft_strchr(CHARSET_WHITESPACES, input[i])
				&& !ft_is_quoted(input, i))
				|| (!ft_is_shell_reserved(input, i)
				&& ft_is_part_of_op(input, i))))
		{
			bool_word = 0;
			ft_add_token_to_list(&token_list, input, start, i);
			continue ;
		}
		else if (bool_word && ft_is_shell_reserved(input, i)
				&& !ft_is_part_of_op(input, i))
		{
			bool_word = 0;
			ft_add_token_to_list(&token_list, input, start, i);
			continue ;
		}
		i++;
	}
	if (bool_word)
		ft_add_token_to_list(&token_list, input, start, i);
	return (ft_token_list_to_tab(token_list));
}

uint32_t		ft_get_tokens_count(char **tokens)
{
	uint32_t	count;

	count = 0;
	while (tokens[count])
		count++;
	return (count);
}

t_tokens		*ft_get_tokens(char *input)
{
	t_tokens	*tokens;
	uint32_t	i;
	uint32_t	count;

	if (!(tokens = (t_tokens*)ft_memalloc(sizeof(t_tokens))))
		exit(EXIT_FAILURE);
	if (!(tokens->tokens = ft_lexer(input)))
	{
		free(tokens);
		return (NULL);
	}
	count = ft_get_tokens_count(tokens->tokens);
	if (!(tokens->lens = (uint32_t*)ft_memalloc(sizeof(uint32_t) * count)))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		tokens->lens[i] = ft_strlen(tokens->tokens[i]);
		i++;
	}
	return (tokens);
}

void			ft_free_tokens(t_tokens *tokens)
{
	uint32_t	i;

	i = 0;
	while (tokens->tokens[i])
		free(tokens->tokens[i++]);
	free(tokens->tokens);
	free(tokens->lens);
	free(tokens);
}
