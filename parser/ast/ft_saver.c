/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_saver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 07:12:11 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/28 09:00:59 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static void		ft_put_parser_into_file(int32_t fd, t_parser *parser)
{
	uint32_t	i;

	i = 0;
	if (!parser->retained)
		return ;
	write(fd, (char*)parser, sizeof(t_parser));
	if (parser->id == OR || parser->id == AND)
	{
		while (i < parser->parser.and.n)
			ft_put_parser_into_file(parser->parser.or.parsers[i++]);
	}
	else if (parser->id == PLUS || parser->id == MULTIPLY
			 || parser->id == FUNC || parser->id == NOT)
		ft_put_parser_into_file(parser->parser.plus.parser);
}

int32_t			ft_save_parser(char	*filename, t_parser *parser)
{
	int32_t	fd;

	if ((fd = open(filename, O_WRONLY | O_CREAT) <= 0))
		return (-1);
	ft_put_parser_into_file(fd, parser);
	return (1);
}
