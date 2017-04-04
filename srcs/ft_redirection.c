/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 14:22:32 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/03 18:16:58 by sclolus          ###   ########.fr       */
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
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(redirect, 0), 1), 6)->parser.str_any_of.str;
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
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(AND_PARSER_N(redirect, 1), 2), 1), 1)->parser.str_any_of.str;
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
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(redirect, 2), 1), 1)->parser.str_any_of.str;
		if ((fd_file = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			ft_error_exit(2, (char*[]){"No such file or directory: ", filename}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){"File descriptor duplication failed"}, EXIT_REDIREC_ERROR);
	}
	close(fd_file);
	return (redirect_fd);
}

int32_t	ft_redirections(t_parser *redirect)
{
	if (ft_output_redirect(redirect) == -1) // test
		return (-1);
	return (1);
}
