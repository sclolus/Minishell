/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 11:10:55 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/28 19:16:44 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*ft_get_t_heredoc_index(uint32_t index, t_shenv *shenv)
{
	t_list		*tmp;
	uint32_t	len;

	if (shenv->heredocs)
		len = ft_lstlen(shenv->heredocs);
	else
		return (NULL);
	tmp = shenv->heredocs;
	index = len - index - 1;
	while (index && tmp)
	{
		index--;
		tmp = tmp->next;
	}
	if (tmp)
		return (tmp->content);
	return (NULL);
}

int			ft_get_heredoc_index(uint32_t index, t_shenv *shenv)
{
	t_list		*tmp;
	uint32_t	len;

	if (shenv->heredocs)
		len = ft_lstlen(shenv->heredocs);
	else
		return (-1);
	tmp = shenv->heredocs;
	index = len - index - 1;
	while (index && tmp)
	{
		index--;
		tmp = tmp->next;
	}
	if (tmp)
		return (ft_open_heredoc_file(((t_heredoc*)tmp->content)->filename));
	return (-1);
}

char		*ft_get_heredoc_delimiter_index(t_tokens *tokens, uint32_t index)
{
	char		*delimiter;
	uint32_t	i;

	i = 0;
	while (tokens->tokens[i])
	{
		if (tokens->lens[i] == 2 && *((short*)(tokens->tokens[i])) == 0x3C3C)
		{
			if (!index)
			{
				if (!(delimiter = ft_strdup(tokens->tokens[i + 1])))
					exit(EXIT_FAILURE);
				return (delimiter);
			}
			index--;
		}
		i++;
	}
	return (NULL);
}
