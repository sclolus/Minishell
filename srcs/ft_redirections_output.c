/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections_output.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 14:07:17 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/28 14:08:10 by sclolus          ###   ########.fr       */
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
		if ((fd_file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			ft_error_exit(2, (char*[]){"Failed to open or to create: ", filename}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){ERROR_BAD_FD}, EXIT_REDIREC_ERROR);
	}
	else
	{
		redirect = OR_PARSER_N(redirect, 1);
		redirect_fd = STDOUT_FILENO;
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(redirect, 0), 1), 1)->parser.str_any_of.str;
		if ((fd_file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			ft_error_exit(2, (char*[]){"Failed to open or create: ", filename}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){ERROR_BAD_FD}, EXIT_REDIREC_ERROR);
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
			ft_error_exit(1, (char*[]){ERROR_BAD_FD}, EXIT_REDIREC_ERROR);
	}
	else
	{
		redirect = OR_PARSER_N(redirect, 1);
		redirect_fd = STDOUT_FILENO;
		filename = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(redirect, 6), 1), 1)->parser.str_any_of.str;
		if ((fd_file = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			ft_error_exit(2, (char*[]){"Failed to open or create: ", filename}, EXIT_REDIREC_ERROR);
		if (dup2(fd_file, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){ERROR_BAD_FD}, EXIT_REDIREC_ERROR);
	}
	close(fd_file);
	return (redirect_fd);
}

int32_t	ft_duplicating_output_redirect(t_parser *redirect)
{
	int32_t	fd_duplicated;
	int32_t	redirect_fd;

	if (OR_PARSER_N(redirect, 0)->retained)
	{
		redirect = OR_PARSER_N(redirect, 0);
		redirect_fd = ft_atoi(AND_PARSER_N(redirect, 0)->parser.str_any_of.str);
		fd_duplicated = ft_atoi(AND_PARSER_N(OR_PARSER_N(AND_PARSER_N(redirect, 1), 1), 2)->parser.str_any_of.str);
		if (redirect_fd < 0)
			ft_error_exit(1, (char*[]){"Invalid File descriptor"}, EXIT_REDIREC_ERROR);
		if (dup2(fd_duplicated, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){ERROR_BAD_FD}, EXIT_REDIREC_ERROR);
	}
	else
	{
		redirect = OR_PARSER_N(redirect, 1);
		redirect_fd = STDOUT_FILENO;
		fd_duplicated = ft_atoi(AND_PARSER_N(OR_PARSER_N(redirect, 1), 2)->parser.str_any_of.str);
		if (dup2(fd_duplicated, redirect_fd) == -1)
			ft_error_exit(1, (char*[]){ERROR_BAD_FD}, EXIT_REDIREC_ERROR);
	}
	return (redirect_fd);
}
