/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_parser_strings.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 16:44:34 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/05 17:16:38 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

uint32_t		ft_eval_parser_satisfy_str(t_parser *parser, char **string)
{
	uint32_t	ret;

	if ((ret = parser->parser.satisfy_str.f(*string)))
	{
		(*string) += ret;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_parser_str(t_parser *parser, char **string)
{
	if (!(ft_memcmp(parser->parser.string.str
					, *string, parser->parser.string.len)))
	{
		*string += parser->parser.string.len;
		return (1);
	}
	else
		return (0);
}

uint32_t		ft_eval_parser_str_any(t_parser *parser, char **string)
{
	uint32_t	ret;
	uint32_t	count;

	ret = 0;
	count = 0;
	if (parser->parser.str_any.end)
	{
		parser->parser.str_any.str = *string;
		while (**string
			&& !(ret = (ft_eval_parser(parser->parser.str_any.end, string))))
		{
			(*string)++;
			count++;
		}
		if (ret)
			(*string)--;
		parser->parser.str_any.len = count;
		parser->parser.str_any.str = ft_strndup(parser->parser.str_any.str
												, count);
	}
	else
	{
		parser->parser.str_any.str = *string;
		parser->parser.str_any.len = ft_strlen(*string);
		(*string) += parser->parser.str_any.len;
	}
	return (1);
}

uint32_t		ft_eval_parser_str_any_of(t_parser *parser, char **string)
{
	uint32_t			bool;
	static char			buf[4096];
	uint32_t			offset;
	t_string			*str;

	bool = 0;
	offset = 0;
	str = ft_t_string_new(32);
	while (**string)
	{
		if (ft_strchr(parser->parser.str_any_of.charset, **string))
		{
			bool |= 1;
			if (offset < 4096)
			{
				buf[offset++] = **string;
				(*string)++;
			}
			else
			{
				ft_t_string_concat_len(str, buf, 4096);
				offset = 0;
			}
		}
		else
			break ;
	}
	if (offset)
		ft_t_string_concat_len(str, buf, offset);
	parser->parser.str_any_of.str = str->string;
	free(str);
	return (bool);
}
