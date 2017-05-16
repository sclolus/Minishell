/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 22:45:44 by aalves            #+#    #+#             */
/*   Updated: 2017/05/05 23:04:11 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_free_tokens(t_tokens *tokens)
{
	uint32_t	i;

	i = 0;
	while (tokens->tokens[i])
		free(tokens->tokens[i++]);
	free(tokens->tokens);
	free(tokens->lens);
	free(tokens);
}
