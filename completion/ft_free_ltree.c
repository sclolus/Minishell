/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ltree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 06:00:33 by jaustry           #+#    #+#             */
/*   Updated: 2017/04/13 06:01:03 by jaustry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_completion.h"

uint32_t		ft_free_ltree(t_ltree *root)
{
	if (!root)
		return (2);
	if (root->son)
		ft_free_ltree(root->son);
	if (root->alternative)
		ft_free_ltree(root->alternative);
	free(root);
	return (1);
}
