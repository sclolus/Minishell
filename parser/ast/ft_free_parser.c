/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 09:49:33 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/31 02:47:04 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ft_free_parser_struct(t_parser *parser)
{
	if (!parser)
		return ;
	if (parser->name)
		free(parser->name);
	if (parser->alloc == ALONE)
		free(parser);
}

void	ft_free_parser_onechar(t_parser *parser)
{
	ft_free_parser_struct(parser);
}

void	ft_free_parser_ref(t_parser *parser)
{
	free(parser->parser.ref.rule_name);
	ft_free_parser_struct(parser);
}

void	ft_free_parser_str_any_of(t_parser *parser)
{

	free(parser->parser.str_any_of.charset);
	if (parser->parser.str_any_of.str)
		free(parser->parser.str_any_of.str);
	ft_free_parser_struct(parser);
}

void	ft_free_parser_any(t_parser *parser)
{
	ft_free_parser_struct(parser);
}

void	ft_free_parser_str_any(t_parser *parser)
{
    if(parser->parser.str_any.str)
      	free(parser->parser.str_any.str);
    ft_free_parser_struct(parser);
}

void	ft_free_parser_str(t_parser *parser)
{
	free(parser->parser.string.str);
	ft_free_parser_struct(parser);
}

void	ft_free_parser_regexp(t_parser *parser)
{
	free(parser->parser.regexp.regexp);
	ft_free_parser_struct(parser);
}

void	ft_free_parser_and_n(t_parser *parser)
{
	uint32_t	i;

	i = 0;
	while (i < parser->parser.and.n)
	{
		ft_free_parser(parser->parser.and.parsers[i]);
		i++;
	}
	free(parser->parser.and.parsers);
	ft_free_parser_struct(parser);
}

void	ft_free_parser_or_n(t_parser *parser)
{
	uint32_t	i;

	i = 0;
	while (i < parser->parser.or.n)
	{
		ft_free_parser(parser->parser.or.parsers[i]);
		i++;
	}
	free(parser->parser.or.parsers);
	ft_free_parser_struct(parser);
}

void	ft_free_parser_plus(t_parser *parser)
{
	uint32_t	i;

	i = 0;
	while (i < parser->parser.plus.n)
	{
		ft_free_parser(parser->parser.plus.parsers[i]);
		i++;
	}
        if (parser->parser.plus.n)
            free(parser->parser.plus.parsers);
	ft_free_parser(parser->parser.plus.parser);
	ft_free_parser_struct(parser);
}

void	ft_free_parser_multiply(t_parser *parser)
{
	uint32_t	i;

	i = 0;
	while (i < parser->parser.multiply.n)
	{
		ft_free_parser(parser->parser.multiply.parsers[i]);
		i++;
	}
        if (parser->parser.plus.n)
            free(parser->parser.multiply.parsers);
	ft_free_parser(parser->parser.multiply.parser);
	ft_free_parser_struct(parser);
}

void	ft_free_parser_char_range(t_parser *parser)
{
	ft_free_parser_struct(parser);
}

void	ft_free_parser_satisfy(t_parser *parser)
{
	ft_free_parser_struct(parser);
}

void	ft_free_parser_satisfy_str(t_parser *parser)
{
	ft_free_parser_struct(parser);
}

void	ft_free_parser_oneof(t_parser *parser)
{
	free(parser->parser.oneof.charset);
	ft_free_parser_struct(parser);
}

void	ft_free_parser_not(t_parser *parser)
{
	free(parser->parser.not.parser);
	ft_free_parser_struct(parser);
}

void	ft_free_parser_func(t_parser *parser)
{
	ft_free_parser(parser->parser.func.parser);
	ft_free_parser_struct(parser);
}

void	ft_free_parser_undefined(t_parser *parser)
{
	ft_putstr("feels bad man");
        (void)parser;
	ft_free_parser_struct(parser);
}

void	ft_free_parser(t_parser *parser)
{
	static const t_free_parser	free_parsers[18] = {
		{ft_free_parser_undefined},
		{ft_free_parser_ref},
		{ft_free_parser_onechar},
		{ft_free_parser_str},
		{ft_free_parser_regexp},
		{ft_free_parser_char_range},
		{ft_free_parser_any},
		{ft_free_parser_str_any_of},
		{ft_free_parser_satisfy},
		{ft_free_parser_satisfy_str},
		{ft_free_parser_str_any},
		{ft_free_parser_oneof},
		{ft_free_parser_func},
		{ft_free_parser_and_n},
		{ft_free_parser_or_n},
		{ft_free_parser_not},
		{ft_free_parser_plus},
		{ft_free_parser_multiply}};

	if (!parser)
		return ;
	free_parsers[parser->id].f(parser);
}
