/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fuk_norminette.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 10:26:42 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/09 15:09:53 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_completion.h"
#include "minishell.h"

void			ft_fuk_norminette(char *tmp, t_ltree **ltree
								, struct dirent *curr_entry)
{
	char	*tmp_curr_name;

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

static uint32_t	*ft_get_lens_tab(char **strings, uint32_t n)
{
	uint32_t	*tab;
	uint32_t	i;

	if (!(tab = (uint32_t*)malloc(sizeof(uint32_t) * (n + 1))))
		exit(EXIT_FAILURE);
	tab[n] = 0;
	i = 0;
	while (i < n)
	{
		tab[i] = ft_strlen(strings[i]);
		if (tab[i] > tab[n])
			tab[n] = tab[i];
		i++;
	}
	tab[n]++;
	return (tab);
}

uint32_t		*ft_fuk_norminette2(char **completions, uint32_t n,
				t_string *buf, int64_t *old_offset)
{
	uint32_t				*lens;

	ft_sort_strings(completions, n);
	lens = ft_get_lens_tab(completions, n);
	*old_offset = buf->offset;
	ft_move_end_line(buf);
	ft_static_put("\n", 1, 0);
	return (lens);
}

int32_t			ft_set_canonical_mode(void)
{
	static struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag |= ICANON;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}

uint32_t		ft_fuk_norminette3(char **path, t_ltree **ltree)
{
	uint32_t	i;

	i = 0;
	while (path[i])
	{
		if (!(ft_ltree_add_directory(ltree, path[i++])))
		{
			ft_free_argv(path);
			ft_free_ltree(*ltree);
			return (0);
		}
	}
	return (1);
}
