/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 01:18:14 by aalves            #+#    #+#             */
/*   Updated: 2017/04/05 03:05:38 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_generate_filename(void)
{
	uint32_t	i;
	char		*name;

	i = 0;
	if (!(name = ft_strnew(12)))
		ft_error_exit(1, (char*[]){"Malloc error"}, EXIT_FAILURE);
	while (i < 11)
		name[i++] = ft_random() % 27 + 'A';
}

int32_t	ft_heredoc_redirect(t_parser *redirect)
{
	int32_t	filename;
	int32_t	redirect_fd;
	char	*line;
	char	*delimiter;


	filename =
	if (OR_PARSER_N(redirect, 0)->retained)
	{
		redirect = OR_PARSER_N(redirect, 0);
		redirect_fd = ft_atoi(AND_PARSER_N(redirect, 0)->parser.str_any_of.str);
		delimiter = AND_PARSER_N(AND_PARSER_N(OR_PARSER_N(AND_PARSER_N(redirect, 1), 2), 1), 1)->parser.str_any_of.str;
		if (redirect_fd < 0)
			ft_error_exit(1, (char*[]){"Invalid File descriptor"}, EXIT_REDIREC_ERROR);
		while (1)
		{
			ft_putstr("\nheredoc>");
			ft_termget(&line);
			if (!ft_strcmp(line, delimiter))
				break;
			write(redirect_fd, line, )

		}
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
