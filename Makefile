NAME= minishell
CC= gcc
FLAGS= -Wall -Werror -Wextra -g #   -fsanitize=address -fsanitize-blacklist=my_ignores.txt
SRC= srcs/minishell.c \
	srcs/ft_init_shell.c \
	srcs/ft_signal.c \
	srcs/ft_signal_handlers.c \
	srcs/ft_find_command.c \
	srcs/ft_built_in_echo.c \
	srcs/ft_built_in.c \
	srcs/ft_built_in_cd.c \
	srcs/ft_built_in_cd2.c \
	srcs/ft_built_in_exit.c \
	srcs/ft_built_in_env.c \
	srcs/ft_built_in_setenv.c \
	srcs/ft_built_in_unsetenv.c \
	srcs/ft_built_in_unset.c \
	srcs/ft_built_in_export.c \
	srcs/ft_shenv.c \
	srcs/ft_env.c \
	srcs/ft_var_attr.c \
	srcs/ft_env.c \
	srcs/ft_lsttotab_token.c \
	srcs/ft_is_quoted.c \
	srcs/ft_line_continuation.c \
	srcs/ft_expansions.c \
	srcs/ft_var_expansion.c \
	srcs/ft_quote_removal.c \
	srcs/ft_expansions_cmd_prefix.c \
	srcs/ft_expansions_cmd_postfix.c \
	srcs/ft_expansions_io_redirect.c \
	srcs/ft_built-in_history.c \
	srcs/ft_exec_command.c \
	srcs/ft_exec_parser.c \
	srcs/ft_exec_pipeline.c \
	srcs/ft_create_pipeline.c \
	srcs/ft_exec_simple_cmd.c \
	srcs/ft_process.c \
	srcs/ft_error.c \
	srcs/ft_redirection.c \
	srcs/ft_redirections_input.c \
	srcs/ft_redirections_output.c \
	srcs/ft_redirections_duplicating.c \
	srcs/ft_heredocs.c \
	srcs/ft_create_heredocs.c \
	srcs/ft_free_heredocs.c \
	srcs/ft_get_cmd_heredoc_count.c \
	srcs/ft_get_heredocs.c \
	srcs/ft_heredocs_redirection.c \
	srcs/ft_check_file.c \
	srcs/ft_argv.c \
	srcs/ft_get_argv.c \
	srcs/ft_lexer.c \
	srcs/ft_get_shenv.c \
	termcaps/termcaps.c \
	termcaps/ft_paste_line.c \
	termcaps/line.c \
	termcaps/line_2.c \
	termcaps/history.c \
	termcaps/set_mode.c \
	termcaps/cursor.c \
	termcaps/string.c \
	termcaps/ft_set_term.c \
	termcaps/ft_set_state.c \
	parser/ast/ast.c \
	parser/ast/ft_dup_parser.c \
	parser/ast/ft_eval_parser.c \
	parser/ast/ft_free_parser.c \
	parser/ast/ft_get_grammar.c \
	parser/ast/ft_optimizer.c \
	parser/ast/ft_sanitizer.c \
	parser/ast/ft_put_parser.c \
	parser/ast/ft_eval_tokens/ft_eval_tokens.c \
	parser/ast/ft_eval_tokens/ft_eval_tokens_chars.c \
	parser/ast/ft_eval_tokens/ft_eval_tokens_logicals.c \
	parser/ast/ft_eval_tokens/ft_eval_tokens_misc.c \
	parser/ast/ft_eval_tokens/ft_eval_tokens_strings.c \
	completion/ft_completion.c \
	completion/ft_put_completions.c \
	completion/ft_complete_command.c \
	completion/ft_complete_argv.c \
	completion/ft_termcaps_completion.c \
	completion/ft_sanitize_completion.c \
	completion/ft_create_ltree.c \
	completion/ft_ltree_get_suffixes.c \
	completion/ft_free_ltree.c \
	completion/ft_ltree_get_directory.c
OBJ= $(SRC:.c=.o)
HDR_PATH= ./includes

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $^ -L./libft -lft -ltermcap  $(FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $< -I$(HDR_PATH) $(FLAGS) -o $@ -c

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all
