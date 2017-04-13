/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 03:06:29 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/13 03:41:50 by sclolus          ###   ########.fr       */
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
	t_ltree		*ltree;
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

static t_ltree	*ft_get_matching_alternative(t_ltree *node
											, t_ltree **root, char c)
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

t_ltree		*ft_ltree_last_match(t_ltree *root, char *word)
{
	t_ltree		*last_match;
	t_ltree		*node;
	uint32_t	i;

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

void		ft_ltree_put(t_ltree *root)
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

char		**ft_get_ltree_all_suffixes(t_ltree *root)
{
	char		**strings;
	t_ltree		*node;
	uint32_t	size;
	uint32_t	i;

	i = 0;
	node = root;
	ft_ltree_put(root);
	size = ft_ltree_count_suffixes(node);
	if (!(strings = (char**)malloc(sizeof(char*) * (size + 1))))
		exit(EXIT_FAILURE);
	strings[size] = NULL;
	while (i < size)
	{
		strings[i] = ft_ltree_get_match_no_prefix(root, i);
		ft_putendl(strings[i]);
		i++;
	}
	return (strings);
}

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

t_ltree		*ft_get_ltree_directory(char *path)
{
	t_ltree			*ltree;
	DIR				*curr_dir;
	struct dirent	*curr_entry;

	ltree = NULL;
	if (!(curr_dir = opendir(path)))
	{
		//error plz;
		ft_putstr_fd("Opendir failed", 2);
		exit(EXIT_FAILURE);
	}
	while ((curr_entry = readdir(curr_dir)))
		ft_ltree_add_word(&ltree, curr_entry->d_name);
	if (closedir(curr_dir) == -1)
	{
		ft_putstr_fd("closedir failed", 2);
		exit(EXIT_FAILURE);
	}
	return (ltree);
}

int32_t		ft_ltree_add_directory(t_ltree **ltree, char *path)
{
	DIR				*curr_dir;
	struct dirent	*curr_entry;
	char			*tmp;
	char			*tmp_curr_name;

	if (!(curr_dir = opendir(path)))
		return (0);
	while ((curr_entry = readdir(curr_dir)))
	{
		if (!(tmp = ft_strjoin(path, curr_entry->d_name)))
			exit(EXIT_FAILURE);
		if (ft_is_dir(tmp))
		{
			if (!(tmp_curr_name = ft_strjoin(curr_entry->d_name, "/")))
				exit(EXIT_FAILURE);
		}
		else
		{
			if (!(tmp_curr_name = ft_strdup(curr_entry->d_name)))
				exit(EXIT_FAILURE);
		}
		ft_sanitize_completion(&tmp_curr_name);
		ft_ltree_add_word(ltree, tmp_curr_name);
		free(tmp_curr_name);
		free(tmp);
	}
	if (closedir(curr_dir) == -1)
		return (0);
	return (1);
}

int32_t		ft_ltree_add_directory_bin(t_ltree **ltree, char *path)
{
	DIR				*curr_dir;
	struct dirent	*curr_entry;
	char			*tmp;
	char			*tmp_curr_name;

	if (!(curr_dir = opendir(path)))
		return (0);
	while ((curr_entry = readdir(curr_dir)))
	{
		if (!(tmp = ft_strjoin(path, curr_entry->d_name)))
			exit(EXIT_FAILURE);
		if (ft_check_exec_perm(tmp))
		{
			if (ft_is_dir(tmp))
			{
				if (!(tmp_curr_name = ft_strjoin(curr_entry->d_name, "/")))
					exit(EXIT_FAILURE);
				ft_sanitize_completion(&tmp_curr_name);
				ft_ltree_add_word(ltree, tmp_curr_name);
			}
			else
			{
				if (!(tmp_curr_name = ft_strdup(curr_entry->d_name)))
					exit(EXIT_FAILURE);
				ft_sanitize_completion(&tmp_curr_name);
				ft_ltree_add_word(ltree, tmp_curr_name);
			}
			free(tmp_curr_name);
		}
		free(tmp);
	}
	if (closedir(curr_dir) == -1)
		return (0);
	return (1);
}

char		**ft_get_matching_filenames(char *prefix)
{
	char	**strings;
	t_ltree	*ltree;

	ltree = ft_get_ltree_directory(".");
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
