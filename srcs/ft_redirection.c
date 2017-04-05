/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 14:22:32 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/05 05:05:34 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	ft_output_redirect(t_parser *redirect)
{
	int32_t	fd_file;
	int32_t	redirect_fd;
	char	*filename;

	if (OR_PARSER_N(redirect, 0)->retained)
	{
			CHECK(OUTPUT_REDIRECT);
		redirect = OR_PARSER_N(redirect, 0);
		redirect_fd = ft_atoi(AND_PARSER_N(redirect, 0)->parser.str_any_of.str);
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(AND_PARSER_N(redirect, 1), 0), 1), 1)->parser.str_any_of.str;
		if (redirect_fd < 0)
			ft_error_exit(1, (char*[]){"Invalid File descriptor"}, EXIT_REDIREC_ERROR);
		if ((fd_file = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			ft_error_exit(2, (char*[]){"Failed to open or to create: ", filename}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){"File descriptor duplication failed"}, EXIT_REDIREC_ERROR);
	}
	else
	{
		redirect = OR_PARSER_N(redirect, 1);
		redirect_fd = STDOUT_FILENO;
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(redirect, 0), 1), 1)->parser.str_any_of.str;
		if ((fd_file = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			ft_error_exit(2, (char*[]){"Failed to open or create: ", filename}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){"File descriptor duplication failed"}, EXIT_REDIREC_ERROR);
	}
	close(fd_file);
	return (redirect_fd);
}

int32_t	ft_output_append_redirect(t_parser *redirect)
{
	int32_t	fd_file;
	int32_t	redirect_fd;
	char	*filename;

	if (OR_PARSER_N(redirect, 0)->retained)
	{
		redirect = OR_PARSER_N(redirect, 0);
		redirect_fd = ft_atoi(AND_PARSER_N(redirect, 0)->parser.str_any_of.str);
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(AND_PARSER_N(redirect, 1), 6), 1), 1)->parser.str_any_of.str;
		if (redirect_fd < 0)
			ft_error_exit(1, (char*[]){"Invalid File descriptor"}, EXIT_REDIREC_ERROR);
		if ((fd_file = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			ft_error_exit(2, (char*[]){"Failed to open or to create: ", filename}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){"File descriptor duplication failed"}, EXIT_REDIREC_ERROR);
	}
	else
	{
		redirect = OR_PARSER_N(redirect, 1);
		redirect_fd = STDOUT_FILENO;
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(redirect, 6), 1), 1)->parser.str_any_of.str;
		if ((fd_file = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			ft_error_exit(2, (char*[]){"Failed to open or create: ", filename}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){"File descriptor duplication failed"}, EXIT_REDIREC_ERROR);
	}
	close(fd_file);
	return (redirect_fd);
}

int32_t	ft_input_redirect(t_parser *redirect)
{
	int32_t	fd_file;
	int32_t	redirect_fd;
	char	*filename;

	if (OR_PARSER_N(redirect, 0)->retained)
	{
		redirect = OR_PARSER_N(redirect, 0);
		redirect_fd = ft_atoi(AND_PARSER_N(redirect, 0)->parser.str_any_of.str);
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(AND_PARSER_N(redirect, 1), 2), 1), 1)->parser.str_any_of.str;
		if (redirect_fd < 0)
			ft_error_exit(1, (char*[]){"Invalid File descriptor"}, EXIT_REDIREC_ERROR);
		if ((fd_file = open(filename, O_RDONLY)) == -1)
			ft_error_exit(2, (char*[]){"No such file or directory: ", filename}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){"File descriptor duplication failed"}, EXIT_REDIREC_ERROR);
	}
	else
	{
		redirect = OR_PARSER_N(redirect, 1);
		redirect_fd = STDIN_FILENO;
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(redirect, 2), 1), 1)->parser.str_any_of.str;
		if ((fd_file = open(filename, O_RDONLY)) == -1)
			ft_error_exit(2, (char*[]){"No such file or directory: ", filename}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){"File descriptor duplication failed"}, EXIT_REDIREC_ERROR);
	}
	close(fd_file);
	return (redirect_fd);
}

int32_t	ft_read_write_redirect(t_parser *redirect)
{
	int32_t	fd_file;
	int32_t	redirect_fd;
	char	*filename;

	if (OR_PARSER_N(redirect, 0)->retained)
	{
		redirect = OR_PARSER_N(redirect, 0);
		redirect_fd = ft_atoi(AND_PARSER_N(redirect, 0)->parser.str_any_of.str);
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(AND_PARSER_N(redirect, 1), 5), 1), 1)->parser.str_any_of.str;
		if (redirect_fd < 0)
			ft_error_exit(1, (char*[]){"Invalid File descriptor"}, EXIT_REDIREC_ERROR);
		if ((fd_file = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			ft_error_exit(2, (char*[]){"No such file or directory: ", filename}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){"File descriptor duplication failed"}, EXIT_REDIREC_ERROR);
	}
	else
	{
		redirect = OR_PARSER_N(redirect, 1);
		redirect_fd = STDIN_FILENO;
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(redirect, 5), 1), 1)->parser.str_any_of.str;
		if ((fd_file = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			ft_error_exit(2, (char*[]){"No such file or directory: ", filename}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){"File descriptor duplication failed"}, EXIT_REDIREC_ERROR);
	}
	close(fd_file);
	return (redirect_fd);
}

static uint32_t	ft_get_redirec_number(t_parser *redirec)
{
	if (OR_PARSER_N(redirec, 0)->retained)
	{
		redirec = OR_PARSER_N(redirec, 0);
		return (AND_PARSER_N(redirec, 1)->parser.or.matched);
	}
	else
	{
		redirec = OR_PARSER_N(redirec, 1);
		return (redirec->parser.or.matched);
	}
}

int32_t		ft_redirections(t_parser *simple_cmd)
{
	static const t_redirec	f_redirec[8] = {
		&ft_output_redirect,
		NULL,
		&ft_input_redirect,
		NULL,
		NULL,
		&ft_read_write_redirect,
		&ft_output_append_redirect,
		&ft_output_redirect
	};
	t_parser		*parser;
	uint32_t		prefix_n;
	uint32_t		postfix_n;
	uint32_t		i;

	i = 0;
	prefix_n = MULTIPLY_N(AND_PARSER_N(simple_cmd, 1));
	postfix_n = MULTIPLY_N(AND_PARSER_N(simple_cmd, 4));
	parser = AND_PARSER_N(simple_cmd, 1);
	while (i < prefix_n)
	{
		if (OR_PARSER_N(MULTIPLY_PARSER_N(parser, i), 1)->retained)
			f_redirec[ft_get_redirec_number(AND_PARSER_N(OR_PARSER_N(MULTIPLY_PARSER_N(parser, i), 1), 0))]
				(AND_PARSER_N(OR_PARSER_N(MULTIPLY_PARSER_N(parser, i), 1), 0));
		i++;
	}
	i = 0 ;
	parser = AND_PARSER_N(simple_cmd, 4);
	while (i < postfix_n)
	{
		if (OR_PARSER_N(AND_PARSER_N(MULTIPLY_PARSER_N(parser, i), 0), 0)->retained)
		{
			f_redirec[ft_get_redirec_number(OR_PARSER_N(AND_PARSER_N(MULTIPLY_PARSER_N(parser, i), 0), 0))]
				(OR_PARSER_N(AND_PARSER_N(MULTIPLY_PARSER_N(parser, i), 0), 0));
		}
		i++;
	}
	return (1);
}
