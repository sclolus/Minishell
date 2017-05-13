/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command_directory_completions_tab.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 01:30:35 by aalves            #+#    #+#             */
/*   Updated: 2017/05/14 01:30:36 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_get_command_directory_completions_tab(char *command_prefix)
{
	char	**tab;
	t_list	*lst;

	if (!(lst = ft_completion_add_directory_bin(command_prefix)))
		return (NULL);
	tab = ft_lsttotab_completion(lst);
	ft_free_completions_lst(lst);
	tab = ft_get_completions(tab, command_prefix);
	return (tab);
}
