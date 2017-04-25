/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 22:56:18 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/25 16:05:07 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL_H__
# define __MINISHELL_H__

# include "libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/signal.h>
# include <dirent.h>
# include <signal.h>
# include <stdlib.h>
# include "termcaps.h"
# include "ft_completion.h"
# include "ast.h"

// debuf MACROS
# define ENDL ft_putendl("");
#define REVERT 0

# define PROMPT "$>"
# define SHELL_NAME "minishell: "
# define ECHO_FLAGS "n" // obsolete


# define TOKEN_OR "||"
# define TOKEN_AND "&&"
# define TOKEN_SINGLE_AND "&"
# define TOKEN_PIPE "|"
# define TOKEN_END_OF_STATEMENT ";"
# define TOKEN_LEFT_REDIRECTION "<"
# define TOKEN_RIGHT_REDIRECTION ">"
# define TOKEN_HEREDOC "<<"
# define TOKEN_RIGHT_APPEND ">>"

# define TOKEN_COUNT 9

# define TYPE_TOKEN_OR 1
# define TYPE_TOKEN_AND 2
# define TYPE_TOKEN_SINGLE_AND 3
# define TYPE_TOKEN_PIPE 4
# define TYPE_TOKEN_END_OF_STATEMENT 5
# define TYPE_TOKEN_LEFT_REDIRECTION 6
# define TYPE_TOKEN_RIGHT_REDIRECTION 7
# define TYPE_TOKEN_HEREDOC 8
# define TYPE_TOKEN_RIGHT_APPEND 9

# define TYPE_TOKEN_STATEMENT 10
# define TYPE_TOKEN_START_OF_STATEMENT 11

# define CHARSET_SPECIAL_CHAR "|&<>;*?"
# define CHARSET_SPECIAL_DELIMITORS "(|&<>; )"
# define CHARSET_LOGICAL "&|"
# define CHARSET_END_OF_EXPRESSION " ;"
# define ESCAPE_CHAR "\\"
# define CHARSET_VAR_NAME "_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

# define MAX_PATH_NAME 4096
# define MAX_FILE_NAME 255
# define MAX_PATH 4096
# define MAX_VAR_NAME 1024

# define EXIT_NO_PERM 126
# define EXIT_ILLEGAL_CMD 127
# define EXIT_REDIREC_ERROR 55
# define EXIT_SIG_ERROR 11
# define EXIT_VAR_NOT_FOUND 56
# define EXIT_HEREDOC_FILE 57

# define POSIX_EXIT_STATUS(x) (x & 0xFF)

# define BUILT_IN_COUNT 9

typedef struct s_env t_env;
typedef uint8_t	t_bool;
typedef struct	s_shenv t_shenv;
typedef struct	s_shell	t_shell;

t_shell		*shell;

typedef struct	s_heredoc
{
	char	*filename;
	char	*delimiter;
}				t_heredoc;

typedef struct	s_shenv
{
	t_env		*env;
	char		**var;
	t_bool		*attr;	
	uint32_t	count;
	t_list		*heredocs;
	uint32_t	heredocs_count;
}				t_shenv;

typedef struct	s_built_in
{
	char	*id;
	int32_t	(*f)(char **, t_shenv*);
}				t_built_in;

typedef struct	s_env
{
	char		**env;
	uint32_t	variable_count;
}				t_env;

typedef struct	s_process
{
	struct s_process	*next;
	struct s_process	*prev;
	pid_t				pid;
	pid_t				gpid;
	char				**argv;
}				t_process;

typedef struct	s_job
{
	struct s_job	*next;
	t_parser		*cmd;
	t_process		*processes;
	pid_t			pgid;
}				t_job;

typedef struct	s_shell
{
	int				terminal;
	int				interactive;
	pid_t			shell_pgid;
	struct termios	backup_term;
}				t_shell;

int32_t		ft_setup_sighandlers(void);
void		ft_init_shell(void);

char		*ft_find_command(char *filename, char **path);
/*char		**ft_parse_line(char *line);
char		*ft_parse_arg(char *line);
void		ft_normalize_command(char **command);*/

int32_t		ft_is_unbalanced(char *line);
char		*ft_line_continuation(char *line);
int32_t		ft_is_line_backslash_terminated(char *line);

char		*ft_variable_expansion(char *token, char **env);

//int32_t		ft_cd(char **argv, t_list **env);
char		*ft_find_env(char const **env, char const *variable);
char		*ft_strjoin_f(char *a, char *b, int32_t mode);

uint32_t	ft_is_escaped(char *input, uint32_t index);
uint32_t	ft_is_quoted(char *input, uint32_t index);

void	ft_exit_shell(void);

/*
** Lexer
*/

char		**ft_lexer(char *input);
t_tokens	*ft_get_tokens(char *input);
void		ft_put_tokens(char **tokens);
uint32_t	ft_get_tokens_count(char **tokens);
void		ft_free_tokens(t_tokens *tokens);

/*
** redirections
*/

typedef int32_t (*t_redirec)(t_parser*);

int32_t		ft_redirections(t_parser *redirect);
int32_t		ft_output_redirect(t_parser *redirect);
int32_t		ft_output_append_redirect(t_parser *redirect);
int32_t		ft_duplicating_input_redirect(t_parser *redirect);
int32_t		ft_duplicating_output_redirect(t_parser *redirect);
int32_t		ft_input_redirect(t_parser *redirect);
int32_t		ft_read_write_redirect(t_parser *redirect);

/*
** expansions
*/

int32_t		ft_expansions(t_parser *simple_cmd, t_shenv *env);
void		ft_var_expansion(char **word, t_shenv *shenv);
void		ft_quote_removal(char **word);
void		ft_tilde_expansion(char **word, t_shenv *env);
int32_t		ft_find_file(char *filename, t_env *env);
char		*ft_get_file_name(char *file);
char		*ft_get_path_name(char *file);
void		ft_expansions_cmd_prefix(t_parser *cmd_prefix, t_shenv *shenv);
void		ft_expansions_cmd_postfix(t_parser *cmd_postfix, t_shenv *shenv);
void		ft_expansions_io_filename(t_parser *io_filename, t_shenv *shenv);
void		ft_expansions_io_number(t_parser *io_number, t_shenv *shenv);
void		ft_expansions_io_redirect(t_parser *io_redirect, t_shenv *shenv);
void		ft_expansions_io_file(t_parser *io_file, t_shenv *shenv);

/*
** built_ins
*/

int32_t		ft_built_in_echo(char **argv, t_shenv *shenv);
int32_t		ft_built_in(char **argv, t_shenv *shenv);
int32_t		ft_built_in_cd(char **argv, t_shenv *shenv);
int32_t		ft_built_in_history(char **argv, t_env *env);
int32_t		ft_built_in_exit(char **argv, t_shenv *shenv);
int32_t		ft_built_in_setenv(char **argv, t_shenv *shenv);
int32_t		ft_built_in_env(char **argv, t_shenv *shenv);
int32_t		ft_built_in_unsetenv(char **argv, t_shenv *shenv);
int32_t		ft_built_in_export(char **argv, t_shenv *shenv);
int32_t		ft_built_in_unset(char **argv, t_shenv *shenv);

/*
** Error handling
*/

void		ft_error_exit(uint32_t n, char **str, int32_t exit_status);
int32_t		ft_error(uint32_t n, char **str, int32_t return_status);

/*
** Permissions/files checks
*/

int32_t	ft_check_exec_perm(char *pathname);
int32_t	ft_check_exec_read(char *pathname);
int32_t	ft_check_exec_write(char *pathname);
int32_t	ft_is_dir(char *pathname);

/*
** Shell environnement management
*/

t_shenv		*ft_init_shenv(uint32_t argc, char **env);
t_env		*ft_get_env(t_shenv *shenv);
char		**ft_find_var(t_shenv *shenv, char *var);
int32_t		ft_shenv_get_env_count(t_shenv *shenv);
uint32_t	ft_get_env_count(char **env);

t_bool		ft_is_var_exported_index(t_shenv *shenv, uint32_t index);
t_bool		ft_is_var_exported(t_shenv *shenv, char *var);
t_bool		ft_set_var_to_export(t_shenv *shenv, char *var);

void		ft_modify_var(t_shenv *shenv, char *var);
void		ft_add_var(t_shenv *shenv, char *var);
int32_t		ft_unset_var(t_shenv *shenv, char *var);

void		ft_free_t_env(t_env *env);
void		ft_free_t_shenv(t_shenv *shenv);

/*
** Signal Handling
*/

int32_t		ft_setup_sighandlers(void);
void		ft_reset_signals(void);
void		ft_ignore_signals(void);

/*
** Miscellaneous Free functions
*/

void	ft_free_argv(char **argv);

/*
** Processes
*/

void		ft_clear_processes(t_process **processes);
void		ft_t_process_print(t_process *process);
void		ft_put_processes_in_foreground(t_process *process, int cont);

/*
** Term setup
*/

int32_t		ft_unset_term(void);
int32_t		ft_set_term(void);
int32_t		ft_unset_echo_mode(void);
int32_t		ft_set_echo_mode(void);
int32_t		ft_set_canonical_mode(void);
int32_t		ft_unset_echoctl_mode(void);

/*
** Shell utilities
*/

void	ft_put_shell_in_foreground(void);
void	ft_exit_shell(void);
void	ft_init_shell(void);

/* test*/
int32_t		ft_is_built_in(t_parser *parser);
t_process	*ft_start_process(t_parser *simple_cmd, pid_t gpid, int *stdfd, t_shenv *shenv);
int32_t		ft_exec_pipeline(t_parser *parser, t_shenv *shenv);
int32_t		ft_exec_pipe_sequence(t_parser *parser, t_shenv *shenv);
int32_t		ft_exec_and_or(t_parser *parser, t_shenv *shenv);
int32_t		ft_exec_env_assignment(t_parser *parser, t_shenv *shenv);
int32_t		ft_exec_cmd_prefix(t_parser *cmd_prefix, t_shenv *shenv);
void		ft_exec_cmd(char **argv, t_shenv *shenv);
int32_t		ft_exec_simple_cmd(t_parser *simple_cmd, t_shenv *shenv);
int32_t		ft_exec_command(t_parser *parser, t_shenv *shenv);
int32_t		ft_exec_parser(t_parser *parser, t_shenv *shenv);
char		**ft_get_env_value(char **env, char *variable);
t_process	*ft_t_process_add(t_process **processes, t_process *new);

void		ft_create_heredocs(t_tokens *tokens, t_shenv *shenv);
void		ft_clear_heredoc(t_list *heredoc);
void		ft_put_heredocs(t_shenv *shenv);

#endif
