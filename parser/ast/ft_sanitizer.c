/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 03:53:17 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/18 04:12:23 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ft_sanitize_parser_onechar(t_parser *parser)
{
	parser->retained = 0;
}

void	ft_sanitize_parser_ref(t_parser *parser)
{
	parser->retained = 0;
}

void	ft_sanitize_parser_str_any_of(t_parser *parser)
{
	parser->retained = 0;
	free(parser->parser.str_any_of.str);
	parser->parser.str_any_of.str = NULL;
}

void	ft_sanitize_parser_any(t_parser *parser)
{
	parser->retained = 0;
	parser->parser.any.matched = 0;
}

void	ft_sanitize_parser_str_any(t_parser *parser)
{
	parser->retained = 0;
	free(parser->parser.str_any.str);
	parser->parser.str_any.str = NULL;
}

void	ft_sanitize_parser_str(t_parser *parser)
{
	parser->retained = 0;
	parser->parser.string.len = 0;
	parser->parser.string.str = NULL;
}

void	ft_sanitize_parser_regexp(t_parser *parser)
{
	parser->retained = 0;
}

void	ft_sanitize_parser_and_n(t_parser *parser)
{
	uint32_t	i;

	i = 0;
	parser->retained = 0;
	while (i < parser->parser.and.n)
	{
		ft_sanitize_parser(parser->parser.and.parsers[i]);
		i++;
	}
}

void	ft_sanitize_parser_or_n(t_parser *parser)
{
	uint32_t	i;

	i = 0;
	parser->retained = 0;
	parser->parser.or.matched = -1;
	while (i < parser->parser.or.n)
	{
		ft_sanitize_parser(parser->parser.or.parsers[i]);
		i++;
	}
}

void	ft_sanitize_parser_plus(t_parser *parser)
{
	uint32_t	i;

	i = 0;

	parser->retained = 0;
	while (i < parser->parser.plus.n)
	{
		ft_free_parser(parser->parser.plus.parsers[i]);
		i++;
	}
	parser->parser.plus.n = 0;
	parser->parser.plus.parsers = NULL;
}

void	ft_sanitize_parser_multiply(t_parser *parser)
{
	uint32_t	i;

	i = 0;
	parser->retained = 0;
	while (i < parser->parser.multiply.n)
	{
		ft_free_parser(parser->parser.multiply.parsers[i]);
		i++;
	}
	parser->parser.multiply.n = 0;
	parser->parser.multiply.parsers = NULL;
}

void	ft_sanitize_parser_char_range(t_parser *parser)
{
	parser->retained = 0;
	parser->parser.range.matched = 0;
}

void	ft_sanitize_parser_satisfy(t_parser *parser)
{
	parser->retained = 0;
}

void	ft_sanitize_parser_satisfy_str(t_parser *parser)
{
	parser->retained = 0;
}

void	ft_sanitize_parser_oneof(t_parser *parser)
{
	parser->retained = 0;
	parser->parser.oneof.c = 0;
}

void	ft_sanitize_parser_not(t_parser *parser)
{
	parser->retained = 0;
	ft_sanitize_parser(parser->parser.not.parser);
}

void	ft_sanitize_parser_func(t_parser *parser)
{
	parser->retained = 0;
	ft_sanitize_parser(parser->parser.func.parser);
}

void	ft_sanitize_parser_undefined(t_parser *parser)
{
	parser->retained = 0;
	ft_putstr_fd("Sanitizing undefined parser", 2);
}

void	ft_sanitize_parser(t_parser *parser)
{
	static const t_free_parser	sanitize_parsers[18] = {
		{ft_sanitize_parser_undefined},
		{ft_sanitize_parser_ref},
		{ft_sanitize_parser_onechar},
		{ft_sanitize_parser_str},
		{ft_sanitize_parser_regexp},
		{ft_sanitize_parser_char_range},
		{ft_sanitize_parser_any},
		{ft_sanitize_parser_str_any_of},
		{ft_sanitize_parser_satisfy},
		{ft_sanitize_parser_satisfy_str},
		{ft_sanitize_parser_str_any},
		{ft_sanitize_parser_oneof},
		{ft_sanitize_parser_func},
		{ft_sanitize_parser_and_n},
		{ft_sanitize_parser_or_n},
		{ft_sanitize_parser_not},
		{ft_sanitize_parser_plus},
		{ft_sanitize_parser_multiply}};

	if (!parser)
		return ;
	sanitize_parsers[parser->id].f(parser);
}
