/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 11:10:55 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/22 17:37:16 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_heredoc_file(uint32_t index, t_shenv *shenv)
{
	char		*filename;
	t_list		*lstnew;
	int			fd;

	if (!(filename = ft_itoa(index)))
		exit(EXIT_FAILURE);
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC
				   , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		ft_error_exit(1, (char*[]){"Failed to create Here-Document File"}
					, EXIT_HEREDOC_FILE);
	close(fd);
	if (!(lstnew = ft_lstnew(0, 0)))
		exit(EXIT_FAILURE);
	lstnew->content = filename;
	ft_lstadd(&shenv->heredocs, lstnew);
	return (filename);
}

int		ft_open_heredoc_file(char *filename)
{
	int			fd;

	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC
				   , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		ft_error_exit(1, (char*[]){"Failed to create Here-Document File"}
					, EXIT_HEREDOC_FILE);
	return (fd);
}

int		ft_get_heredoc_index(uint32_t index, t_shenv *shenv)
{
	t_list		*tmp;
	uint32_t	len;

	if (shenv->heredocs)
		len = ft_lstlen(shenv->heredocs);
	else
		return (-1);
	tmp = shenv->heredocs;
	index = len - index;
	while (index && tmp)
	{
		index--;
		tmp = tmp->next;
	}
	if (tmp)
		return (ft_open_heredoc_file(tmp->content));
	return (-1);
}

uint32_t	ft_get_count_heredocs(char *input)
{
	uint32_t	i;
	uint32_t	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (*((short*)(input + i)) == 0x3C3C && !ft_is_quoted(input, i))
			count++;
		i++;
	}
	return (count);
}

void		ft_create_heredocs(char *input, t_shenv *shenv)
{
	uint32_t	i;
	uint32_t	count;

	count = ft_get_count_heredocs(input);
	i = 0;
	while (i < count)
		ft_create_heredoc_file(i++, shenv);
}

void		ft_put_heredocs(t_shenv *shenv)
{
	t_list	*tmp;

	tmp = shenv->heredocs;
	while (tmp)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
}

#if 0
void		ft_get_heredoc(t_parser *heredoc, uint32_t index, t_shenv *shenv)
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
	while (!ft_strcmp(heredoc_input + offset, ?))
	{
		offest += ft_strlen(heredoc_input + offset);
		ft_termget(&tmp, shenv);
		if (!(ft_strcmp(tmp, ?)))
		{
			offest += ft_strlen(heredoc_input + offset);
			break ;
		}
		heredoc_input = ft_strjoin_f(heredoc_input, tmp, 0); // free bss
	}
	write(fd, heredoc_input, offset);
	if (close(fd) == -1)
		ft_error_exit(1, (char*[]){"Failed to close Here-Document file"}
					, EXIT_HEREDOC_FILE);
	free(heredoc_input);
}

#endif
