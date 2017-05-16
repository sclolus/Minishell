/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_parser_chars.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 20:13:20 by aalves            #+#    #+#             */
/*   Updated: 2017/05/05 20:16:13 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	ft_free_parser_onechar(t_parser *parser)
{
	ft_free_parser_struct(parser);
}

void	ft_free_parser_any(t_parser *parser)
{
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

void	ft_free_parser_oneof(t_parser *parser)
{
	free(parser->parser.oneof.charset);
	ft_free_parser_struct(parser);
}
