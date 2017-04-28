/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 14:22:32 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/28 14:25:42 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static uint32_t	ft_get_redirec_number(t_parser *redirec)
{
	if (OR_PARSER_N(redirec, 0)->retained)
	{
		redirec = OR_PARSER_N(redirec, 0);
		return (AND_PARSER_N(redirec, 1)->parser.or.matched);
	}
	else
	{
		redirec = OR_PARSER_N(redirec, 1);
		return (redirec->parser.or.matched);
	}
}

int32_t		ft_redirections(t_parser *simple_cmd)
{
	static const t_redirec	f_redirec[8] = {
		&ft_output_redirect,
		&ft_duplicating_output_redirect,
		&ft_input_redirect,
		&ft_duplicating_input_redirect,
		&ft_heredoc_redirect,
		&ft_read_write_redirect,
		&ft_output_append_redirect,
		&ft_output_redirect
	};
	t_parser		*parser;
	uint32_t		prefix_n;
	uint32_t		postfix_n;
	uint32_t		i;

	i = 0;
	prefix_n = MULTIPLY_N(AND_PARSER_N(simple_cmd, 1));
	postfix_n = MULTIPLY_N(AND_PARSER_N(simple_cmd, 4));
	parser = AND_PARSER_N(simple_cmd, 1);
	while (i < prefix_n)
	{
		if (OR_PARSER_N(MULTIPLY_PARSER_N(parser, i), 1)->retained)
			f_redirec[ft_get_redirec_number(AND_PARSER_N(OR_PARSER_N(MULTIPLY_PARSER_N(parser, i), 1), 0))]
				(AND_PARSER_N(OR_PARSER_N(MULTIPLY_PARSER_N(parser, i), 1), 0));
		i++;
	}
	i = 0 ;
	parser = AND_PARSER_N(simple_cmd, 4);
	while (i < postfix_n)
	{
		if (OR_PARSER_N(AND_PARSER_N(MULTIPLY_PARSER_N(parser, i), 0), 0)->retained)
		{
			f_redirec[ft_get_redirec_number(OR_PARSER_N(AND_PARSER_N(MULTIPLY_PARSER_N(parser, i), 0), 0))]
				(OR_PARSER_N(AND_PARSER_N(MULTIPLY_PARSER_N(parser, i), 0), 0));
		}
		i++;
	}
	return (1);
}
