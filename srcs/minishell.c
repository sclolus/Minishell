#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"

t_process	*current_process = NULL; // not used

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

// TODO ctrl+d ctrl+c

int main(int argc, char **argv, char **env)
{
	char		*line;
	t_parser	*bnf_parser;
	t_parser	*parser;
	char		*grammar;

	line = NULL;
	if (argc || argv)
	{};
	ft_init_shell();
/*							   <env_assignment>	::= <var_name> '=' <var_value> \n\
							   <var_name>		::= ('A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '0' | '1' | '2' | '3 ' | '4' | '5' | '6' | '7' | '8' | '9')+ \n\
							   <var_value>		::= ('A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '0' | '1' | '2' | '3 ' | '4' | '5' | '6' | '7' | '8' | '9' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z')+ \n\
*/
#if _POSIX_JOB_CONTROL
	ft_putstr_fd("posix job control", 2);
# endif
#if 1
	# define test 1
# if test == 1
	if (!(grammar = ft_strdup("<command>		::= <sp> <list> <sp> \n\
							   <list>			::= (<and_or> <sp> <separator> <sp>)+ | (<and_or> <sp> <separator> <sp>)* <and_or> \n\
							   <and_or>			::= (<sp> \"&&\" <sp> <pipeline> | <sp> \"||\" <sp> <pipeline> | <sp> <pipeline>)+\n\
							   <simple_cmd>		::= <sp> (<cmd_prefix>)* <command_name> <sp> (<cmd_postfix> <sp>)*  | (<cmd_prefix>)+ <sp>\n\
							   <cmd_postfix>	::= <io_redirect> | <arg> \n\
							   <cmd_prefix>		::= <env_assignment> <sp> | <io_redirect> <sp> \n\
							   <pipeline>		::= <pipe_sequence> | '!' <pipe_sequence> \n\
							   <pipe_sequence>	::= (<simple_cmd> '|')+ <simple_cmd> | <simple_cmd> \n\
							   <io_redirect>	::= <io_number> <io_file> | <io_file> \n\
							   <io_number>		::= ('$' | '-' | '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')+ \n\
							   <io_file>        ::= \'>\' <io_filename> | \">&\" <sp> <io_number> | \'<\' <io_filename> | \"<&\" <sp> <io_number> | \"<<\" <io_filename> | \"<>\" <io_filename> | \">>\" <io_filename> | \">|\" <io_filename> \n\
							   <io_filename>	::= <sp> ('\\' | '$' | '-' | '/' | '.' | '~'| 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z')+ \n\
							   <env_assignment>	::= <var_name> '=' <var_value> \n\
							   <var_name>		::= ('_' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')+ \n\
							   <var_value>		::= ('\\' | '_' | '$' | '~' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z')+ \n\
							   <command_name>	::= ('\\' | ' ' | '\'' | '\"' | '_' | '$' | '~'| '.' | '/' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z'| '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')+ \n\
							   <arg>			::= ('\\' |' ' | ':' | '_' | '=' | '$' | '\'' | '\"' | '-' | '/' | '.' | '~' | 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z' | 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y' | 'Z' | '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')+ \n\
							   <sp>				::= (\' \' | \'\t\')* \n\
							   <separator>		::= \'&\' | \';\' \n")))
		exit(EXIT_FAILURE);
#endif


	bnf_parser = ft_get_parser_syntax();
	if (!ft_eval_input(bnf_parser, &grammar))
	{
		ft_putstr_fd("Grammar evaluation failed", 2);
		exit (EXIT_FAILURE);
	}
	parser = ft_get_grammar_syntax(bnf_parser);
	ft_optimizer(parser);
	t_shenv	*shenv;
	t_tokens	*tokens;

	shenv = ft_init_shenv(ft_get_env_count(env), env);
	ft_putchar('\n');
	while (1)
	{
		ft_putstr("$>");
		ft_termget_complete_line(&line, shenv);
		if (!*line)
			continue ;
		if (!ft_strcmp(line, "exit"))
			break ;
		char	*tmp;
		tmp = line;
		if (!(tokens = ft_get_tokens(line)))
			exit(EXIT_FAILURE);
		ft_put_tokens(tokens->tokens);
		if (ft_eval_tokens_input(parser, tokens))
		{
			ft_put_ast_tokens(parser);
			ft_putendl("");
//			ft_create_heredocs(tmp, shenv);
//			ft_put_heredocs(shenv);
			ft_exec_parser(parser, shenv);
		}
		else
		{
			ft_putendl("parsing error ::= ");
			ft_put_ast_tokens(parser);
			CHECK(TOKENS ^);
			}
//		ft_sanitize_parser(parser);
	}
	ft_exit_shell();
	exit(EXIT_FAILURE);
#endif
	ft_putstr("test");
	return (0);
}
