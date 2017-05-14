/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command_bin_completions_tab.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 01:30:31 by aalves            #+#    #+#             */
/*   Updated: 2017/05/14 05:42:09 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_put_lst(t_list *lst)
{
	ft_putendl("___LIST___");
	while (lst)
	{
		ft_putendl(lst->content);
		lst = lst->next;
	}
	ft_putendl("___END_LIST___");
}

char		**ft_get_command_bin_completions_tab(char *command_prefix,
														char **path)
{
	char		**tab;
	char		*tmp;
	t_list		*path_lst;
	t_list		*lst;
	uint32_t	i;

	i = 0;
	path_lst = NULL;
	while (path[i])
	{
		if (!(tmp = ft_strjoin(path[i], command_prefix)))
			exit(EXIT_FAILURE);
		if (!(lst = ft_completion_add_directory_bin(tmp)))
			return (NULL);
		ft_merge_lists(&path_lst, lst);
		free(tmp);
	}
	ft_put_lst(path_lst);
	tab = ft_lsttotab_completion(path_lst);
	tab = ft_get_completions(tab, command_prefix);
	ft_free_completions_lst(path_lst);
	return (tab);
}
