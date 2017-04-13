NAME= minishell
CC= gcc
FLAGS= -Wall -Werror -Wextra -g -fsanitize=address -fsanitize-blacklist=my_ignores.txt
SRC= srcs/minishell.c \
	srcs/ft_signal.c \
	srcs/ft_built-in_export.c \
	srcs/ft_find_command.c \
	srcs/ft_built-in_echo.c \
	srcs/ft_built-in.c \
	srcs/ft_built-in_exit.c \
	srcs/ft_env.c \
	srcs/ft_putenv.c \
	srcs/ft_lsttotab_token.c \
	srcs/ft_line_continuation.c \
	srcs/ft_is_quoted.c \
	srcs/ft_expansions.c \
	srcs/ft_built-in_history.c \
	srcs/ft_exec_parser.c \
	srcs/ft_error.c \
	srcs/ft_redirection.c \
	srcs/ft_check_file.c \
	termcaps/termcaps.c \
	termcaps/line.c \
	termcaps/history.c \
	termcaps/set_mode.c \
	termcaps/cursor.c \
	termcaps/string.c \
	termcaps/ft_set_term.c \
	parser/ast/ast.c \
	parser/ast/ft_dup_parser.c \
	parser/ast/ft_eval_parser.c \
	parser/ast/ft_free_parser.c \
	parser/ast/ft_get_grammar.c \
	parser/ast/ft_optimizer.c \
	parser/ast/ft_put_parser.c \
	completion/ft_completion.c \
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
	make -C libft/ re

