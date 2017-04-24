/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 10:50:13 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/24 14:31:38 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

uint32_t		ft_eval_tokens_input(t_parser *parser, t_tokens *tokens)
{
	uint32_t	ret;

	if ((ret = ft_eval_tokens(parser
				, tokens)) && !tokens->tokens[tokens->index])
		return (1);
	return (0);
}

uint32_t		ft_eval_tokens(t_parser *parser, t_tokens *tokens)
{
	static const t_eval_tokens	eval_tokens[18] = {
		{&ft_eval_tokens_undefined},
		{&ft_eval_tokens_undefined},
		{&ft_eval_tokens_onechar},
		{&ft_eval_tokens_str},
		{&ft_eval_tokens_undefined},
		{&ft_eval_tokens_char_range},
		{&ft_eval_tokens_any},
		{&ft_eval_tokens_str_any_of},
		{&ft_eval_tokens_satisfy},
		{&ft_eval_tokens_satisfy_str},
		{&ft_eval_tokens_str_any},
		{&ft_eval_tokens_oneof},
		{&ft_eval_tokens_undefined},
		{&ft_eval_tokens_and},
		{&ft_eval_tokens_or},
		{&ft_eval_tokens_not},
		{&ft_eval_tokens_plus},
		{&ft_eval_tokens_multiply}};
	uint32_t					base;
	uint32_t					ret;

	base = tokens->index;
	if (tokens->tokens[tokens->index] == NULL)
		return (1);
	ret = eval_tokens[parser->id].f(parser, tokens);
	if (ret)
		parser->retained = RETAINED;
	else
	{
		parser->retained = UNRETAINED;
		tokens->index = base;
	}
	return (ret);
}