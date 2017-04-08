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
# include "ast.h"
// debuf MACROS
# define ENDL ft_putendl("");
#define REVERT 0


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

# define MAX_PATH_NAME 4096
# define MAX_FILE_NAME 255
# define MAX_PATH 4096

# define EXIT_NO_PERM 126
# define EXIT_ILLEGAL_CMD 127
# define EXIT_REDIREC_ERROR 55

# define BUILT_IN_COUNT 9

typedef struct s_env t_env;

typedef struct	s_built_in
{
	char	*id;
	int32_t	(*f)(char **, t_env*);
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
	char				**argv;
}				t_process;

typedef struct	s_job
{
	struct s_job	*next;
	t_parser		*cmd;
	t_process		*processes;
	pid_t			pgid;
}				t_job;

int32_t		ft_setup_sighandlers(void);

char		*ft_find_command(char *filename, char **path);
char		**ft_parse_line(char *line);
char		*ft_parse_arg(char *line);
void		ft_normalize_command(char **command);

int32_t		ft_is_unbalanced(char *line);
char		*ft_line_continuation(char *line);
int32_t		ft_is_line_backslash_terminated(char *line);

char		**ft_lexer(char *command_line, char **env);

char		**ft_preparse(char **tokens, char **env);
uint32_t	ft_count_abstract_tokens(char **tokens);
char		*ft_variable_expansion(char *token, char **env);
t_btree		*ft_parser(char **tokens, char **env);
t_token		*ft_sanitize_tokens(t_token *tokens_tab, uint32_t count);

uint32_t	ft_get_branches_count(t_token *tokens, uint32_t count);
void		ft_put_ast(t_btree *tree);
t_btree		*ft_add_ast_node(t_token *tokens, t_btree *tree);
t_btree		*ft_arrange_tree(t_btree *nodes, uint32_t count);
t_btree		*ft_get_ast_tree(t_token *tokens, uint32_t count);

int32_t		ft_cd(char **argv, t_list **env);
char		*ft_find_env(char const **env, char const *variable);
int32_t		ft_exec_ast(t_btree *tree, char **env, char **path);
int32_t		ft_exec_f(t_btree *tree, char **env, char **path
				  , int32_t (*f)(t_btree*, char**, char**));
int32_t		ft_execve(char *filename, char *path, char **argv, char **env);
int32_t		ft_exec_statement(t_btree *tree, char **env, char **path);
int32_t		ft_exec_statement_no_fork(t_btree *tree, char **env, char **path);
int32_t		ft_exec_token_or(t_btree *tree, char **env, char **path);
int32_t		ft_exec_token_and(t_btree *tree, char **env, char **path);
int32_t		ft_exec_asynchronous_statement(t_btree *tree, char **env, char **path);
int32_t		ft_exec_token_single_and(t_btree *tree, char **env, char **path);
int32_t		ft_exec_token_pipe(t_btree *tree, char **env, char **path);

t_btree		*ft_btreenew(void *content, uint32_t content_size);
char		*ft_strjoin_f(char *a, char *b, int32_t mode);

t_list		*ft_get_lstenv(char **env);

int32_t		ft_putenv(t_list *env, char **argv);
int32_t		ft_unsetenv(t_list **env, char const **argv);
int32_t		ft_setenv(t_list **env, char const **argv);
t_list		*ft_find_lst_env(t_list *env, char const *variable);
t_list		*ft_get_lstenv(char **env);

void		*ft_lsttotab_token(t_list *lst, unsigned int len);

uint32_t	ft_is_escaped(char *input, uint32_t index);
uint32_t	ft_is_quoted(char *input, uint32_t index);

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

int32_t		ft_expansions(t_parser *simple_cmd, t_env *env);
void		ft_tilde_expansion(char **word, t_env *env);
int32_t		ft_find_file(char *filename, t_env *env);
char		*ft_get_file_name(char *file);
char		*ft_get_path_name(char *file);

/*
** built_ins
*/

int32_t		ft_built_in_echo(char **argv, t_env *env);
int32_t		ft_built_in(char **argv, t_env *env);
int32_t		ft_built_in_history(char **argv, t_env *env);
int32_t		ft_built_in_exit(char **argv, t_env *env);


void		ft_error_exit(uint32_t n, char **str, int32_t exit_status);
int32_t		ft_error(uint32_t n, char **str, int32_t return_status);
/* test*/

t_process	*ft_start_process(t_parser *simple_cmd, pid_t gpid, int *stdfd, t_env *env);
int32_t	ft_exec_pipeline(t_parser *parser, t_env *env);
int32_t	ft_exec_and_or(t_parser *parser, t_env *env);
int32_t	ft_exec_env_assignment(t_parser *parser, t_env *env);
void	ft_exec_cmd(char **argv, t_env *env);
void	ft_exec_simple_cmd(char **argv, t_parser *parser, t_env *env);
int32_t	ft_exec_command(t_parser *parser, t_env *env);
int32_t	ft_exec_parser(t_parser *parser, t_env *env);
char		**ft_get_env_value(char **env, char *variable);
#endif
