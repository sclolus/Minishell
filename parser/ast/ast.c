/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:05:18 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/02 02:34:49 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int32_t		ft_is_metachar(char c)
{
	if (ft_strchr(MPC_PARSING_METACHAR, c))
		return (1);
	else
		return (0);
}

int32_t		ft_is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z'));
}

t_parser	*ft_get_parser_whitespace(void)
{
	t_parser	*parser;

	parser = ft_get_parser_multiply(ft_get_parser_or_n(2
													   , (t_parser *[]){ft_get_parser_onechar(' ')
															   , ft_get_parser_onechar('\t')}));
	ft_set_name_parser(parser, "<whitespace>");
	return (parser);
}

t_parser	*ft_get_parser_term(void)
{
	t_parser	*parser;

	parser = ft_get_parser_or_n(3, (t_parser *[]){ft_get_parser_literal(),
													ft_get_parser_rule_name(),
													ft_get_parser_invocations()});
	ft_set_name_parser(parser, "<term>");
	return (parser);
}

t_parser	*ft_get_parser_literal(void)
{
	t_parser	*parser;

	parser = ft_get_parser_or_n(2, (t_parser *[]){
				ft_get_parser_and_n(3, (t_parser *[]){ft_get_parser_onechar('\"')
							, ft_get_parser_str_any(), ft_get_parser_onechar('\"')})
					, ft_get_parser_and_n(3, (t_parser *[]){ft_get_parser_onechar('\'')
								, ft_get_parser_any(), ft_get_parser_onechar('\'')})});
	if (!(parser->name = ft_strdup("<parser_literal>")))
		exit(EXIT_FAILURE);

	return (parser);
}

t_parser	*ft_get_parser_rule_name(void)
{
	t_parser	*parser;

	parser = ft_get_parser_and_n(3, (t_parser *[]){ft_get_parser_onechar('<')
					, ft_get_parser_str_any()
					, ft_get_parser_onechar('>')});
	if (!(parser->name = ft_strdup("<rule_name>")))
		exit(EXIT_FAILURE);
	return (parser);
}

// list optimisable
t_parser	*ft_get_parser_list(void)
{
	t_parser	*parser;

	parser = ft_get_parser_plus(ft_get_parser_and_n(2,
		(t_parser *[]){ft_get_parser_term(), ft_get_parser_whitespace()}));
	if (!(parser->name = ft_strdup("<list>")))
		exit(EXIT_FAILURE);
	return (parser);
}

t_parser	*ft_get_parser_invocations(void)
{
	t_parser	*parser;

	parser = ft_get_parser_and_n(8, (t_parser *[]){ft_get_parser_whitespace(), ft_get_parser_onechar('(')
					, ft_get_parser_whitespace(), ft_get_parser_func(&ft_get_parser_expression, &ft_eval_delayed)
					, ft_get_parser_whitespace(), ft_get_parser_onechar(')'), ft_get_parser_oneof("+*"), ft_get_parser_whitespace()});
	ft_set_name_parser(parser, "<invocations>");
	return (parser);
}

t_parser	*ft_get_parser_expression(void)
{
	t_parser	*parser;

	parser = ft_get_parser_plus(ft_get_parser_and_n(2,(t_parser *[])
			{ft_get_parser_list(),
			ft_get_parser_multiply(ft_get_parser_and_n(4,(t_parser *[])
						{ft_get_parser_whitespace(),
						ft_get_parser_onechar('|'),
						ft_get_parser_whitespace(),
						ft_get_parser_list()}))
			}));
	if (!(parser->name = ft_strdup("<expression>")))
		exit(EXIT_FAILURE);
	return (parser);
}

t_parser	*ft_get_parser_line_end()
{
	t_parser	*eol;

	eol = ft_get_parser_and_n(2, (t_parser *[]){ft_get_parser_whitespace(), ft_get_parser_onechar('\n')});
	if (!(eol->name = ft_strdup("<eol>")))
		exit(EXIT_FAILURE);
	return (ft_get_parser_plus(eol));
}

t_parser	*ft_get_parser_rule(void)
{
	t_parser	*parser;
	parser = ft_get_parser_and_n(7, (t_parser*[]){ft_get_parser_whitespace(), ft_get_parser_rule_name()
					, ft_get_parser_whitespace(), ft_get_parser_str("::=")
				, ft_get_parser_whitespace(), ft_get_parser_expression(), ft_get_parser_line_end()});
	if (!(parser->name = ft_strdup("<rule>")))
		exit(EXIT_FAILURE);
	return (parser);
}

t_parser	*ft_get_parser_syntax(void)
{
	t_parser	*parser;

	parser = ft_get_parser_plus(ft_get_parser_rule());
	ft_set_name_parser(parser, "<syntax>");
	return (parser);
}

t_parser	*ft_get_parser_grammar(void)
{
	t_parser	*syntax;
	ft_putstr("dafuw");
	CHECK(bruh);
	syntax = ft_get_parser_syntax();
	return (syntax);
}

t_parser	*ft_get_undefined_parser(void)
{
	t_parser	*parser;

	if (!(parser = (t_parser*)malloc(sizeof(t_parser))))
		exit (EXIT_FAILURE);
	parser->id = UNDEFINED;
	parser->retained = UNRETAINED;
	parser->alloc = ALONE;
	parser->name = NULL;
	return (parser);
}

t_parser	*ft_get_parser_str_any(void)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->parser.str_any.len = 0;
	parser->parser.str_any.str = NULL;
	parser->id = STR_ANY;
	return (parser);
}

t_parser	*ft_get_parser_multiply(t_parser *parser)
{
	t_parser	*new;

	new = ft_get_undefined_parser();
	new->parser.multiply.parser = parser;
	new->parser.multiply.n = 0;
	new->id = MULTIPLY;
	return (new);
}

t_parser	*ft_get_parser_plus(t_parser *parser)
{
	t_parser	*new;

	new = ft_get_undefined_parser();
	new->parser.plus.parser = parser;
	new->parser.plus.n = 0;
	new->id = PLUS;
	return (new);
}

t_parser	*ft_get_parser_onechar(char c)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->parser.onechar.c = c;
	parser->id = ONECHAR;
	return (parser);
}

t_parser	*ft_get_parser_str(char *str)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	if (!(parser->parser.string.str = ft_strdup(str)))
		exit(EXIT_FAILURE);
	parser->parser.string.len = ft_strlen(str);
	parser->id = STRING;
	return (parser);
}

t_parser	*ft_get_parser_range(char start, char end)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = RANGE;
	parser->parser.range.start = start;
	parser->parser.range.end = end;
	return (parser);
}

t_parser	*ft_get_parser_and_n(uint32_t n, t_parser **parsers)
{
	t_parser	*parser;
	uint32_t	i;

	i = 0;
	parser = ft_get_undefined_parser();
	if (!(parser->parser.and.parsers = (t_parser**)malloc(sizeof(t_parser*) * n)))
		exit (EXIT_FAILURE);
	parser->parser.and.n = n;
	while (i < n)
	{
		parser->parser.and.parsers[i] = parsers[i];
		i++;
	}
	parser->id = AND;
	return (parser);
}

t_parser	*ft_get_parser_or_n(uint32_t n, t_parser **parsers)
{
	t_parser	*parser;
	uint32_t	i;

	i = 0;
	parser = ft_get_undefined_parser();
	if (!(parser->parser.or.parsers = (t_parser**)malloc(sizeof(t_parser*) * n)))
		exit (EXIT_FAILURE);
	parser->parser.or.n = n;
	while (i < n)
	{
		parser->parser.or.parsers[i] = parsers[i];
		i++;
	}
	parser->id = OR;
	parser->parser.or.matched = NULL;
	return (parser);
}

t_parser	*ft_get_parser_any(void)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = ANY;
	return (parser);
}

t_parser	*ft_get_parser_satisfy(int32_t (*f)(char))
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = SATISFY;
	parser->parser.satisfy.f = f;
	return (parser);
}

t_parser	*ft_get_parser_satisfy_str(int32_t (*f)(char*))
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = SATISFY_STR;
	parser->parser.satisfy_str.f = f;
	return (parser);
}

t_parser	*ft_get_parser_not(t_parser *parser)
{
	t_parser	*new_parser;

	new_parser = ft_get_undefined_parser();
	new_parser->id = NOT;
	new_parser->parser.not.parser = parser;
	return (parser);
}

t_parser	*ft_get_parser_oneof(char *charset)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = ONEOF;
	if (!(parser->parser.oneof.charset = ft_strdup(charset)))
		exit (EXIT_FAILURE);
	parser->parser.oneof.c = 0;
	return (parser);
}

//split parser set I/O modes
t_parser	*ft_get_parser_func(t_parser *(*generator)(void), uint32_t (*f)(t_parser*, char **))
{
	t_parser	*new_parser;

	new_parser = ft_get_undefined_parser();
	new_parser->id = FUNC;
	new_parser->parser.func.parser = NULL;
	new_parser->parser.func.f = f;
	new_parser->parser.func.gene = generator;
	return (new_parser);
}

t_parser	*ft_get_parser_ref(char *rule_name)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = REF;
	parser->parser.ref.rule_name = rule_name;
	return (parser);
}

void	ft_set_name_parser(t_parser *parser, char *str)
{
	if (!(parser->name = ft_strdup(str)))
		exit (EXIT_FAILURE);
}

t_parser	*ft_get_parser_str_any_of(char *charset)
{
	t_parser	*parser;

	parser = ft_get_undefined_parser();
	parser->id = STR_ANY_OF;
	parser->parser.str_any_of.charset = charset;
	parser->parser.str_any_of.str = NULL;
	return (parser);
}
