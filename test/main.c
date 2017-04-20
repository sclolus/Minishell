/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 06:20:48 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/19 06:49:03 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_parser	*bnf;
	t_shenv		*shenv;
	t_process	*process;

	shenv = ft_init_shenv(ft_get_env_count(env), env);
	ft_start_process
	# if 0
	bnf = ft_get_grammar_syntax();
	if (!ft_eval_parser(bnf, " <simple_cmd>		::= <sp> (<cmd_prefix>)* <command_name> <sp> (<cmd_postfix> <sp>)*  | <cmd_prefix> <sp>\n\
							   <cmd_postfix>	::= <io_redirect> | <arg> \n\
							   <cmd_prefix>		::= <env_assignment> <sp> | <io_redirect> <sp> \n \
							   <pipeline>		::= <pipe_sequence> | '!' <pipe_sequence> \n\
							   <pipe_sequence>	::= <simple_cmd> | (<simple_cmd> '|')+ <simple_cmd> \n\
							   <io_redirect>	::= <io_number> <io_file> | <io_file> \n\
							   <io_number>		::= ('0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')+ \n\
							   <io_file>        ::= \'>\' <io_filename> | \">&\" <sp> <io_number> | \'<\' <io_filename> | \"<&\" <sp> <io_number> | \"<<\" <io_filename> | \"<>\" <io_filename> | \">>\" <io_filename> | \">|\" <io_filename> \n\
							   <io_filename>	::= <sp> ('/' | '.' | '~'| 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z')+ \n\
							   <env_assignment>	::= <var_name> '=' <var_value> \n\
							   <var_name>		::= ('A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')+ \n\
							   <var_value>		::= ('~' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z')+ \n\
							   <command_name>	::= ('~'| '.' | '/' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z')+ \n\
							   <arg>			::= ('\'' | '\"' | '-' | '/' | '.' | '~' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')+ \n\
							   <sp>				::= (\' \' | \'\t\')* \n\
							   <separator>		::= \'&\' | \';\' \n"))
	{
		ft_putstr_fd("Grammar evaluation failed", 2);
		exit (EXIT_FAILURE);
	}
	t_parser *parser = ft_get_grammar_syntax(bnf_parser);
	ft_optimizer(parser);
	char		*line;
	uint32_t	i = 1;
	line = ft_strnew(0);
	while (i < argc - 1)
	{
		line = ft_strjoin_f(line, argv[i], 0);
		i++;
	}
	if (!(ft_eval_parser(parser, &line)))
	{
		ft_putstr_fd("syntax error");
		exit(EXIT_FAILURE);
	}
	ft_exec_pipeline(parser);
	#endif
	return (0);
}
