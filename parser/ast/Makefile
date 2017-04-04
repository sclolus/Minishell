# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalves <aalves@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/11 02:24:19 by aalves            #+#    #+#              #
#    Updated: 2017/03/31 01:28:08 by aalves           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=		ast.c \
			ft_put_parser.c \
			ft_eval_parser.c \
			ft_dup_parser.c \
			ft_get_grammar.c \
			ft_optimizer.c \
			ft_free_parser.c \

OBJS= $(SRCS:.c=.o)

ifeq ($(VERBOSE), 1)
.c.o:
	@$(ECHO) "$(GREEN)Creating $@ $(NC)"
	@$(CC) $(FLAGS) -I ../includes -o $@ -c $<
else
.c.o:
	@$(CC) $(FLAGS) -I ../includes -o $@ -c $<
endif

all: $(OBJS)
	@$(ECHO) "$(CYAN)Parsing module done $(NC)"
	@ar r ../$(NAME) $^

clean:
	@$(RM) $(OBJS)
	@$(ECHO) "$(BLUE)Parsing module cleaned $(NC)"

re: clean all
