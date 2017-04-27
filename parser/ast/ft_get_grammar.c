/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 04:43:56 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/27 06:35:46 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_parser	*ft_get_grammar_literal(t_parser *literal)
{
	t_parser	*parser;
	t_parser	*tmp;

	if (literal->parser.or.parsers[0]->retained)
	{
		tmp = literal->parser.or.parsers[0]->parser.and.parsers[1];
		parser = ft_get_parser_str(tmp->parser.str_any.str);
	}
	else if (literal->parser.or.parsers[1]->retained)
	{
		tmp = literal->parser.or.parsers[1]->parser.and.parsers[1];
		parser = ft_get_parser_onechar(tmp->parser.any.matched);
	}
	else
	{
		ft_putstr_fd("Error\n", 2);
		return (NULL);
	}
	return (parser);
}

t_parser	*ft_find_rule_name(t_parser **ruleset, char *name)
{
	uint32_t			i;

	i = 0;
	while (ruleset[i])
	{
		if (!ft_strcmp(ruleset[i]->name, name))
			return (ruleset[i]);
		++i;
	}
	ft_putstr_fd(name, 2);
	ft_putstr_fd("not found", 2);
	exit(EXIT_FAILURE);
}

void		ft_link_rule_name(t_parser **ruleset, t_parser **node)
{
	t_parser	*parser;
	uint32_t	i;

	i = 0;
	if ((*node)->id == REF)
	{
		parser = ft_find_rule_name(ruleset, (*node)->parser.ref.rule_name);
		// free((*node));
		*(node) = ft_dup_parser(parser);
	}
	if ((*node)->id >= AND)
	{
		if ((*node)->id == AND || (*node)->id == OR)
		{
			while (i < (*node)->parser.and.n)
			{
				ft_link_rule_name(ruleset, &((*node)->parser.and.parsers[i]));
				++i;
			}
		}
		else
			ft_link_rule_name(ruleset, &((*node)->parser.not.parser));
	}
	else
		return ;
}

t_parser	*ft_get_grammar_term(t_parser *term)
{
	if (term->parser.or.parsers[0]->retained)
		return (ft_get_grammar_literal(term->parser.or.parsers[0]));
	else if (term->parser.or.parsers[1]->retained)
	{
		return (ft_get_parser_ref(
					term->parser.or.parsers[1]->parser.and.parsers[1]->parser.str_any.str));
	}
	else
	{
		if (term->parser.or.parsers[2]->parser.and.parsers[6]->parser.oneof.c == '*')
			return (ft_get_parser_multiply(ft_get_grammar_expression(
											   term->parser
											   .or.parsers[2]->parser.and.parsers[3]->parser.func.parser)));
		else
			return (ft_get_parser_plus(ft_get_grammar_expression(
										   term->parser.or.parsers[2]->parser.and.parsers[3]->parser.func.parser)));
	}
}

t_parser	*ft_get_grammar_list(t_parser *list)
{
	t_parser	*parser;
	t_parser	**parsers;
	uint32_t	i;

	i = 0;
	if (list->parser.plus.n == 1)
		return (ft_get_grammar_term(list->parser.plus.parsers[0]->parser.and.parsers[0]));
	if (!(parsers = (t_parser**)malloc(sizeof(t_parser*)
									   * list->parser.plus.n)))
		exit(EXIT_FAILURE);
	while (i < list->parser.plus.n)
	{
		parsers[i] = ft_get_grammar_term(list->parser.plus.parsers[i]->parser.and.parsers[0]);
		i++;
	}
	parser = ft_get_parser_and_n(list->parser.plus.n, parsers);
	free(parsers);
	return (parser);
}

t_parser	*ft_get_grammar_or_n(uint32_t n, t_parser *first, t_parser **parsers)
{
	t_parser	*parser;
	uint32_t	i;

	i = 0;
	parser = ft_get_undefined_parser();
	parser->id = OR;
	parser->parser.or.matched = -1;
	if (!(parser->parser.or.parsers = (t_parser**)malloc(sizeof(t_parser*) * n)))
		exit (EXIT_FAILURE);
	parser->parser.or.n = n;
	parser->parser.or.parsers[0] = ft_get_grammar_list(first);
	while (i + 1 < n)
	{
		parser->parser.or.parsers[i + 1] = ft_get_grammar_list(parsers[i]->parser.and.parsers[3]);
		i++;
	}
	return (parser);
}

t_parser	*ft_get_grammar_sub_expression(t_parser *sub_expression)
{
	uint32_t	size;


	size = sub_expression->parser.and.parsers[1]->parser.multiply.n;
	if (size)
	{
		return (ft_get_grammar_or_n(size + 1, sub_expression->parser.and.parsers[0]
									, sub_expression->parser.and.parsers[1]->parser.multiply.parsers));
	}
	else
		return (ft_get_grammar_list(sub_expression->parser.and.parsers[0]));
}

t_parser	*ft_get_grammar_expression(t_parser *expression)
{
	t_parser	*parser;
	t_parser	**parsers;
	uint32_t	i;

	i = 0;
	if (expression->parser.plus.n == 1)
		return (ft_get_grammar_sub_expression(expression->parser.plus.parsers[0]));
	if (!(parsers = (t_parser**)malloc(sizeof(t_parser*) * expression->parser.plus.n)))
		exit(EXIT_FAILURE);
	while (i < expression->parser.plus.n)
	{
		parsers[i] = ft_get_grammar_sub_expression(expression->parser.plus.parsers[i]);
		i++;
	}
	parser = ft_get_parser_and_n(expression->parser.plus.n, parsers);
	free(parsers);
	return (parser);
}

t_parser	*ft_get_grammar_rule(t_parser *rule)
{
	t_parser	*parser;

	parser = ft_get_grammar_expression(rule->parser.and.parsers[5]);
	parser->name = ft_strndup(rule->parser.and.parsers[1]->parser.and.parsers[1]->parser.str_any.str
							  , rule->parser.and.parsers[1]->parser.and.parsers[1]->parser.str_any.len);
	return (parser);
}

t_parser	*ft_get_grammar_syntax(t_parser *syntax)
{
	t_parser	*parser;
	t_parser	**parsers;
	uint32_t	i;

	i = 0;
	if (!(parsers = (t_parser**)malloc((syntax->parser.plus.n + 1) * sizeof(t_parser*))))
		exit(EXIT_FAILURE);
	while (i < syntax->parser.plus.n)
	{
		parsers[i] = ft_get_grammar_rule(syntax->parser.plus.parsers[i]);
		i++;
	}
	parsers[i] = NULL;
	parser = ft_get_parser_plus(parsers[0]);
	ft_set_name_parser(parser, "syntax");
	i = 0;
	while (parsers[i])
		ft_link_rule_name(parsers, &parsers[i++]);
	i = 1;
	while (parsers[i])
		ft_free_parser(parsers[i++]);
	free(parsers);
	return (parser);
}
