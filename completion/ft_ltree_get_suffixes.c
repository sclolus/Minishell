/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltree_get_suffixes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 05:13:51 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/13 06:08:09 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_completion.h"

char		**ft_get_ltree_suffixes(t_ltree *root, char *prefix)
{
	char		**strings;
	t_ltree		*node;
	uint32_t	size;
	uint32_t	i;

	i = 0;
	if (!*prefix)
		return (ft_get_ltree_all_suffixes(root));
	if (!prefix || !(node = ft_ltree_last_match(root, prefix)))
		return (NULL);
	size = ft_ltree_count_suffixes(node->son);
	if (!(strings = (char**)malloc(sizeof(char*) * (size + 1))))
		exit(EXIT_FAILURE);
	strings[size] = NULL;
	while (i < size)
	{
		strings[i] = ft_ltree_get_match(node, prefix, i);
		i++;
	}
	return (strings);
}

uint32_t	ft_ltree_get_suffix_len(t_ltree *node, uint32_t index)
{
	uint32_t	ret;
	uint32_t	len;

	if (!node)
		return (0);
	len = 0;
	while (node->c != '\0' || index)
	{
		len++;
		ret = ft_ltree_count_suffixes(node->son);
		if (node->c == '\0' && index)
		{
			index--;
			len--;
			node = node->alternative;
			continue ;
		}
		if (ret <= index)
		{
			index -= ret;
			node = node->alternative;
			len--;
		}
		else
			node = node->son;
	}
	return (len);
}

char		*ft_ltree_get_match(t_ltree *root, char *prefix, uint32_t index)
{
	char		*string;
	uint32_t	i;
	uint32_t	prefix_len;
	uint32_t	len;
	uint32_t	ret;

	prefix_len = ft_strlen(prefix);
	len = ft_ltree_get_suffix_len(root->son, index) + prefix_len;
	if (!(string = ft_strnew(len)))
		exit(EXIT_FAILURE);
	ft_memcpy(string, prefix, prefix_len);
	i = prefix_len;
	root = root->son;
	while (i < len)
	{
		ret = ft_ltree_count_suffixes(root->son);
		if (root->c == '\0' && index)
		{
			root = root->alternative;
			index--;
			continue ;
		}
		if (ret <= index)
		{
			index -= ret;
			root = root->alternative;
		}
		else
		{
			string[i] = root->c;
			i++;
			root = root->son;
		}
	}
	return (string);
}

char		*ft_ltree_get_match_no_prefix(t_ltree *root, uint32_t index)
{
	char		*string;
	uint32_t	i;
	uint32_t	len;
	uint32_t	ret;

	len = ft_ltree_get_suffix_len(root, index);
	if (!(string = ft_strnew(len)))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		ret = ft_ltree_count_suffixes(root->son);
		if (root->c == '\0' && index)
		{
			root = root->alternative;
			index--;
			continue ;
		}
		if (ret <= index)
		{
			index -= ret;
			root = root->alternative;
		}
		else
		{
			string[i] = root->c;
			i++;
			root = root->son;
		}
	}
	return (string);
}

char		**ft_get_ltree_all_suffixes(t_ltree *root)
{
	char		**strings;
	t_ltree		*node;
	uint32_t	size;
	uint32_t	i;

	i = 0;
	node = root;
	size = ft_ltree_count_suffixes(node);
	if (!(strings = (char**)malloc(sizeof(char*) * (size + 1))))
		exit(EXIT_FAILURE);
	strings[size] = NULL;
	while (i < size)
	{
		strings[i] = ft_ltree_get_match_no_prefix(root, i);
		i++;
	}
	return (strings);
}
