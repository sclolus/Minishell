/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 22:45:44 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/05 22:46:06 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

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
