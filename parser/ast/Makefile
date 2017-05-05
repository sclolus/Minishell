# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalves <aalves@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/11 02:24:19 by aalves            #+#    #+#              #
#    Updated: 2017/05/05 18:05:22 by sclolus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= 		ast.c \
		ft_assign_parsers.c \
		ft_dup_parser/ft_dup_parser.c \
		ft_eval_parser.c \
		ft_eval_parser_chars.c \
		ft_eval_parser_logical.c \
		ft_eval_parser_misc.c \
		ft_eval_parser_multiply.c \
		ft_eval_parser_str_any_of.c \
		ft_eval_parser_strings.c \
		ft_eval_tokens/ft_eval_tokens.c \
		ft_eval_tokens/ft_eval_tokens_chars.c \
		ft_eval_tokens/ft_eval_tokens_logicals.c \
		ft_eval_tokens/ft_eval_tokens_misc.c \
		ft_eval_tokens/ft_eval_tokens_multiply.c \
		ft_eval_tokens/ft_eval_tokens_plus.c \
		ft_eval_tokens/ft_eval_tokens_strings.c \
		ft_free_parser/ft_free_parser.c \
		ft_free_parser/ft_free_parser_chars.c \
		ft_free_parser/ft_free_parser_logicals.c \
		ft_free_parser/ft_free_parser_misc.c \
		ft_free_parser/ft_free_parser_strings.c \
		ft_get_grammar.c \
		ft_get_grammar_linker.c \
		ft_get_grammar_syntax.c \
		ft_get_parser.c \
		ft_get_parser_chars.c \
		ft_get_parser_grammar.c \
		ft_get_parser_logicals.c \
		ft_get_parser_misc.c \
		ft_get_parser_strings.c \
		ft_get_parser_terminals.c \
		ft_optimizer.c \
		ft_sanitizer/ft_sanitizer.c \
		ft_sanitizer/ft_sanitizer_chars.c \
		ft_sanitizer/ft_sanitizer_logicals.c \
		ft_sanitizer/ft_sanitizer_misc.c \
		ft_sanitizer/ft_sanitizer_strings.c


OBJS= $(SRCS:.c=.o)

ifeq ($(VERBOSE), 1)
.c.o:
	@$(ECHO) "$(GREEN)Creating $@ $(NC)"
	@$(CC) $(FLAGS) -I ../../includes -o $@ -c $<
else
.c.o:
	@$(CC) $(FLAGS) -I ../../includes -o $@ -c $<
endif

all: $(OBJS)
	@$(ECHO) "$(CYAN)Parsing module done $(NC)"
	@ar r ../$(NAME) $^

clean:
	@$(RM) $(OBJS)
	@$(ECHO) "$(BLUE)Parsing module cleaned $(NC)"

re: clean all
