/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 06:13:51 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/03 14:04:11 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void		ft_put_ast_tokens(t_parser *parser)
{
	uint32_t	i;

	i = 0;
	if (!parser->retained)
		return ;
	if (parser->id == OR)
	{
		while (i < parser->parser.or.n)
		{
			ft_put_ast_tokens(parser->parser.or.parsers[i]);
			i++;
		}
	}
	else if (parser->id == AND)
	{
		while (i < parser->parser.and.n)
		{
			ft_put_ast_tokens(parser->parser.or.parsers[i]);
			ft_putchar(' ');
			i++;
		}
	}
	else if (parser->id == PLUS)
	{
		while (i < parser->parser.plus.n)
		{
			ft_put_ast_tokens(parser->parser.plus.parsers[i]);
			ft_putchar(' ');
			i++;
		}
	}
	else if (parser->id == MULTIPLY)
	{
		while (i < parser->parser.plus.n)
		{
			ft_put_ast_tokens(parser->parser.plus.parsers[i]);
			ft_putchar(' ');
			i++;
		}
	}
	else if (parser->id == FUNC)
		ft_put_ast_tokens(parser->parser.func.parser);
	else
	{
		switch (parser->id)
		{
		case ONECHAR:
			ft_putchar(parser->parser.onechar.c);
			break;
		case STRING:
			ft_putstr(parser->parser.string.str);
			break;
		case ANY:
			ft_putchar(parser->parser.any.matched);
			break;
		case SATISFY:
			ft_putstr("SATISFY");
			break;
		case STR_ANY:
			ft_putstr(parser->parser.str_any.str);
			break;
		case ONEOF:
			ft_putchar(parser->parser.oneof.c);
			break;
		case STR_ANY_OF:
			ft_putstr(parser->parser.str_any_of.str);
			break;
		default :
			ft_putstr("broken");
			ft_putnbr(parser->id);
			break;
		}
	}
}

uint32_t	ft_count_depth(t_parser *parser)
{
	uint32_t	ret;
	uint32_t	tmp;
	uint32_t	i;

	ret = 0;
	i = 0;
	if (parser->id >= AND)
	{
		if (parser->id == AND || parser->id == OR)
		{
			while (i < parser->parser.and.n)
			{
/*				ft_putnbr(i);
				ft_putchar(' ');*/
				tmp = ft_count_depth(parser->parser.and.parsers[i]);
				ret = ret < tmp ? tmp : ret;
				i++;
			}
			return (ret + 1);
		}
		else
			return (ft_count_depth(parser->parser.plus.parser) + 1);
	}
	else
		return (1);
}

void	ft_put_tree_level(t_parser *parser, uint32_t level)
{
	uint32_t	i;

	i = 0;
	if (level > 0)
	{
/*		if (parser->name)
		ft_putstr(parser->name);*/
		if (parser->id >= AND)
		{
			if (parser->name)
				if (!ft_strcmp(parser->name, "<sp>"))
					return ;
			if (parser->id == AND || parser->id == OR)
			{
				if (level == 1)
					ft_putchar('(');
				while (i < parser->parser.and.n)
				{
					ft_put_tree_level(parser->parser.and.parsers[i], level - 1);
					i++;
				}
				if (level == 1)
					ft_putchar(')');
			}
/*			else if (parser->id == PLUS || parser->id == MULTIPLY)
			{
				while (i < parser->parser.plus.n)
				{
					ft_put_tree_level(parser->parser.plus.parsers[i], level - 1);
					i++;
				}
				}*/
			else
				ft_put_tree_level(parser->parser.plus.parser, level - 1);
		}
	}
	else
	{
		if (parser->name)
			ft_putstr(parser->name);
		if (parser->id == ONECHAR)
		{
			if (parser->parser.onechar.c == ' ')
				ft_putchar('_');
			else if (parser->parser.onechar.c == '\t')
				ft_putstr("tab");
			else if (parser->parser.onechar.c == '\n')
				ft_putstr("\\n");
			else
			{
				if (parser->retained)
					ft_putchar('~');
				ft_putchar(parser->parser.onechar.c);
			}
		}
		else if (parser->id == STRING)
			ft_putstr(parser->parser.string.str);
		else if (parser->id == FUNC)
		{
			ft_put_id(parser);
			if (!parser->parser.func.parser)
				ft_putchar(';');
		}
		else
			ft_put_id(parser);
		ft_putnbr(parser->retained);
			ft_putchar('\t');
	}
}

void	ft_put_parser_tree(t_parser *parser)
{
	uint32_t		max_depth;
	uint32_t		i;
	uint32_t		u;

	max_depth = ft_count_depth(parser);
	ft_putnbr(max_depth);
	i = 0;
	while (i < max_depth)
	{
		u = 0;
		while (u++ + i< max_depth / 2)
			ft_putchar('\t');
		ft_put_tree_level(parser, i);
		u = 0;
		while (u++ + i < max_depth / 2)
			ft_putchar('\t');
		ft_putchar('\n');
		i++;
	}
}

void	ft_put_id(t_parser *parser)
{
	if (!parser)
	{
		ft_putstr("NULL");
		return;
	}
	switch (parser->id)
	{
	case ONECHAR:
		ft_putstr("ONECHAR");
		ft_putchar(parser->parser.onechar.c);
		break;
	case STRING:
		ft_putstr("STRING");
		break;
	case AND:
		ft_putstr("&&");
		break;
	case OR:
		ft_putstr("|");
		break;
	case ANY:
		ft_putstr("ANY");
		break;
	case SATISFY:
		ft_putstr("SATISFY");
		break;
	case STR_ANY:
		ft_putstr("STR_ANY");
		break;
	case PLUS:
		ft_putstr("+");
		break;
	case MULTIPLY:
		ft_putstr("*");
		break;
	case FUNC:
		ft_putstr("FUNC");
		break;
	case REF:
		ft_putstr("REF");
		break;
	case ONEOF:
		ft_putstr("ONEOF");
		break;
	case STR_ANY_OF:
		ft_putstr("STR_ANY_OF");
		break;
	default :
	ft_putstr("broken");
		ft_putnbr(parser->id);
		break;
	}
}

void	ft_put_parser(t_parser *parser)
{
	uint32_t	i;

	i = 0;
//	ft_put_id(parser);
	if (parser->id == OR)
	{
		ft_put_id(parser);
		ft_putnbr(parser->parser.or.n);
//		ft_putstr("| ");
		ft_putchar('\n');
		while (i < parser->parser.or.n)
		{
				ft_put_id(parser->parser.or.parsers[i]);
			ft_putchar('\t');
			ft_put_parser(parser->parser.or.parsers[i]);
			i++;
		}
	}
	else if (parser->id == AND)
	{
//		ft_putstr("& ");
		ft_put_id(parser);
		ft_putnbr(parser->parser.and.n);
		ft_putchar('\n');
		while (i < parser->parser.and.n)
		{
//			printf("%d \n", parser->parser.or.parsers[i]->id);
			ft_put_id(parser->parser.and.parsers[i]);
			ft_putchar('\t');
			ft_put_parser(parser->parser.or.parsers[i]);
			i++;
		}
	}
	else if (parser->id == PLUS)
	{
		ft_put_id(parser);
		ft_putchar('\t');
		ft_putchar('\n');
		ft_put_id(parser->parser.plus.parser);
		ft_putchar('\t');
		ft_put_parser(parser->parser.plus.parser);
		ft_putchar('\n');
	}
	else if (parser->id == MULTIPLY)
	{
		ft_put_id(parser);
		ft_putchar('\n');
		ft_put_id(parser->parser.multiply.parser);
		ft_put_parser(parser->parser.plus.parser);
		ft_putchar('\n');
	}
	else
//		ft_putstr("node ");
		;
}
