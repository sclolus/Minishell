/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_completions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 13:42:20 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/28 14:01:13 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_completion.h"

static void		ft_termcaps_go_back_to_offset(t_string *buf, int64_t old_offset)
{
	char	*res;

	while (buf->offset > 0 && buf->offset > old_offset)
	{
		buf->offset--;
		res = tgetstr("le", NULL);
		tputs(res, 1, &ft_putterm);
	}
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

int32_t			ft_put_max_completion(t_ltree *ltree, t_string *buf,
										char *prefix, uint32_t n)
{
	char		*max_completion;

	if ((max_completion = ft_ltree_get_completion(ltree, prefix)))
	{
		if (*max_completion)
		{
			ft_t_string_insert(buf, max_completion);
			ft_termcaps_putstr(buf, max_completion);
			free(max_completion);
			return (1);
		}
		else
			ft_putchar(7);
		free(max_completion);
		if (n < 2)
			return (1);
	}
	else
	{
		ft_putchar(7);
		return (0);
	}
	return (-1);
}

static void		ft_completions_cleanup(t_string *buf, int64_t old_offset, uint32_t *lens)
{
	ft_static_put("\n", 1, 0);
	ft_static_put(PROMPT, 2, 0);
	ft_static_put(buf->string, buf->len, 0);
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
	ft_termcaps_go_back_to_offset(buf, old_offset);
	free(lens);
}

int32_t			ft_put_completions(t_string *buf, char **completions,
									uint32_t n, char *prefix)
{
	static struct winsize	window;
	static char				buffer[1024];
	uint32_t				*lens;
	uint32_t				i;
	uint32_t				offset;
	int64_t					old_offset;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	if (!window.ws_col)
		return (0);
	if (buffer[0] == 0)
		ft_memset(buffer, ' ', 1023);
	i = 0;
	ft_sort_strings(completions, n);
	lens = ft_get_lens_tab(completions, n);
	old_offset = buf->offset;
	ft_move_end_line(buf);
	ft_static_put("\n", 1, 0);
	offset = 0;
	while (i < n)
	{
		if (*completions[i] == '.' && *prefix != '.')
		{
			i++;
			continue ;
		}
		if ((offset + lens[n]) / window.ws_col)
		{
			ft_static_put("\n", 1, 0);
			offset = 0;
		}
		ft_static_put(completions[i], lens[i], 0);
		ft_static_put(buffer, lens[n] - lens[i], 0);
		offset += lens[n];
		i++;
	}
	ft_completions_cleanup(buf, old_offset, lens);
	return (n);
}
