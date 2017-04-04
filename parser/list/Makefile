# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalves <aalves@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 05:34:22 by aalves            #+#    #+#              #
#    Updated: 2017/03/28 01:42:53 by aalves           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =  init_list_head.c \
		ft_list_add.c \
		ft_list_add_between.c \
		ft_list_add_tail.c \
		ft_list_del.c \
		ft_list_empty.c \
		ft_list_iter.c \
		ft_list_iter_safe.c \
		ft_list_move.c \
		ft_list_move_tail.c \
		ft_list_splice_init.c

OBJS = $(SRCS:.c=.o)

ifeq ($(VERBOSE), 1)
.c.o:
	@$(ECHO) "$(GREEN)Creating $@ $(NC)"
	@$(CC) $(FLAGS) -I ../includes -o $@ -c $<
else
.c.o:
	@$(CC) $(FLAGS) -I ../includes -o $@ -c $<
endif

all: $(OBJS)
	@$(ECHO) "$(CYAN)List module done $(NC)"
	@ar r ../$(NAME) $^

clean:
	@$(RM) $(OBJS)
	@$(ECHO) "$(BLUE)List module cleaned $(NC)"

re: clean all
