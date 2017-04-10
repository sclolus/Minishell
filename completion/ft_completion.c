/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 03:06:29 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/10 07:06:35 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_ltree_add_word(&ft_get_alternative_node(*root, *word)->son, word + 1);
	}
	return ;
}

int32_t		ft_ltree_search(t_ltree *root, char *word)
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

t_ltree		*ft_get_ltree_dictionary_list(t_list *list)
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

t_ltree		*ft_get_ltree_dictionary(uint32_t size, char **strings)
{
	t_ltree	*ltree;
	uint32_t	i;

	ltree = NULL;
	i = 0;
	while (i < size)
	{
		ft_ltree_add_word(&ltree, strings[i]);
		i++;
	}
	return (ltree);
}

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

t_ltree		*ft_ltree_last_match(t_ltree *root, char *word)
{
	t_ltree		*last_match;
	t_ltree		*node;
	uint32_t	i;

	i = 0;
	if (!root)
		return (NULL);
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
		while (node)
		{
			if (node->c == word[i])
			{
				root = node;
				break ;
			}
			node = node->alternative;
		}
		if (!node)
			break ;
	}
	if (!word[i])
		return (last_match);
	return (NULL);
}

void		ft_ltree_put(t_ltree *root)
{
	if (root->c == '\0')
		ft_putchar('%');
	else
		ft_putchar(root->c);
	if (root->son)
		ft_ltree_put(root->son);
    if (root->alternative)
		ft_ltree_put(root->alternative);
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

uint32_t	ft_ltree_get_suffix_len(t_ltree *root, uint32_t index)
{
	t_ltree		*node;
	uint32_t	ret;
	uint32_t	len;

	if (!(node = root))
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
		}
		else if (ret <= index)
		{
			index -= ret;
			if (!node->alternative)
				return (0);
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

char		**ft_get_ltree_suffixes(t_ltree *root, char *prefix)
{
	char		**strings;
	t_ltree		*node;
	uint32_t	size;
	uint32_t	i;
	uint32_t	len;

	i = 0;
	if (!(node = ft_ltree_last_match(root, prefix)))
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
	return(strings);
}

t_ltree		*ft_get_ltree_directory(void)
{
	t_ltree			*ltree;
	DIR				*curr_dir;
	struct dirent	*curr_entry;

	ltree = NULL;
	if (!(curr_dir = opendir("./")))
	{
		//error plz;
		ft_putstr_fd("Opendir failed", 2);
		exit (EXIT_FAILURE);
	}
	while ((curr_entry = readdir(curr_dir)))
		ft_ltree_add_word(&ltree, curr_entry->d_name);
	if (closedir(curr_dir) == -1)
	{
		ft_putstr_fd("closedir failed", 2);
		exit (EXIT_FAILURE);
	}
	return (ltree);
}

void		ft_ltree_add_directory(t_ltree *ltree, char *path)
{
	DIR				*curr_dir;
	struct dirent	*curr_entry;

	ltree = NULL;
	if (!(curr_dir = opendir(path)))
	{
		//error plz;
		ft_putstr_fd("Opendir failed", 2);
		exit (EXIT_FAILURE);
	}
	while ((curr_entry = readdir(curr_dir)))
		ft_ltree_add_word(&ltree, curr_entry->d_name);
	if (closedir(curr_dir) == -1)
	{
		ft_putstr_fd("closedir failed", 2);
		exit (EXIT_FAILURE);
	}
}

char		**ft_get_matching_filenames(char *prefix)
{
	char	**strings;
	t_ltree	*ltree;

	ltree = ft_get_ltree_directory();
	strings = ft_get_ltree_suffixes(ltree, prefix);
	ft_free_ltree(ltree);
	return (strings);
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
