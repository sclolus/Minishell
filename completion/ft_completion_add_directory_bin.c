/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion_add_directory_bin.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaustry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 06:20:42 by jaustry           #+#    #+#             */
/*   Updated: 2017/05/14 06:39:26 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_list_insert(t_list **head, char *val)
{
	t_list			*lst;

	if (!(lst = ft_lstnew(0, 0)))
		exit(EXIT_FAILURE);
	lst->content = val;
	ft_lstadd(head, lst);
}

static void	ft_c_clean(char **tmp, char **tmp_curr_name,
				char *path, struct dirent *curr_entry)
{
	*tmp_curr_name = NULL;
	if (!(*tmp = ft_strjoin(path, curr_entry->d_name)))
		exit(EXIT_FAILURE);
	if (ft_check_exec_perm(*tmp) && ft_strcmp("..", curr_entry->d_name)
		&& ft_strcmp(".", curr_entry->d_name))
		ft_fuk_norminette(tmp_curr_name, curr_entry, *tmp);
}

t_list		*ft_completion_add_directory_bin(char *path)
{
	DIR				*curr_dir;
	struct dirent	*curr_entry;
	char			*tmp;
	char			*tmp_curr_name;
	t_list			*list_dir;

	list_dir = NULL;
	path = ft_get_path_name(path);
	if (!(curr_dir = opendir(path)))
		return (NULL);
	while ((curr_entry = readdir(curr_dir)))
	{
		ft_c_clean(&tmp, &tmp_curr_name, path, curr_entry);
		if (!(tmp_curr_name))
		{
			free(tmp);
			continue ;
		}
		ft_list_insert(&list_dir, tmp_curr_name);
		free(tmp);
	}
	if (closedir(curr_dir) == -1)
		ft_error_exit(1, (char*[]){"Failed to close completion directory"}, 4);
	return (list_dir);
}
