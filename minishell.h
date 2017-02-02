#ifndef __MINISHELL_H__
# define __MINISHELL_H__

# include "libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/signal.h>
# include <signal.h>
# include <stdlib.h>

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

# define MAX_PATH 4096

typedef union	s_token_union
{
	char	*token;
	char	**tokens;
}				t_token_union;

typedef struct	s_token
{
	int32_t			type;
	t_token_union	token;
}				t_token;	

typedef struct	s_btree
{
	void			*content;
	struct s_btree	*left;
	struct s_btree	*right;
}				t_btree;

void		ft_sighandler(int signum);
char		*ft_find_command(char *filename, char **path);

char		**ft_parse_line(char *line);
char		*ft_parse_arg(char *line);
void		ft_normalize_command(char **command);
char		**ft_lexer(char *command_line, char **env);

char		**ft_preparse(char **tokens, char **env);
uint32_t	ft_count_abstract_tokens(char **tokens);
char		*ft_variable_expansion(char *token, char **env);
t_btree		*ft_parser(char **tokens, char **env);
t_token		*ft_sanitize_tokens(t_token *tokens_tab, uint32_t count);

uint32_t	ft_get_branches_count(t_token *tokens, uint32_t count);
void		ft_put_ast(t_btree *tree);
t_btree		*ft_add_ast_node(t_token *tokens, uint32_t index, t_btree *tree);
t_btree		*ft_arrange_tree(t_btree *nodes, uint32_t count);
t_btree		*ft_get_ast_tree(t_token *tokens, uint32_t count);

void		ft_echo(char **argv);
int32_t		ft_buildin(char *filename, char **argv, char **env, t_list **env_lst);
int32_t		ft_cd(char **argv, t_list **env);
char		*ft_find_env(char const **env, char const *variable);
int32_t		ft_execve(char *filename, char *path, char **argv, char **env);

t_btree		*ft_btreenew(void *content, uint32_t content_size);
char		*ft_strjoin_f(char *a, char *b, int32_t mode);

t_list		*ft_get_lstenv(char **env);

int32_t		ft_putenv(t_list *env, char **argv);
int32_t		ft_unsetenv(t_list **env, char const **argv);
int32_t		ft_setenv(t_list **env, char const **argv);
t_list		*ft_find_lst_env(t_list *env, char const *variable);
t_list		*ft_get_lstenv(char **env);

void		*ft_lsttotab_token(t_list *lst, unsigned int len);
#endif
