#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"

char		*ft_find_env(char const **env, char const *variable)
{
	uint32_t	i;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	while (*env)
	{
		if (!ft_strncmp(variable, *env, i))
			return ((char*)*env);
		else
			env++;
	}
	return (NULL);
}


char		**ft_get_env_value(char **env, char *variable)
{
	char		**path;
	char		*tmp;
	uint32_t	len;
	uint32_t	variable_len;

	path = NULL;
	tmp = NULL;
	variable_len = ft_strlen(variable);
	if (!(path = ft_strsplit(ft_find_env((char const**)env, variable), ':')))
		exit (EXIT_FAILURE);
	if (!(tmp = ft_strdup(*path)))
		exit(EXIT_FAILURE);
	len = ft_strlen(tmp) - variable_len - 1; 
	ft_strncpy(*path, tmp + variable_len + 1, len + 1);
	return (path);
}

int main(int argc, char **argv, char **env)
{
	char		*line;
	t_list		*env_lst;
	char		**env_tab;
	t_parser	*bnf_parser;
	t_parser	*parser;
	char		*grammar;

	line = NULL;
	if (argc || argv)
	{};
	if (ft_setup_sighandlers() == -1)
	{
		ft_putstr_fd("Signal handlers setup failed", 2);
		exit(EXIT_FAILURE);
	}
/*							   <env_assignment>	::= <var_name> '=' <var_value> \n\
							   <var_name>		::= ('A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '0' | '1' | '2' | '3 ' | '4' | '5' | '6' | '7' | '8' | '9')+ \n\
							   <var_value>		::= ('A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '0' | '1' | '2' | '3 ' | '4' | '5' | '6' | '7' | '8' | '9' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z')+ \n\
*/
#if _POSIX_JOB_CONTROL
	ft_putstr("posix job control");	
# endif
#if 1
	# define test 1
# if test
	if (!(grammar = ft_strdup("<command>		::= <sp> <list> <sp> \n\
							   <list>			::= (<and_or> <sp> <separator> <sp>)* <and_or> <sp> (<separator>)* | <and_or> <sp> (<separator>)* \n\
							   <and_or>			::= (<sp> \"&&\" <sp> <simple_cmd> | <sp> \"||\" <sp> <simple_cmd> | <sp> <simple_cmd>)+\n\
							   <simple_cmd>		::= <sp> (<cmd_prefix>)* <command_name> <sp> (<cmd_postfix> <sp>)*  | <cmd_prefix> <sp>\n\
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
							   <separator>		::= \'&\' | \';\' \n")))
		exit(EXIT_FAILURE);
#elif test == 0
	if (!(grammar = ft_strdup("<expression> ::= \"||\"\n")))
		exit (EXIT_FAILURE);
#endif

	int32_t	fd;

	if ((fd = open("grammar.txt", O_RDONLY)) <= 0)
		exit(EXIT_FAILURE);
	bnf_parser = ft_get_parser_syntax();
	if (!ft_eval_input(bnf_parser, &grammar))
	{
		ft_putstr_fd("Grammar evaluation failed", 2);
		exit (EXIT_FAILURE);
	}
	parser = ft_get_grammar_syntax(bnf_parser);
	ft_optimizer(parser);
	if (!(env_lst = ft_get_lstenv(env)))
		exit(EXIT_FAILURE);
	if (ft_set_term() == -1)
		exit(EXIT_FAILURE);
	t_env	s_env;
	s_env.env = env;
	while (1)
	{
		ft_putstr("\n$>");
		ft_termget_complete_line(&line);
		if (!*line)
			continue ;
		if (!ft_strcmp(line, "exit"))
			break ;
		if (ft_eval_input(parser, &line))
		{
			ft_put_ast_tokens(parser);
/*			ft_putendl("");
			ft_exec_parser(parser, &s_env);*/
		}
		else
		{
			ft_putendl("parsing error ::= ");
			ft_put_ast_tokens(parser);
		}
//		line = ft_line_continuation(line);
		
		if (!(env_tab = ft_lsttotab_token(env_lst, ft_lstlen(env_lst))))
			exit (EXIT_FAILURE);
		free(env_tab);
	}
	if (ft_set_term() == -1)
		exit(EXIT_FAILURE);
#endif
	ft_putstr("test");
	return (0);
}
