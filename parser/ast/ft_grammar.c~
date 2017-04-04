/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grammar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 03:13:00 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/12 07:40:18 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int32_t	ft_count_rules(char *grammar)
{
	uint32_t	i;
	uint32_t	count;
	uint32_t	quotes;
	uint32_t	semi_colon;

	semi_colon = 0;
	count = 0;
	quotes = 0;
	i = 0;
	while (grammar[i])
	{
		if (grammar[i] == '\'')
			quotes ^= 0b01;
		else if (grammar[i] == '\"')
			quotes ^= 0b10;
		else if (grammar[i] == ':' && !semi_colon && !quotes)
		{
			count++;
			semi_colon ^= 1;
		}
		else if (grammar[i] == ':')
			return (-1);
		else if (grammar[i] == ';' && semi_colon && !quotes)
			semi_colon ^= 1;
		else if (grammar[i] == ';')
			return (-1);
		i++;
	}
	return (count);
}

/*
*** Not safe, need checks on rule existence
*/

uint32_t		ft_count_metachar(char *start, char *end)
{
	uint32_t	count;

	count = 0;
	while (start < end)
		if (ft_strchr(MPC_PARSING_METACHAR, *start++))
			count++;
	return (count);
}

uint32_t ft_assign_prec(char c)
{
	if (c == '(' || c == ')')
		return (0);
	else if (c == '/')
		return (1);
	else if (c == '[' || c == ']')
		return (2);
	else if (c == '|')
		return (3);
	else if (c == '\'' || c == '\"' || c == '<' || c == '>')
		return (4);
	else if (c == '*' || c == '+')
		return (41);
	exit(EXIT_FAILURE);
	return (0);
}

int32_t			ft_fill_metachar_stack(t_metachar_stack *stack, char *start
									   , char *end)
{
	uint32_t	i;
	uint32_t	quotes;

	i = 0;
	quotes = 0;
	while (start < end)
	{
		if (*start == '\'' && quotes != 0b10)
			quotes ^= 0b01;
		else if (*start == '\"' && quotes != 0b01)
			quotes ^= 0b10;
		if (ft_strchr(MPC_PARSING_METACHAR, *start) && !quotes)
		{
			stack[i].c = *start;
			stack[i].prec = ft_assign_prec(*start);
			ft_putchar(*start);
			stack[i++].offset = end - start;
		}
		start++;
	}
	stack[i].c = 0;
	if (quotes)
		return (-1);
	return (i);
}
t_metachar_stack	**ft_find_separators(t_metachar_stack *stack,
												uint32_t prec_range)
{
	uint32_t i = 0;
	uint32_t u = 0;
	int32_t size = 0;
	uint32_t level = 42;
	int32_t paren = 0;
	t_metachar_stack	**ret;

	while (stack[i].c)
	{
		printf("%c size = %u\n", stack[i].c, size);

		if (!stack[i].c || stack[i].prec <= prec_range)
		{
			printf("	end of range\n");
			if (size++)
				break;
			else
				return (NULL);
		}
		paren -= stack[i].c == ')' ? 1 : 0;
		if (stack[i].prec < level)
		{
			size = 0;
			level = stack[i].prec;
			printf("	new level set = %d\n", level);
		}
		if (stack[i].prec == level && !paren)
		{
			printf("	added\n");
			++size;
		}
		paren += stack[i].c == '(' ? 1 : 0;
		++i;
	}
	if (!(ret = ft_memalloc(sizeof(t_metachar_stack *) * (size + 1))))
		exit(EXIT_FAILURE);
		printf("alloc\n" );
	i = 0;
	while (size > 0)
	{
		printf("%c size = %u\n", stack[i].c, size);
		paren -= stack[i].c == ')' ? 1 : 0;
		if (stack[i].prec == level && !paren)
		{
			printf("	added\n");
			ret[u++] = stack + i;
			--size;
		}
		paren += stack[i].c == '(' ? 1 : 0;
		++i;
	}
	for (size_t llo = 0; ret[llo]; llo++) {
		printf("%p > stack[%u] = %c\n", ret[llo], llo, ret[llo]->c);
	}
	return (ret);
}
// t_metachar_stack	**ft_find_separators(t_metachar_stack *stack,
// 												uint32_t prec_level)
// {
// 	//returns a tab of all the metachar corresponding to Plevel or higher if not found
// 	// */+ added when the metachar preceding it is added
// 	// null if no metachar to add
//
// 	uint32_t i, u;
// 	uint32_t level;
// 	uint32_t size;
// 	int32_t paren = 0;
// 	t_metachar_stack	**ret;
//
// 	i = 0;
// 	u = 0;
// 	size = 0;
// 	level = 0;
// 	while (stack[i].c && level <= 0)
// 	{
// 		paren -= stack[i].c == ')' ? 1 : 0;
// 		if (!stack[i].c)
// 		{
// 			i = 0;
// 			level--;
// 		}
// 		if (stack[i].prec <= prec_level)
// 		{
// 			if (size)
// 				break;
// 			else
// 			{
// 				i = 0;
// 				level++;
// 			}
// 		}
// 		if (stack[i].prec < level)
// 		{
// 			size = 0;
// 			level = stack[i].prec;
// 		}
// 		if (stack[i].prec == level && !paren)
// 			size++;
// 		paren += stack[i].c == '(' ? 1 : 0;
// 		++i;
// 	}
// 	printf("lv = %u, size = %u\n", level, size);
// 	if (!(ret = ft_memalloc(sizeof(t_metachar_stack *) * (size + 1))))
// 		exit(EXIT_FAILURE);
// 	i = 0;
// 	while (stack[i].c && !size)
// 	{
// 		paren -= stack[i].c == ')' ? 1 : 0;
// 		if (stack[i].prec == level && !paren)
// 		{
// 			ret[u++] = stack + i;
// 			--size;
// 		}
// 		paren += stack[i].c == '(' ? 1 : 0;
// 		++i;
// 	}
// 	fflush(NULL);
//
// 	return (ret);
// }

void	ft_parser_insert(t_parser *main, t_parser *sub)
{
	return;
}

t_parser		*ft_generate_parser(t_metachar_stack *start, char *grammar,
									uint32_t prec)
{
	t_parser	*p;
	t_metachar_stack	**separators;

	p = NULL;

	if (!(separators = ft_find_separators(start, prec))) //null if no subnode to make
	{
		//need to handle whitespace = && here
		// ft_set_parser_value(p, start, grammar);
		printf("leaf at c%u %c\n", start->offset, start->c);
		return (p);
	}
	for (size_t i = 0; separators[i]; i++) {
		printf("%c", separators[i]->c);
	}
	printf("\n");
	// p = ft_set_parser_type(separators);
	// //metaword associated with */+ make adequate type
	// //paren without mod make generic << delete at optimisation
	// //if no separator list, realloc needed to extend parser
	while (*separators)
	{
		printf("toto\n" );
		// if ((*separators)->c == ('+' || '*'))
		if (*separators != start)
		{
			printf("parsing start %p, %p,\n", *separators + 1, start);
			ft_parser_insert(p, ft_generate_parser(start, grammar, (*separators)->prec));
		}
		else
		{
			if (*separators + 1 == *(separators + 1))

			printf("parsing %p\n", *separators + 1);
			ft_parser_insert(p, ft_generate_parser(*separators + 1, grammar,
			(*separators)->c == '(' ? 0 : (*separators)->prec));

		}	// 	continue;
		// free(*separators);
		++separators;
	}

	// free(separators);
	return (p);
}


t_parser		*ft_get_next_rule(char **grammar)
{
	static t_metachar_stack	metachar_stack[METACHAR_STACKSIZE];
	t_parser				*parser;
	char					*name;
	char					*definition;

	//parser = ft_get_parser_or_n(1, NULL);
	name = ft_strchr(*grammar, ':');
	definition = ft_strstr(*grammar, ";\
");
	ft_fill_metachar_stack(metachar_stack, name, definition);
	ft_putchar('\n');
	parser = ft_generate_parser(metachar_stack, *grammar, 0);

	*grammar = ++definition;
	ft_bzero(metachar_stack, sizeof(metachar_stack));
	return (parser);
}

t_parser	*ft_grammar(char *grammar)
{
	int32_t		count;
	t_parser	**parsers;

	if ((count = ft_count_rules(grammar)) == -1)
		return (NULL);
	if (!(parsers = (t_parser**)malloc(sizeof(t_parser*) * (count + 1))))
		exit (EXIT_FAILURE);
	// ft_putnbr(count);
	parsers[count] = NULL;
	// while (--count >= 0)
		parsers[count] = ft_get_next_rule(&grammar);
	return ((void*)1);
}
