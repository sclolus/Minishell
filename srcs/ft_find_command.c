/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 16:21:16 by aalves            #+#    #+#             */
/*   Updated: 2017/04/28 16:59:43 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static char		*ft_back_return(char *oldpwd, char *ret)
{
	if (chdir(oldpwd) == -1)
		ft_error(2, (char*[]){SHELL_NAME, "chdir() failed"}, -1);
	return (ret);
}

char			*ft_find_command(char *filename, char **path)
{
	static char oldpwd[MAX_PATH];
	uint32_t	i;

	i = 0;
	getcwd(oldpwd, MAX_PATH);
	if (!path)
		return (NULL);
	*filename == '/' ? filename++ : 0;
	while (path[i])
	{
		if (chdir(path[i]) == -1)
			ft_error(2, (char*[]){SHELL_NAME, "chdir() failed"}, -1);
		if (!(access(filename, F_OK)))
		{
			if (access(filename, X_OK))
			{
				ft_error(2, (char*[]){filename, ": Permission denied"}, -1);
				return (ft_back_return(oldpwd, NULL));
			}
			return (ft_back_return(oldpwd, path[i]));
		}
		else
			i++;
	}
	return (ft_back_return(oldpwd, NULL));
}
