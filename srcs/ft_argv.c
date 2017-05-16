/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 02:11:54 by aalves            #+#    #+#             */
/*   Updated: 2017/04/20 02:14:53 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ft_free_argv() assumes that argv is a NULL-terminated array of strings
*/

void	ft_free_argv(char **argv)
{
	uint32_t	i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}
