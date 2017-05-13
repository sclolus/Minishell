/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 20:39:21 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/14 00:24:40 by sclolus          ###   ########.fr       */
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

int32_t			ft_put_completion(char **completions, t_string *buf, char *prefix)
{
	uint32_t	i;
	uint32_t	n;
	int32_t		ret;

	n = 0;
	i = 0;
	if (!completions)
	{
		ft_putchar(7);
		return (0);
	}
	while (completions[n])
		n++;
	if ((ret = ft_put_max_completion(ltree, buf, prefix, n)) > -1)
	{
		ft_free_argv(completions);
		return (ret);
	}
	if (n > 1)
		ft_put_completions(buf, completions, n, prefix);
	ft_free_argv(completions);
	return (1);
}

int32_t			ft_completion(t_string *buf, t_shenv *shenv)
{
	static const t_comp_event	events[] = {
		NULL,
		&ft_completion_normal_state,
		&ft_complete_command_name,
		&ft_complete_argv,
	};
	t_termcaps_state			*state;

	ft_set_term_state(buf);
	state = ft_get_term_state();
	return (events[*state](buf, shenv));
}

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
	return (0);
}
