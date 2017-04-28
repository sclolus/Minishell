/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 05:08:11 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/28 22:49:39 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_tilde_expansion(char **word, t_shenv *shenv)
{
	char		*word_tmp;
	char		**home_tmp;
	uint32_t	home_len;
	uint32_t	word_len;

	if (!(*word))
		return ;
	word_len = ft_strlen(*word);
	if (!(home_tmp = ft_find_var(shenv, "HOME")))
	{
//		ft_error(1, (char*[]){"HOME not defined, tilde expansion not possible"}, 2);
		return ;
	}
	home_len = ft_strlen(*home_tmp) - 5;
	if (**word != '~')
		return ;
	if (word_len > 1 && (*word)[1] != '/')
		return ;
	if (!(word_tmp = ft_strnew(sizeof(char) * (home_len + word_len))))
		exit(EXIT_FAILURE);
	ft_memcpy(word_tmp, *home_tmp + 5, home_len);
	ft_memcpy(word_tmp + home_len, *word + 1, word_len - 1);
	free(*word);
	*word = word_tmp;
}

char	*ft_get_path_name(char *file)
{
	static char	buf[MAX_PATH_NAME];
	uint32_t	i;
	int64_t		offset;

	if (!file)
		return (NULL);
	i = 0;
	offset = -1;
	buf[0] = 0;
	while (file[i])
	{
		if (file[i] == '/')
			offset = i;
		i++;
	}
	if (offset > MAX_PATH_NAME - 1)
	{
		ft_putstr_fd("Pathname too long\n", 2);
		return (NULL);
	}
	if (offset >= 0)
	{
		ft_memcpy(buf, file, offset + 1);
		buf[offset + 1] = '\0';
	}
	return (buf);
}

char	*ft_get_file_name(char *file)
{
	static char	buf[MAX_FILE_NAME];
	uint32_t	i;
	uint32_t	len;
	int64_t		offset;

	if (!file)
		return (NULL);
	i = 0;
	offset = -1;
	len = ft_strlen(file);
	while (file[i])
	{
		if (file[i] == '/')
			offset = i;
		i++;
	}
	if (len - offset > MAX_FILE_NAME)
	{
		ft_putstr_fd("Filename too long\n", 2);
		return (NULL);
	}
	if (offset == -1)
		ft_memcpy(buf, file + offset + 1, len - offset);
	else
		ft_memcpy(buf, file + offset + 1, len - offset);
	buf[len - offset] = 0;
	return (buf);
}

int32_t	ft_find_file(char *file, t_env *env)
{
	DIR				*curr_dir;
	struct dirent	*curr_entry;
	char			*filename;
	char			*pathname;

	if (env) //use PWD ?
		;
	if (!(filename = ft_get_file_name(file)))
		return (-1);
	if (!(pathname = ft_get_path_name(file)))
		return (-1);
	curr_dir = opendir(pathname); // DAFUQ parser/ == ./parser/
	if (!curr_dir)
	{
//		ft_putstr_fd("", 2);
		return (0);
	}
	while ((curr_entry = readdir(curr_dir)))
	{
		if (!ft_strcmp(filename, curr_entry->d_name))
		{
			if (-1 == (closedir(curr_dir)))
				ft_error_exit(1, (char*[]){"closedir() failed"}, 1);
			return (1);
		}
	}
	closedir(curr_dir);
	return (0);
}

int32_t	ft_expansions(t_parser *simple_cmd, t_shenv *shenv)
{
	if (IS_RETAINED(OR_PARSER_N(simple_cmd, 0)))
	{
		simple_cmd = OR_PARSER_N(simple_cmd, 0);
		ft_expansions_cmd_prefix(AND_PARSER_N(simple_cmd, 1), shenv);
		ft_tilde_expansion(&(AND_PARSER_N(simple_cmd, 2)->parser.str_any_of.str),
																	shenv);
		ft_var_expansion(&(AND_PARSER_N(simple_cmd, 2)->parser.str_any_of.str),
																	shenv);
		ft_quote_removal(&(AND_PARSER_N(simple_cmd, 2)->parser.str_any_of.str));
		ft_expansions_cmd_postfix(AND_PARSER_N(simple_cmd, 4), shenv);
	}
	else
	{
		simple_cmd = OR_PARSER_N(simple_cmd, 1);
		ft_expansions_cmd_prefix(AND_PARSER_N(simple_cmd, 0), shenv);
	}
	return (1);
}
