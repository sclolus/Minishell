/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredocs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 11:10:55 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/26 19:44:45 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_heredoc_file(char *delimiter
								, uint32_t index, t_shenv *shenv)
{
	char		*filename;
	t_heredoc	*new_heredoc;
	t_list		*lstnew;
	int			fd;

	if (!(filename = ft_strjoin_f("./tmp/", ft_itoa(index), 1)))
		exit(EXIT_FAILURE);
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC
				   , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		ft_error_exit(1, (char*[]){"Failed to create Here-Document File"}
					, EXIT_HEREDOC_FILE);
	close(fd);
	if (!(lstnew = ft_lstnew(0, 0)))
		exit(EXIT_FAILURE);
	if (!(new_heredoc = (t_heredoc*)ft_memalloc(sizeof(t_heredoc))))
		exit(EXIT_FAILURE);
	lstnew->content = new_heredoc;
	new_heredoc->filename = filename;
	new_heredoc->delimiter = delimiter;
	ft_lstadd(&shenv->heredocs, lstnew);
	return (filename);
}

int		ft_open_heredoc_file(char *filename)
{
	int			fd;

	if ((fd = open(filename, O_RDWR)) == -1)
		ft_error_exit(1, (char*[]){"Failed to open Here-Document File"}
					, EXIT_HEREDOC_FILE);
	if (fd == -1)
		ft_error_exit(1, (char*[]){"Bad file descriptor"}, -1);
	return (fd);
}

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

int		ft_get_heredoc_index(uint32_t index, t_shenv *shenv)
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

char	*ft_get_heredoc_delimiter_index(t_tokens *tokens, uint32_t index)
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

void		ft_create_heredocs(t_tokens *tokens, t_shenv *shenv)
{
	char		*delimiter;
	uint32_t	count;

	count = 0;
	while (42)
	{
		if (!(delimiter = ft_get_heredoc_delimiter_index(tokens, count)))
			break ;
		ft_create_heredoc_file(delimiter, count, shenv);
		count++;
	}
	shenv->heredocs_index = 0;
}

void		ft_put_heredocs(t_shenv *shenv)
{
	t_list		*tmp;
	uint32_t	i;

	tmp = shenv->heredocs;
	i = 0;
	while (tmp)
	{
		ft_putstr("Heredoc n: ");
		ft_putnbr(i);
		ft_putstr("\nDelimiter: ");
		ft_putendl(((t_heredoc*)tmp->content)->delimiter);
		tmp = tmp->next;
		i++;
	}
}

void		ft_put_heredocs_content(t_shenv *shenv)
{
	t_list		*tmp;
	uint32_t	i;
	int	fd;
	static char		buf[4096];
	uint32_t	ret;

	tmp = shenv->heredocs;
	i = 0;
	while (tmp)
	{
		ft_putstr("Heredoc n: ");
		ft_putnbr(i);
		ft_putstr("\n Filename: ");
		ft_putendl(((t_heredoc*)tmp->content)->filename);
		ft_putstr("\nDelimiter: ");
		ft_putendl(((t_heredoc*)tmp->content)->delimiter);
		if ((fd = ft_open_heredoc_file(((t_heredoc*)tmp->content)->filename)) == -1)
			exit(EXIT_FAILURE);
		while ((ret = read(fd, buf, 4095)))
		{
			buf[ret] = 0;
			ft_putstr(buf);
		}
		ft_putnbr(ret);
		tmp = tmp->next;
		i++;
	}
}

void		ft_clear_heredoc(t_list *heredoc)
{
	free(((t_heredoc*)heredoc->content)->filename);
	free(((t_heredoc*)heredoc->content)->delimiter);
	if (heredoc->next)
		heredoc->next->prev = NULL;
	free(heredoc->content);
	free(heredoc);
}

void		ft_clear_heredocs(t_shenv *shenv)
{
	while (shenv->heredocs)
		ft_delone_heredoc(shenv);
}

void		ft_delone_heredoc(t_shenv *shenv)
{
	t_list	*tmp;

	if (shenv->heredocs->next)
		tmp = shenv->heredocs->next;
	else
		tmp = NULL;
	ft_clear_heredoc(shenv->heredocs);
	shenv->heredocs = tmp;
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
		heredoc_input = ft_strjoin_f(heredoc_input, "\n", 0); // free bss
		offset += ft_strlen(heredoc_input + offset);
		ft_termget(&tmp, shenv);
		if (!(ft_strcmp(tmp, heredoc->delimiter)))
		{
			offset += ft_strlen(heredoc_input + offset);
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

int32_t	ft_heredoc_redirect(t_parser *heredoc)
{
	int32_t		fd_file;
	int32_t		redirect_fd;
	t_shenv		*shenv;
	t_heredoc	*heredocument;

	shenv = *ft_get_shenv();
	if (!(heredocument = ft_get_t_heredoc_index(shenv->heredocs_index, shenv)))
		return (EXIT_REDIREC_ERROR);
	if (OR_PARSER_N(heredoc, 0)->retained)
	{
		heredoc = OR_PARSER_N(heredoc, 0);
		redirect_fd = ft_atoi(AND_PARSER_N(heredoc, 0)->parser.str_any_of.str);
		if (redirect_fd < 0)
			ft_error_exit(1, (char*[]){"Invalid File descriptor"}, EXIT_REDIREC_ERROR);
		if ((fd_file = ft_open_heredoc_file(heredocument->filename)) == -1)
			ft_error_exit(1, (char*[]){"Failed to open heredoc"}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){"File descriptor duplication failed"}, EXIT_REDIREC_ERROR);
	}
	else
	{
		heredoc = OR_PARSER_N(heredoc, 1);
		redirect_fd = STDIN_FILENO;
		if ((fd_file = ft_open_heredoc_file(heredocument->filename)) == -1)
			ft_error_exit(1, (char*[]){"Failed to open heredoc"}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){"File descriptor duplication failed"}, EXIT_REDIREC_ERROR);
	}
	close(fd_file);
	return (redirect_fd);
}
