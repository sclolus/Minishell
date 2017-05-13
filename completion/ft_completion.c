/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 03:06:29 by jaustry           #+#    #+#             */
/*   Updated: 2017/04/13 06:13:24 by jaustry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_completion.h"

int32_t				ft_ltree_search(t_ltree *root, char *word)
{
	if (!root)
		return (0);
	if (root->c == *word)
	{
		if (!*word && root->c == *word)
			return (1);
		return (ft_ltree_search(root->son, word + 1));
	}
	else if (root->alternative)
		return (ft_ltree_search(root->alternative, word));
	return (0);
}

static t_ltree		*ft_get_matching_alternative(t_ltree *node,
												t_ltree **root, char c)
{
	while (node)
	{
		if (node->c == c)
		{
			*root = node;
			break ;
		}
		node = node->alternative;
	}
	return (node);
}

t_ltree				*ft_ltree_last_match(t_ltree *root, char *word)
{
	t_ltree			*last_match;
	t_ltree			*node;
	uint32_t		i;

	i = 0;
	if (!root)
		return (NULL);
	last_match = root;
	while (word[i])
	{
		if (root->c == word[i])
		{
			last_match = root;
			root = root->son;
			i++;
			continue ;
		}
		node = root->alternative;
		node = ft_get_matching_alternative(node, &root, word[i]);
		if (!node)
			break ;
	}
	if (!word[i])
		return (last_match);
	return (NULL);
}

void				ft_ltree_put(t_ltree *root)
{
	if (root->c == '\0')
		ft_putchar('\n');
	else
		ft_putchar(root->c);
	if (root->son)
		ft_ltree_put(root->son);
	if (root->alternative)
	{
		ft_putchar('-');
		ft_ltree_put(root->alternative);
	}
}

char				**ft_get_matching_filenames(char *prefix)
{
	char			**strings;
	t_ltree			*ltree;

	ltree = ft_get_ltree_directory(".");
	strings = ft_get_ltree_suffixes(ltree, prefix);
	ft_free_ltree(ltree);
	return (strings);
}
