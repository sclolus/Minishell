/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_removal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:39:20 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/25 04:40:57 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CHARSET_QUOTES "'\"\\"
#define	QUOTE_REMOVAL_BUFF_SIZE 256
// ''''
static uint32_t		ft_sanitize_quotes(char *word, uint32_t *indexes
									, uint32_t offset, uint32_t i)
{
	uint32_t	u;

	u = 0;
//	'as'dd'dd'little girls''
	while (u + 1 < offset)
	{
/* 		ft_putstr("u: ");ft_putnbr(u);ft_putendl(""); */
/* 		ft_putstr("start: ");ft_putnbr(indexes[u]);ft_putendl(""); */
/* 		ft_putstr("end: ");ft_putnbr(indexes[u + 1]);ft_putendl(""); */
/* 		ft_putstr("len: ");ft_putnbr(indexes[u + 1] - indexes[u]);ft_putendl(""); */
/* 		ft_putendl("__________"); */
		ft_memcpy(word + indexes[u] - u
				, word + indexes[u] + 1, indexes[u + 1] - indexes[u]);
//		word[indexes[u + 1]] = '\0';
		ft_putstr("word:");ft_putendl(word);ft_putendl("");
		u++;
	}
/* 	ft_putstr("u: ");ft_putnbr(u);ft_putendl(""); */
/* 	ft_putstr("start: ");ft_putnbr(indexes[u]);ft_putendl(""); */
/* 	ft_putstr("end: ");ft_putnbr(indexes[u + 1]);ft_putendl(""); */
/* 	ft_putstr("len: ");ft_putnbr(ft_strlen(word + indexes[u]));ft_putendl(""); */
//		ft_putendl("__________");
	ft_memcpy(word + indexes[u] - u
			  , word + indexes[u] + 1, u);
	word[indexes[u] - u] = '\0';
//	ft_putstr("word:");ft_putendl(word);ft_putendl("");
	return (i - offset);
}

void				ft_quote_removal(char **word)
{
	static uint32_t		indexes[QUOTE_REMOVAL_BUFF_SIZE];
	uint32_t			offset;
	uint32_t			i;
	uint32_t			last_unquoted_point;
	uint32_t			is_quoted;

	i = 0;
	last_unquoted_point = 0;
	offset = 0;
	ft_putnbr(ft_is_quoted(*word, 3));
	while (word[0][i])
	{
		/*if (!(*/is_quoted = ft_is_quoted(*word + last_unquoted_point
										   , i - last_unquoted_point);/*))*/
//			last_unquoted_point = i;
		CHECK(TEST);
		ft_putstr("this is the state of the current token: ");
		ft_putchar(word[0][i]);
		ft_putstr(": ");
		ft_putnbr(is_quoted);
		ft_putendl("");
		
		if (ft_strchr(CHARSET_QUOTES, word[0][i]) && !is_quoted)
		{
			ft_putstr("there is a fucking quote in: ");
			ft_putnbr(i);
			ft_putendl("");
			indexes[offset++] = i;
		}
		if (offset == QUOTE_REMOVAL_BUFF_SIZE)
		{
			i = ft_sanitize_quotes(*word, indexes, offset, i);
			offset = 0;
		}
		i++;
		CHECK(END);
	}
	ft_sanitize_quotes(*word, indexes, offset, i);
}
