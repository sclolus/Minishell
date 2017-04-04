/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 12:05:23 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/31 02:28:36 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast.h>

int main(int argc, char **argv)
{

	if (argc || argv)
	{};
/*
	if (ft_grammar("number \"number\" : /[0-9]+/ ;\
expression      : <product> ((\'+\' | \'-\') <product>)* ;\
product         : <value> ((\'*\' | \'/\') <value>)* ;\
value           : <number> | \'(\' <expression> \')\' ;\
maths           : /^/ <expression> /$/ ;"))
		ft_putstr("\n");
	else
	ft_putstr("lol");*/
//	ft_parser(argv[1]);
//	ft_get_parser_grammar();
	t_parser	*parser;

//	ft_putstr("salut");
	int32_t	fd;

	if ((fd = open("grammar.txt", O_RDONLY)) < 0)
	{
		ft_putnbr(fd);
		exit (EXIT_FAILURE);
	}
	parser = ft_get_parser_grammar();

/*	parser = ft_get_parser_and_n(3, (t_parser*[]){ft_get_parser_and_n(2, (t_parser*[]){ft_get_parser_whitespace(), ft_get_parser_onechar('g')})
	s, ft_get_parser_str("loli"), ft_get_parser_str("#tor")});*/
//	ft_dup_parser(parser);
	// ft_put_parser_tree(ft_dup_parser(parser));
	char		*test;
	t_parser	*new_parser;

/*	test = ft_strdup("<command> ::= (<spe> <list> <spe> <separator> <spe>)+ | <list> \n	\
					  <list>	::= (<name> <spe> (<and_or>)* <spe>)+ \n\
					  <name>	::= ('a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z')+ \n\
					  <and_or>	::= \"&&\" | \"||\" \n\
					  <separator> ::= ';' | '&' \n\
					  <spe>		::= (' ' | '\t')* \n");*/
	if (!(test = ft_strdup("<command>		::= <sp> <list> <sp> <separator> <sp> | <sp> <list> <sp> \n\
							   <list>			::= (<simple_cmd> <sp> <and_or> <sp>)* <simple_cmd> \n\
							   <simple_cmd>		::= <command_name> <sp> (<arg> <sp>)* \n\
							   <command_name>	::= ('a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z')+ \n\
							   <arg>			::= ('a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z')+ \n\
							   <and_or>			::= \"&&\" | \"||\" \n\
							   <sp>				::= (\' \' | \'\t\')* \n\
							   <separator>		::= \'&\' | \';\' \n")))
		exit(EXIT_FAILURE);
	char	*input;
	if (!(input = ft_strdup("ls les gens &&  super toto du ; turfu")))
		exit (EXIT_FAILURE);
	if (ft_eval_input(parser, &test))
	{
		new_parser = ft_get_grammar_syntax(parser);
		ft_optimizer(new_parser);
		ft_put_parser_tree(new_parser);
		if (ft_eval_input(new_parser, &input))
		{
			ft_put_parser_tree(new_parser);
			printf("\n\n\n\n");
			ft_put_ast_tokens(new_parser);

		}
		else
		{
			ft_putstr("\nfail\n");
			exit(EXIT_FAILURE);
		}
		ft_free_parser(new_parser);
	}
	else
	{
		ft_putstr("lol");
		exit(EXIT_FAILURE);
	}
	ft_free_parser(parser);
# if 0
	char		*base;
	char		*string;
	char		*shell_syntax;
	t_parser	*new_parser;


	// string = ft_strdup("<expression> ::= \"loli\" \"is for seb\" | \"fbi is coming\" '1' \n");
	// string = ft_strdup("<expr> ::= <num><sp>\"toto\"<sp><loli>\n\
	// <num> ::= ('1' | '2' | '3' | '4' |'5' |'6' |'7' |'8' |'9' |'0' | <hexa>)+ \n\
	// <hexa> ::= 'a' | 'b' | 'c' | 'd'| 'e'| 'f'\n\
	// <loli> ::= \"loli\"\n\
	// <sp> ::= (' ' | '\t')*\n");
/*	shell_syntax = ft_strdup("<complete_command> ::= <list> <separator> | list \n \
						<list>             ::= <list> <separator_op> <and_or> |  and_or \n\
						<and_or>           ::= <pipeline> | <and_or> <AND_IF> <linebreak> <pipeline> \n\ | <and_or> <OR_IF> <linebreak> <pipeline> \n\
						<pipeline>         ::= <pipe_sequence> | <Bang> <pipe_sequence> \n\
						<pipe_sequence>    ::= <command> | <pipe_sequence> '|' <linebreak> <command> \n\
						<command>          ::= <simple_command> | <compound_command> | <compound_command> <redirect_list> | <function_definition> \n\
						<compound_command> ::= <brace_group> | <subshell> | <for_clause> | <case_clause> | <if_clause> | <while_clause> | <until_clause> \n\
						<subshell>         ::= '(' <compound_list> ')' \n\
						<compound_list>    ::= <term> | <newline_list> <term> | <term> <separator> | <newline_list> <term> <separator> \n\
						<term>             ::= <term> <separator> <and_or> | <and_or> \n\
						<for_clause>       ::= <For> <name> <linebreak> <do_group> | <For> <name> <linebreak> <in> <sequential_sep> <do_group> | <For> <name> <linebreak> <in> <wordlist> <sequential_sep> <do_group> \n\
						<name>             ::= <NAME>                     \n\
						<in>               ::= <In>                        \n\
						<wordlist>         ::= <wordlist> WORD | WORD \n\
						<case_clause>      ::= <Case> WORD <linebreak> <in> <linebreak> <case_list> \"Esac\" | <Case> WORD <linebreak> <in> <linebreak> <case_list_ns> <Esac> | <Case> WORD <linebreak> <in> <linebreak> \"Esac\" \n\
						<case_list_ns>     ::= <case_list> <case_item_ns> | <case_item_ns> \n\
						<case_list>        ::= <case_list> <case_item> | <case_item> \n\
						<case_item_ns>     ::= <pattern> ')' <linebreak> | <pattern> ')' <compound_list> <linebreak> | '(' <pattern> ')' <linebreak> | '(' <pattern> ')' <compound_list> <linebreak> \n\
						<case_item>        ::= <pattern> ')' <linebreak> ';' <linebreak> |     <pattern> ')' <compound_list> ';' <linebreak> | '(' <pattern> ')' <linebreak> ';' <linebreak> | '(' <pattern> ')' <compound_list> ';' <linebreak> \n\
						<pattern>          ::=             WORD          | <pattern> '|' WORD          \n\
						<if_clause>        ::= \"if\" <compound_list> \"then\" <compound_list> else_part \"fi\" | \"if\" <compound_list> \"then\" <compound_list> \"fi\" \n\
						<else_part>        ::= \"elif\" <compound_list> \"then\" <else_part> | \"else\" <compound_list> \n\
						<while_clause>     ::= \"while\" <compound_list> <do_group> \n\
						<until_clause>     ::= \"until\" <compound_list> <do_group> \n\
						<function_definition> ::= <fname> '(' ')' <linebreak> <function_body> \n\
						<function_body>    ::= <compound_command>                 | <compound_command> <redirect_list>   \n\
						<fname>            ::= NAME                            \n\
						<brace_group>      ::= \'{\' <compound_list> \'}\' \n\
						<do_group>         ::= \"do\" <compound_list> \"done\"           \n\
						<simple_command>   ::= <cmd_prefix> <cmd_word> <cmd_suffix> | <cmd_prefix> <cmd_word> | <cmd_prefix> | <cmd_name> <cmd_suffix> | <cmd_name> \n\
						<cmd_name>         ::= WORD                   \n\
						<cmd_word>         ::= WORD                    \n\
						<cmd_prefix>       ::= <io_redirect> | <cmd_prefix> <io_redirect> |            ASSIGNMENT_WORD | <cmd_prefix> ASSIGNMENT_WORD \n\
						<cmd_suffix>       ::= <io_redirect> | <cmd_suffix> <io_redirect> |            WORD | <cmd_suffix> WORD \n\
						<redirect_list>    ::= <io_redirect> | <redirect_list> <io_redirect> \n\
						<io_redirect>      ::= <io_file> | IO_NUMBER <io_file> | <io_here> | IO_NUMBER <io_here> \n\
						<io_file>          ::= '<' <filename> | LESSAND <filename> | '>' <filename> | GREATAND  <filename> | DGREAT <filename> | LESSGREAT <filename> | CLOBBER   <filename> \n\
						<filename>         ::= WORD                      \n\
						<io_here>          ::= DLESS     <here_end> | DLESSDASH <here_end> \n\
						<here_end>         ::= NAME \n\
						<newline_list>     ::=              NEWLINE | <newline_list> NEWLINE \n\
						<linebreak>        ::= <newline_list> \n\
						<separator_op>     ::= '&' | ';' \n\
						<separator>        ::= <separator_op> <linebreak> | <newline_list> \n\
					 <sequential_sep>   ::= ';' <linebreak>\n");*/*/ */

#endif
	return (0);
}
