/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 02:04:34 by aalves            #+#    #+#             */
/*   Updated: 2016/12/20 23:31:55 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 2

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_fd_data
{
	int		fd;
	char	buf[BUFF_SIZE + 1];
	char	*current;
}				t_fd_data;

#endif
