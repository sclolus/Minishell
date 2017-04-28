/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_heredocs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:55:24 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/29 01:54:47 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_get_the_norme(int fd, char *heredoc_input, uint32_t offset)
{
	write(fd, heredoc_input, offset);
	if (close(fd) == -1)
		ft_error_exit(1, (char*[]){"Failed to close Here-Document file"}
					, EXIT_HEREDOC_FILE);
	free(heredoc_input);
}

void		ft_get_heredoc(t_heredoc *heredoc, uint32_t index, t_shenv *shenv)
{
	char		*heredoc_input;
	char		*tmp;
	int			fd;
	uint32_t	offset;

	fd = ft_get_heredoc_index(index, shenv);
	ft_termget(&heredoc_input, shenv);
	if (!(heredoc_input = ft_strdup(heredoc_input)))
		exit(EXIT_FAILURE);
	offset = 0;
	while (ft_strcmp(heredoc_input + offset, heredoc->delimiter))
	{
		heredoc_input = ft_strjoin_f(heredoc_input, "\n", 0);
		offset += ft_strlen(heredoc_input + offset);
		ft_termget(&tmp, shenv);
		if (!(ft_strcmp(tmp, heredoc->delimiter)))
		{
			offset += ft_strlen(heredoc_input + offset);
			break ;
		}
		heredoc_input = ft_strjoin_f(heredoc_input, tmp, 0);
	}
	ft_get_the_norme(fd, heredoc_input, offset);
}

void		ft_get_heredocs(t_shenv *shenv)
{
	t_list		*tmp;
	uint32_t	i;

	i = 0;
	tmp = shenv->heredocs;
	while (tmp)
	{
		ft_get_heredoc(tmp->content, i++, shenv);
		tmp = tmp->next;
	}
}
