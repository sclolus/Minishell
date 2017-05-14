/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_completions_tab.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 01:35:02 by aalves            #+#    #+#             */
/*   Updated: 2017/05/14 05:20:45 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_get_completions_tab(char *command_prefix) // ft_sanitize_completion
{
	char	**tab;
	t_list	*lst;

	if (!(lst = ft_completion_add_directory(command_prefix)))
		return (NULL);
	tab = ft_lsttotab_completion(lst);
	tab = ft_get_completions(tab, command_prefix);
	ft_free_completions_lst(lst);
	return (tab);
}
