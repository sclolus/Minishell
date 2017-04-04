/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 07:31:36 by sclolus           #+#    #+#             */
/*   Updated: 2017/03/28 09:00:57 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_parser	*ft_load_parser(char *filename)
{
	static char		buf[4096];
	char			*input;
	uint32_t		len;
	int32_t			ret;
	int32_t			fd;

	if (!(input = ft_strnew(0)))
		exit(EXIT_FAILURE);
	parser = NULL;
	if ((fd = open(filename, O_RDONLY) <= 0))
		return (NULL);
	while ((ret = read(fd, buf, 4096)) > 0)
	{
		buf[ret] = '\0';
		if (ret == -1)
		{
			free(input);
			return (NULL);
		}
		if (!(input = ft_strjoin_f(input, buf, 0)))
			exit(EXIT_FAILURE);
	}
	if (!(len = ft_strlen(input)) || len % sizeof(t_parser))
	{
		free(input);
		return(NULL);
	}
	ft_assign_parsers((t_parser*)input, len / sizeof(t_parser));
	return (input);
}
