/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termgets_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 15:23:54 by aalves            #+#    #+#             */
/*   Updated: 2017/05/13 12:27:32 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"
#include "minishell.h"

void		ft_append_line(char **line, char **final, uint32_t type)
{
	char		*tmp;
	char		*tmp_str;

	if (!*final)
		if (!(*final = ft_strdup(*line)))
			exit(EXIT_FAILURE);
	else
	{
		tmp = *final;
		if (type)
		{
			if (!(tmp_str = ft_strjoin(*line, "\n")))
				exit(EXIT_FAILURE);
			if (!(*final = ft_strjoin_f(*final, tmp_str, 1)))
				exit(EXIT_FAILURE);
		}
		else
		{
			if (!(*final = ft_strjoin(*final, *line)))
				exit(EXIT_FAILURE);
		}
		free(tmp);
	}
}
