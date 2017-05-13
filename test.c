/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 20:39:21 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/13 23:05:36 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_lst(t_list *lst)
{
	while (lst)
	{
		ft_putendl(lst->content);
		lst = lst->next;
	}
}

void	ft_put_tab(char **tab)
{
	while (*tab)
		ft_putendl(*tab++);
}

t_list		*ft_completion_add_directory(char *path);
char		**ft_lsttotab_completion(t_list *lst);
char		**ft_get_completions(char **tab, char *to_complete);
char		*ft_get_max_completion(char **tab, char *to_complete);

int	main(int argc, char **argv)
{
	t_list	*lst;
	char	**tab;

	lst = ft_completion_add_directory(argv[1]);
	tab = ft_lsttotab_completion(lst);
	tab = ft_get_completions(tab, argv[1]);
	ft_put_tab(tab);
	char	*max;
	max = ft_get_max_completion(tab, argv[1]);
	ft_putchar('-');

	ft_putstr(max);
	uint32_t	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (0);
}
