/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ltree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 06:00:33 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/13 06:01:03 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_completion.h"

void		ft_free_ltree(t_ltree *root)
{
	if (!root)
		return ;
	if (root->son)
		ft_free_ltree(root->son);
	if (root->alternative)
		ft_free_ltree(root->alternative);
	free(root);
}
