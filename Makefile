NAME= minishell
CC= gcc
FLAGS= -Wall -Werror -Wextra
SRC= minishell.c \
	ft_signal.c \
	ft_find_command.c \
	build-in_echo.c \
	build-in_cd.c \
	ft_build-in.c \
	ft_btree.c \
	ft_parser.c \
	ft_lexer.c \
	ft_execve.c \
	ft_env.c \
	ft_putenv.c \
	ft_lsttotab_token.c \
	ft_ast.c
OBJ= $(SRC:.c=.o)
HDR_PATH= ./libft/includes

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $^ -L./libft -lft  $(FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $< -I$(HDR_PATH) $(FLAGS) -c

clean:
	make -C libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

re: fclean all
	make -C libft/ re
