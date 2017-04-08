/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 03:06:29 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/08 03:18:58 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_completion.h"

t_ltree	*ft_get_ltree_node(char c)
{
	t_ltree	*new;

	if (!(new = (t_ltree*)malloc(sizeof(t_ltree))))
		exit(EXIT_FAILURE);
	new->c = c;
	new->son = NULL;
	new->alternative = NULL;
	return (new);
}

t_ltree	*ft_get_alternative_node(t_ltree *root, char c)
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

void	ft_ltree_add_word(t_ltree **root, char *word)
{
	t_ltree	*new_node;

	if (!*root)
	{
		*root = ft_get_ltree_node(*word);
		if (!*word)
			return ;
		ft_ltree_add_word(&(*root)->son, word + 1);
		return ;
	}
	else if ((*root)->c == *word)
		ft_ltree_add_word(&(*root)->son, word + 1);
	else
	{
		if (!*word)
		{
			ft_get_alternative_node(*root, *word);
			return ;
		}
		ft_ltree_add_word(&ft_get_alternative_node(*root, *word)->son, word + 1);
	}
	return ;
}

int32_t	ft_ltree_search(t_ltree *root, char *word)
{
	if (!root)
		return (0);
	if (root->c == *word)
	{
		ft_putchar(root->c);
		if (!*word && root->c == *word)
			return (1);
		return (ft_ltree_search(root->son, word + 1));
	}
	else if (root->alternative)
		return (ft_ltree_search(root->alternative, word));
	return (0);
}

t_ltree	*ft_get_ltree_dictionary_list(t_list *list)
{
	t_ltree	*ltree;

	ltree = NULL;
	while (list)
	{
		ft_ltree_add_word(&ltree, list->content);
		list = list->next;
	}
	return (ltree);
}

t_ltree	*ft_get_ltree_dictionary(uint32_t size, char **strings)
{
	uint32_t	i;
	t_ltree	*ltree;

	ltree = NULL;
	i = 0;
	while (i < size)
	{
		ft_ltree_add_word(&ltree, strings[i]);
		i++;
	}
	return (ltree);
}

void	ft_free_ltree(t_ltree *root)
{
	if (!root)
		return ;
	if (root->son)
		ft_free_ltree(root->son);
	if (root->alternative)
		ft_free_ltree(root->alternative);
	free(root);
}
