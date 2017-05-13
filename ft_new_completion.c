/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_completion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 20:34:22 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/14 00:23:28 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_sanitize_completion_path(char *path)
{
	uint32_t	len;
	char		*tmp;

	if (!path)
		return (NULL);
	len = ft_strlen(path);
	if (!len)
		return (path);
	if (path[len - 1] != '/')
	{
		if (!(tmp = ft_strjoin(path, "/")))
			exit(EXIT_FAILURE);
		return (tmp);
	}
	else
	{
		if (!(tmp = ft_strdup(path)))
			exit(EXIT_FAILURE);
		return (tmp);
	}
}

char	**ft_lsttotab_completion(t_list *lst)
{
	uint32_t	len;
	uint32_t	i;
	char		**tab;

	if (!lst)
		return (NULL);
	len = ft_lstlen(lst);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		tab[i] = lst->content;
		i++;
		lst = lst->next;
	}
	return (tab);
}

char		*ft_get_path_name(char *file)
{
	static char	buf[MAX_PATH_NAME];
	uint32_t	i;
	int64_t		offset;

	if (!file && (buf[0] = 0))
		return (NULL);
	i = 0;
	offset = -1;
	while (file[i])
	{
		if (file[i] == '/')
			offset = i;
		i++;
	}
	if (offset > MAX_PATH_NAME - 1)
	{
//		ft_error(1, (char*[]){"Pathname too long"}, 2);
		return (NULL);
	}
	if (offset >= 0)
	{
		ft_memcpy(buf, file, offset + 1);
		buf[offset + 1] = '\0';
	}
	return (buf);
}


t_list		*ft_completion_add_directory(char *path)
{
	DIR				*curr_dir;
	struct dirent	*curr_entry;
	char			*tmp;
	char			*tmp_curr_name;
	t_list			*lst;
	t_list			*list_dir;

	list_dir = NULL;
	path = ft_get_path_name(path);
	if (!(curr_dir = opendir(!*path ? "." : path)))
		//		ft_error_exit(1, (char*[]){"Failed to open completion directory"}, 4);
		return (NULL);
	while ((curr_entry = readdir(curr_dir)))
	{
		if (!(tmp = ft_strjoin(path, curr_entry->d_name)))
			exit(EXIT_FAILURE);
		if (ft_is_dir(tmp))
			(tmp_curr_name = ft_strjoin(curr_entry->d_name, "/"))
			? 0 : exit(EXIT_FAILURE);
		else
			(tmp_curr_name = ft_strdup(curr_entry->d_name))
			? 0 : exit(EXIT_FAILURE);
		if (!(tmp_curr_name = ft_strjoin_f(path, tmp_curr_name, 1)))
			exit(EXIT_FAILURE);
		if (!(lst = ft_lstnew(0, 0)))
			exit(EXIT_FAILURE);
		lst->content = tmp_curr_name;
		ft_lstadd(&list_dir, lst);
		free(tmp);
	}
	if (closedir(curr_dir) == -1)
//		ft_error_exit(1, (char*[]){"Failed to close completion directory"}, 4);
		exit(1);
	return (list_dir);
}

char		*ft_get_file_name(char *file)
{
	static char	buf[MAX_FILE_NAME];
	uint32_t	i;
	uint32_t	len;
	int64_t		offset;

	if (!file)
		return (NULL);
	i = 0;
	offset = -1;
	len = ft_strlen(file);
	while (file[i])
	{
		if (file[i] == '/')
			offset = i;
		i++;
	}
	if (len - offset > MAX_FILE_NAME)
	{
		ft_putstr_fd("Filename too long\n", 2);
		return (NULL);
	}
	ft_memcpy(buf, file + offset + 1, len - offset);
	buf[len - offset] = 0;
	return (buf);
}


char	**ft_get_completions(char **tab, char *to_complete)
{
	char		*pathname;
	char		*filename;
	uint32_t	i;
	uint32_t	count;
	uint32_t	offset;

	i = 0;
	count = 0;
	offset = 0;
	if (!(filename = ft_get_file_name(to_complete)))
		return (NULL);
	pathname = ft_get_path_name(to_complete);
	if (pathname)
		offset = ft_strlen(pathname);
	while (tab[i])
	{
		if (ft_strstr(tab[i] + offset, filename) == tab[i] + offset)
		{
			if (!(tab[count] = ft_strdup(tab[i] + offset)))
				exit(EXIT_FAILURE);
			if (tab[count] != tab[i])
				free(tab[i]);
			count++;
		}
		i++;
	}
	tab[count] = NULL;
	return (tab);
}

uint32_t	ft_get_max_common_len(char *s1, char *s2)
{
	uint32_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (i);
}

char	*ft_get_max_completion(char **tab, char *to_complete)
{
	char		*max_completion;
	uint32_t	len;
	uint32_t	max_offset;
	uint32_t	tmp;
	uint32_t	i;

	max_offset = ~0;
	i = 0;
	while (tab[i])
	{
		tmp = ft_get_max_common_len(tab[0], tab[i]);
		if (tmp < max_offset)
			max_offset = tmp;
		i++;
	}
	if (max_offset == ~0 || !max_offset || !tab[0])
		return (NULL);
	len = ft_strlen(ft_get_file_name(to_complete));
	max_offset -= len;
	if (!(max_completion = ft_strndup(tab[0] + len
							, max_offset)))
		exit(EXIT_FAILURE);
	return (max_completion);
}

/* int32_t		ft_ltree_add_directory_bin(t_ltree **ltree, char *path) */
/* { */
/* 	DIR				*curr_dir; */
/* 	struct dirent	*curr_entry; */
/* 	char			*tmp; */

/* 	if (!(curr_dir = opendir(path))) */
/* 		return (0); */
/* 	while ((curr_entry = readdir(curr_dir))) */
/* 	{ */
/* 		if (!(tmp = ft_strjoin(path, curr_entry->d_name))) */
/* 			exit(EXIT_FAILURE); */
/* 		if (ft_check_exec_perm(tmp) && ft_strcmp("..", curr_entry->d_name) */
/* 									&& ft_strcmp(".", curr_entry->d_name)) */
/* 			ft_fuk_norminette(tmp, ltree, curr_entry); */
/* 		free(tmp); */
/* 	} */
/* 	if (closedir(curr_dir) == -1) */
/* 		return (0); */
/* 	return (1); */
/* } */

/* char	**ft_get_completions_bin(char **tab, char *to_complete, char **path) */
/* { */
/* 	char		*pathname; */
/* 	char		*filename; */
/* 	uint32_t	i; */
/* 	uint32_t	count; */
/* 	uint32_t	offset; */

/* 	i = 0; */
/* 	count = 0; */
/* 	offset = 0; */
/* 	if (!(filename = ft_get_file_name(to_complete))) */
/* 		return (NULL); */
/* 	pathname = ft_get_path_name(to_complete); */
/* 	if (pathname) */
/* 		offset = ft_strlen(pathname); */
/* 	while (tab[i]) */
/* 	{ */
/* 		if (ft_strstr(tab[i] + offset, filename) == tab[i] + offset) */
/* 		{ */
/* 			if (!(tab[count] = ft_strdup(tab[i] + offset))) */
/* 				exit(EXIT_FAILURE); */
/* 			if (tab[count] != tab[i]) */
/* 				free(tab[i]); */
/* 			count++; */
/* 		} */
/* 		i++; */
/* 	} */
/* 	tab[count] = NULL; */
/* 	return (tab); */
/* } */

static void	ft_free_completions_lst(t_list *lst)
{
	while (lst)
	{
		free(lst->content);
		lst = lst->next;
	}
}

char		**ft_get_completions_tab(char *command_prefix)
{
	char	**tab;
	t_list	*lst;

	if (!(lst = ft_completion_add_directory(command_prefix)))
		return (NULL);
	tab = ft_lsttotab_completion(lst);
	ft_free_completions_lst(lst);
	tab = ft_get_completions(tab, command_prefix);
//	max = ft_get_max_completion(tab, command_prefix);
	return (tab);
}
