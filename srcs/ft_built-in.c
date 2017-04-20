/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built-in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 07:46:43 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/20 23:08:30 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	ft_is_built_in(t_parser *parser)
{
	uint32_t			i;
	static const char	*f_built_in[] = {"cd",
										 "echo",
										 "exit",
										 "env",
										 "setenv",
										 "unsetenv",
										 "history",
										 "unset",
										 "export"};

	i = 0;
	while (i < sizeof(f_built_in) / sizeof(char *))
	{
		if (!ft_strcmp(AND_PARSER_N(parser, 2)->parser.str_any_of.str
					, f_built_in[i]))
			return (1);
		i++;
	}
	return (0);
}

int32_t	ft_built_in(char **argv, t_shenv *shenv)
{
	uint32_t	i;
	static const t_built_in	f_built_in[BUILT_IN_COUNT] = {
		{"cd", NULL},
		{"echo", &ft_built_in_echo},
		{"exit", &ft_built_in_exit},
		{"env", &ft_built_in_env},
		{"setenv", &ft_built_in_setenv},
		{"unsetenv", &ft_built_in_unsetenv},
		{"history", /*&ft_built_in_history*/ NULL}, //TODO
		{"unset", &ft_built_in_unset},
		{"export", &ft_built_in_export}};

	i = 0;
	while (i < BUILT_IN_COUNT)
	{
		if (!ft_strcmp(argv[0], f_built_in[i].id))
			return (f_built_in[i].f(argv, shenv));
		i++;
	}
	return (EXIT_ILLEGAL_CMD);
}
