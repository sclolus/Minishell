/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ltree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 05:16:28 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/13 06:12:30 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_completion.h"

t_ltree		*ft_get_ltree_node(char c)
{
	t_ltree	*new;

	if (!(new = (t_ltree*)malloc(sizeof(t_ltree))))
		exit(EXIT_FAILURE);
	new->c = c;
	new->son = NULL;
	new->alternative = NULL;
	return (new);
}

t_ltree		*ft_get_alternative_node(t_ltree *root, char c)
{
	t_ltree	*alternative;

	if (root->c == c)
		return (root);
	if (!root->alternative)
	{
		alternative = ft_get_ltree_node(c);
		root->alternative = alternative;
		return (alternative);
	}
	else
		return (ft_get_alternative_node(root->alternative, c));
}

void		ft_ltree_add_word(t_ltree **root, char *word)
{
	if (!*root)
	{
		*root = ft_get_ltree_node(*word);
		if (!*word)
			return ;
		ft_ltree_add_word(&(*root)->son, word + 1);
		return ;
	}
	else if ((*root)->c == *word)
	{
		if (*word == '\0')
			return ;
		ft_ltree_add_word(&(*root)->son, word + 1);
	}
	else
	{
		if (!*word)
		{
			ft_get_alternative_node(*root, *word);
			return ;
		}
		ft_ltree_add_word(&ft_get_alternative_node(*root
												, *word)->son, word + 1);
	}
	return ;
}

uint32_t	ft_ltree_count_suffixes(t_ltree *root)
{
	uint32_t	ret;

	ret = 0;
	if (!root)
		return (0);
	if (root->c == '\0')
		ret++;
	if (root->son)
		ret += ft_ltree_count_suffixes(root->son);
	if (root->alternative)
		ret += ft_ltree_count_suffixes(root->alternative);
	return (ret);
}

char		*ft_ltree_get_completion(t_ltree *root, char *prefix)
{
	t_ltree		*node;
	char		*string;
	uint32_t	len;
	uint32_t	i;

	if (!root || !prefix || !(root = ft_ltree_last_match(root, prefix)))
		return (NULL);
	node = root->son;
	i = 0;
	while (node->c != '\0' && node->son && !node->alternative)
	{
		i++;
		node = node->son;
	}
	len = i;
	if (!(string = ft_strnew(len)))
		exit(EXIT_FAILURE);
	i = 0;
	node = root->son;
	while (i < len)
	{
		string[i++] = node->c;
		node = node->son;
	}
	return (string);
}
