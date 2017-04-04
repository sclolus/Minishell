# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalves <aalves@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/08 03:04:06 by aalves            #+#    #+#              #
#    Updated: 2017/03/31 02:49:13 by aalves           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

export NAME = libft.a
export CC = gcc
export FLAGS = -Werror -Wall -Wextra -g -O0 -fsanitize=address -fsanitize-blacklist=my_ignores.txt
export VERBOSE = 0

SRCS =

OBJS = $(SRCS:.c=.o)

MODULES =	./libft \
			./list/ \
			./ast \

export RM = rm -f
export ECHO = echo

#	COLORS

export BLACK = \033[0;30m
export RED = \033[0;31m
export GREEN = \033[0;32m
export BROWN = \033[0;33m
export BLUE = \033[0;34m
export PURPLE = \033[0;35m
export CYAN = \033[0;36m
export GRAY = \033[0;37m
export NC = \033[0m

ifneq (,$(findstring s,$(MAKEFLAGS)))
	VERBOSE = 0
endif

ifeq ($(VERBOSE), 1)
.c.o:
	@$(ECHO) "$(GREEN)Creating $@ $(NC)"
	@$(CC) $(FLAGS) -I./includes -o $@ -c $<

else
.c.o:
	@$(CC) $(FLAGS) -I./includes -o $@ -c $<
endif

all: $(NAME)

modules:
	@$(foreach module, $(MODULES), make -C $(module);)

$(NAME): $(OBJS) modules
	@ranlib $@

test: all
	gcc $(FLAGS) -I./includes -o test test.c -L. -lft
clean:
	@$(ECHO) "$(CYAN)Cleaning objects $(NC)"
	@$(foreach mod, $(MODULES), make -C $(mod) clean;)

fclean: clean
	@$(RM) $(NAME)
	@$(ECHO) "$(BLUE)Cleaned archive $(NC)"

re: fclean all
