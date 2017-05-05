/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_tokens_logicals.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 10:53:22 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/05 17:55:02 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

uint32_t		ft_eval_tokens_or(t_parser	*parser, t_tokens *tokens)
{
	uint32_t	ret;
	uint32_t	i;

	ret = 0;
	i = 0;
	while (!ret && i < parser->parser.or.n)
	{
		if (parser->parser.or.parsers[i]->id == STR_ANY)
			parser->parser.or.parsers[i]->parser.str_any.end
				= i + 1 < parser->parser.or.n ? parser->parser.or.parsers[i + i]
				: NULL;
		ret |= ft_eval_tokens(parser->parser.or.parsers[i], tokens);
		i++;
	}
	if (ret)
		parser->parser.or.matched = i - 1;
	return (ret);
}


uint32_t		ft_eval_tokens_and(t_parser	*parser, t_tokens *tokens)
{
	uint32_t	ret;
	uint32_t	i;

	ret = 1;
	i = 0;
	while (ret && i < parser->parser.and.n)
	{
		if (parser->parser.and.parsers[i]->id == STR_ANY)
			parser->parser.and.parsers[i]->parser.str_any.end
				= i + 1 < parser->parser.and.n ? parser->parser.and.parsers[i + i]
				: NULL;
		ret &= ft_eval_tokens(parser->parser.and.parsers[i], tokens);
		i++;
	}
	return (ret);
}

uint32_t		ft_eval_tokens_not(t_parser	*parser, t_tokens *tokens)
{
	return (!ft_eval_tokens(parser, tokens));
}

uint32_t		ft_eval_tokens_plus(t_parser *parser, t_tokens *tokens)
{
	t_list		*head;
	t_list		*link;
	uint32_t	n;
	uint32_t	i;

	n = 0;
	i = 0;
	head = NULL;
	while (1)
	{
		if (!(link = ft_lstnew(NULL, sizeof(t_parser*))))
			exit(EXIT_FAILURE);
		link->content = ft_dup_parser(parser->parser.plus.parser);
		if (!ft_eval_tokens(link->content, tokens))
		{
			ft_free_parser(link->content);
			free(link);
			break;
		}
		ft_lstadd(&head, link);
		++n;
	}
	if (n)
	{
		parser->parser.plus.n = n;
		if (!(parser->parser.plus.parsers = (t_parser**)malloc(n * sizeof(t_parser*))))
			exit(EXIT_FAILURE);
		i = n - 1;
		while (head)
		{
			parser->parser.plus.parsers[i] = head->content;
			link = head;
			head = head->next;
			free(link);
			--i;
		}
	}
	return (n != 0);
}

uint32_t		ft_eval_tokens_multiply(t_parser *parser, t_tokens *tokens)
{
	t_list		*head;
	t_list		*link;
	uint32_t	n;
	uint32_t	i;

	n = 0;
	i = 0;
	head = NULL;
	while (1)
	{
		if (!(link = ft_lstnew(NULL, sizeof(t_parser*))))
			exit(EXIT_FAILURE);
		link->content = ft_dup_parser(parser->parser.multiply.parser);
		if (!ft_eval_tokens(link->content, tokens))
		{
			ft_free_parser(link->content);
			free(link);
			break;
		}
		ft_lstadd(&head, link);
		++n;
	}
	if (n)
	{
		parser->parser.multiply.n = n;
		if (!(parser->parser.multiply.parsers = (t_parser**)malloc(n * sizeof(t_parser*))))
			exit(EXIT_FAILURE);
		i = n - 1;
		while (head)
		{
			parser->parser.multiply.parsers[i] = head->content;
			link = head;
			head = head->next;
			free(link);
			--i;
		}
	}
	return (1);
}
