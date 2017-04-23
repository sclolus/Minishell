/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:06:56 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/23 08:39:39 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AST_H__
# define __AST_H__
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef uint32_t	t_id;

# define CHECK(x) do {  ft_putendl("___"); \
ft_putendl(#x);			\
ft_putendl("____");		} while (0);

# define PARSER_TYPE(t_parser) t_parser->id
# define IS_RETAINED(t_parser) t_parser->retained == 1
# define OR_PARSER_N(t_parser, n) t_parser->parser.or.parsers[n]
# define AND_PARSER_N(t_parser, n) t_parser->parser.and.parsers[n]
# define OR_N(t_parser) t_parser->parser.or.n
# define AND_N(t_parser) t_parser->parser.and.n
# define PLUS_N(t_parser) t_parser->parser.plus.n
# define MULTIPLY_N(t_parser) t_parser->parser.multiply.n
# define PLUS_PARSER_N(t_parser, n) t_parser->parser.plus.parsers[n]
# define MULTIPLY_PARSER_N(t_parser, n) t_parser->parser.multiply.parsers[n]


# define UNRETAINED 0
# define RETAINED 1

# define MPC_PARSING_METACHAR "\"\'|*+()/<>[]"
# define METACHAR_STACKSIZE 4096

# define TO_BE_USED 1
# define USED 2

# define ALONE 0
# define GROUPED 1

typedef struct	s_metachar_stack
{
	uint32_t	offset;
	uint32_t	prec;
	uint32_t	used;
	char		c;
}				t_metachar_stack;

typedef struct	s_parser t_parser;

typedef enum	e_id
{
	UNDEFINED = 0,
	REF,
	ONECHAR,
	STRING,
	REGEXP,
	RANGE,
	ANY,
	STR_ANY_OF,
	SATISFY,
	SATISFY_STR,
	STR_ANY,
	ONEOF,
	FUNC,
	AND,
	OR,
	NOT,
	PLUS,
	MULTIPLY,
}				t_e_id;

typedef struct	s_mpc_ref
{
	char	*rule_name;
}				t_mpc_ref;

typedef struct	s_mpc_onechar
{
	char	c;
}				t_mpc_onechar;

typedef struct	s_mpc_str_any_of
{
	char	*charset;
	char	*str;
}				t_mpc_str_any_of;

typedef struct	s_mpc_any
{
	char	matched;
}				t_mpc_any;

typedef struct	s_mpc_str_any
{
	char		*str;
	t_parser	*end;
	uint32_t	len;
}				t_mpc_str_any;

typedef struct	s_mpc_str
{
	char		*str;
	uint32_t	len;
}				t_mpc_str;

typedef struct	s_mpc_regexp
{
	char	*regexp;
}				t_mpc_regexp;

typedef struct	s_mpc_and_n
{
	t_parser	**parsers;
	uint32_t	n;
}				t_mpc_and_n;

typedef struct	s_mpc_or_n
{
	t_parser	**parsers;
	uint32_t	n;
	int32_t		matched;
}				t_mpc_or_n;

typedef struct	s_mpc_not
{
	t_parser	*parser;
}				t_mpc_not;

typedef struct	s_mpc_char_range
{
	char	start;
	char	end;
	char	matched;
}				t_mpc_char_range;

typedef struct	s_mpc_satisfy
{
	int32_t		(*f)(char);
	char		c;
}				t_mpc_satisfy;

typedef struct	s_mpc_satisfy_str
{
	int32_t		(*f)(char*);
}				t_mpc_satisfy_str;

typedef struct	s_mpc_plus
{
	t_parser	*parser;
	t_parser	**parsers;
	uint32_t	n;
}				t_mpc_plus;

typedef struct	s_mpc_multiply
{
	t_parser	*parser;
	t_parser	**parsers;
	uint32_t	n;
}				t_mpc_multiply;

typedef struct	s_mpc_oneof
{
	char	*charset;
	char	c;
}				t_mpc_oneof;

typedef struct	s_mpc_func
{
	t_parser	*parser;
	t_parser	*(*gene)(void);
	uint32_t	(*f)(t_parser*, char **);
}				t_mpc_func;

typedef struct	s_mpc_recursive
{
	t_parser	*ref;
	t_parser	*parser;
}				t_mpc_recursive;

typedef union	s_mpc
{
	t_mpc_onechar		onechar;
	t_mpc_str_any_of	str_any_of;
	t_mpc_ref			ref;
	t_mpc_str			string;
	t_mpc_regexp		regexp;
	t_mpc_and_n			and;
	t_mpc_or_n			or;
	t_mpc_char_range	range;
	t_mpc_any			any;
	t_mpc_satisfy		satisfy;
	t_mpc_satisfy_str	satisfy_str;
	t_mpc_not			not;
	t_mpc_plus			plus;
	t_mpc_func			func;
	t_mpc_oneof			oneof;
	t_mpc_multiply		multiply;
	t_mpc_str_any		str_any;

}				t_mpc;

typedef struct	s_parser
{
	t_mpc	parser;
	char	*name;
	t_e_id	id;
	char	retained;
	char	alloc;
}				t_parser;


typedef struct	s_eval_parser
{
	uint32_t	(*f)(t_parser*, char **);
}				t_eval_parser;

typedef struct	s_free_parser
{
	void	(*f)(t_parser*);
}				t_free_parser;

t_parser		*ft_get_undefined_parser(void);
t_parser		*ft_get_parser_str_any(void);
t_parser		*ft_get_parser_plus(t_parser *parser);
t_parser		*ft_get_parser_multiply(t_parser *parser);
t_parser		*ft_get_parser_onechar(char c);
t_parser		*ft_get_parser_str_any_of(char *charset);
t_parser		*ft_get_parser_str(char *str);
t_parser		*ft_get_parser_range(char start, char end);
t_parser		*ft_get_parser_and_n(uint32_t n, t_parser **parsers);
t_parser		*ft_get_parser_or_n(uint32_t n, t_parser **parsers);
t_parser		*ft_get_parser_any(void);
t_parser		*ft_get_parser_satisfy(int32_t (*f)(char));
t_parser		*ft_get_parser_satisfy_str(int32_t (*f)(char*));
t_parser		*ft_get_parser_not(t_parser *parser);
t_parser		*ft_get_parser_oneof(char *charset);
t_parser		*ft_get_parser_ref(char *rule_name);
t_parser		*ft_get_parser_func(t_parser *(*generator)(void), uint32_t (*f)(t_parser*, char **));

t_parser		*ft_get_parser_whitespace(void);
t_parser		*ft_get_parser_grammar(void);
t_parser		*ft_get_parser_term(void);
t_parser		*ft_get_parser_literal(void);
t_parser		*ft_get_parser_invocations(void);
t_parser		*ft_get_parser_rule_name(void);
t_parser		*ft_get_parser_list(void);
t_parser		*ft_get_parser_expression(void);
t_parser		*ft_get_parser_line_end(void);
t_parser		*ft_get_parser_rule(void);
t_parser		*ft_get_parser_syntax(void);

uint32_t		ft_eval_input(t_parser *parser, char **string);
uint32_t		ft_eval_input_file(uint32_t fd, t_parser *parser);
uint32_t		ft_eval_parser(t_parser *parser, char **string);
uint32_t		ft_eval_parser_onechar(t_parser *parser, char **string);
uint32_t		ft_eval_parser_str(t_parser *parser, char **string);
uint32_t		ft_eval_parser_any(t_parser *parser, char **string);
uint32_t		ft_eval_parser_char_range(t_parser *parser, char **string);
uint32_t		ft_eval_parser_undefined(t_parser *parser, char **string);
uint32_t		ft_eval_parser_not(t_parser	*parser, char **string);
uint32_t		ft_eval_parser_str_any(t_parser *parser, char **string);
uint32_t		ft_eval_parser_str_any_of(t_parser *parser, char **string);
uint32_t		ft_eval_parser_or(t_parser	*parser, char **string);
uint32_t		ft_eval_parser_and(t_parser	*parser, char **string);
uint32_t		ft_eval_parser_satisfy(t_parser *parser, char **string);
uint32_t		ft_eval_parser_satisfy_str(t_parser *parser, char **string);
uint32_t		ft_eval_parser_plus(t_parser *parser, char **string);
uint32_t		ft_eval_parser_multiply(t_parser *parser, char **string);
uint32_t		ft_eval_parser_oneof(t_parser *parser, char **string);
uint32_t		ft_eval_delayed(t_parser *parser, char **string);

t_parser		*ft_get_grammar_literal(t_parser *literal);
t_parser		*ft_get_grammar_term(t_parser *term);
t_parser		*ft_get_grammar_list(t_parser *list);
t_parser		*ft_get_grammar_or_n(uint32_t n, t_parser *first, t_parser **parsers);
t_parser		*ft_get_grammar_sub_expression(t_parser *sub_expression);
t_parser		*ft_get_grammar_expression(t_parser *expression);
t_parser		*ft_get_grammar_rule(t_parser *rule);
t_parser		*ft_get_grammar_syntax(t_parser *syntax);
t_parser		*ft_find_rule_name(t_parser **ruleset, char *name);
void			ft_link_rule_name(t_parser **ruleset, t_parser **node);

void			ft_free_parser(t_parser *parser);
void			ft_free_parser_onechar(t_parser *parser);
void			ft_free_parser_ref(t_parser *parser);
void			ft_free_parser_str_any_of(t_parser *parser);
void			ft_free_parser_any(t_parser *parser);
void			ft_free_parser_str_any(t_parser *parser);
void			ft_free_parser_str(t_parser *parser);
void			ft_free_parser_regexp(t_parser *parser);
void			ft_free_parser_and_n(t_parser *parser);
void			ft_free_parser_or_n(t_parser *parser);
void			ft_free_parser_plus(t_parser *parser);
void			ft_free_parser_multiply(t_parser *parser);
void			ft_free_parser_char_range(t_parser *parser);
void			ft_free_parser_satisfy(t_parser *parser);
void			ft_free_parser_satisfy_str(t_parser *parser);
void			ft_free_parser_oneof(t_parser *parser);
void			ft_free_parser_func(t_parser *parser);
void			ft_free_parser_func(t_parser *parser);
void			ft_free_parser_undefined(t_parser *parser);

void			ft_optimizer(t_parser *parser);

uint32_t		ft_eval_parser_invocations(t_parser *parser, char **string);
int32_t			ft_is_alpha(char c);

t_parser		*ft_grammar(char *grammar);
uint32_t		ft_count_metachar(char *start, char *end);
int32_t			ft_count_rules(char *grammar);

t_parser		*ft_dup_parser(t_parser *parser);

void			ft_put_parser(t_parser *parser);
void			ft_put_id(t_parser *parser);
void			ft_set_name_parser(t_parser *parser, char *str);
void			ft_put_parser_tree(t_parser *parser);
void			ft_put_ast_tokens(t_parser *parser);

int32_t			ft_save_parser(char	*filename, t_parser *parser);
#endif
