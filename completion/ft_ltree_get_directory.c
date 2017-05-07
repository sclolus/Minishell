/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltree_get_directory.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 06:01:42 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/14 21:14:21 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_completion.h"
#include "minishell.h"

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

t_ltree		*ft_get_ltree_directory(char *path)
{
	t_ltree			*ltree;
	DIR				*curr_dir;
	struct dirent	*curr_entry;

	ltree = NULL;
	if (!(curr_dir = opendir(path)))
	{
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

	if (!(curr_dir = opendir(!*path ? "." : path)))
		return (0);
	while ((curr_entry = readdir(curr_dir)))
	{
		if (!(tmp = ft_strjoin(path, curr_entry->d_name)))
			exit(EXIT_FAILURE);
		if (ft_is_dir(tmp) &&
		!(tmp_curr_name = ft_strjoin(curr_entry->d_name, "/")))
			exit(EXIT_FAILURE);
		else if (!(tmp_curr_name = ft_strdup(curr_entry->d_name)))
			exit(EXIT_FAILURE);
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

	if (!(curr_dir = opendir(path)))
		return (0);
	while ((curr_entry = readdir(curr_dir)))
	{
		if (!(tmp = ft_strjoin(path, curr_entry->d_name)))
			exit(EXIT_FAILURE);
		if (ft_check_exec_perm(tmp) && ft_strcmp("..", curr_entry->d_name)
									&& ft_strcmp(".", curr_entry->d_name))
		    ft_fuk_norminette(tmp, ltree, curr_entry);
		free(tmp);
	}
	if (closedir(curr_dir) == -1)
		return (0);
	return (1);
}
