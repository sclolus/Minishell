/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:59:02 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/06 20:48:07 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "unistd.h"
#include <signal.h>

int	main(int argc, char **argv, char **env)
{
	pid_t	tab[3];

	if ((tab[0] = fork()) != -1)
	{
		if (tab[0])
		{
			if (setpgid(tab[0], tab[0]) == -1)
			{
				ft_putstr_fd("setpgid 1 failed", 2);
				exit (EXIT_FAILURE);
			}
			ft_putstr_fd("first child created", 1);
		}
		else
 		{
			execve("./test1", argv, env);
			ft_putstr_fd("execve test1 failed", 2);
			exit (EXIT_FAILURE);
		}
	}
	else
		exit(EXIT_FAILURE);
	if ((tab[1] = fork()) != -1)
	{
		if (tab[1])
		{
			if (setpgid(tab[1], tab[0]) == -1)
			{
				ft_putstr_fd("setpgid failed", 2);
				exit(EXIT_FAILURE);
			}
			ft_putstr_fd("second child created and added to gpid of the second child", 1);
		}
		else
		{
			execve("./test2", argv, env);
			ft_putstr_fd("execve test2 failed", 2);
			exit (EXIT_FAILURE);
		}
	}
	else
		exit(EXIT_FAILURE);
	ft_putnbr_fd(getpgid(0), 2);
	ft_putchar_fd('\n', 2);
	ft_putnbr_fd(getpgid(tab[0]), 2);
	ft_putchar_fd('\n', 2);
	ft_putnbr_fd(getpgid(tab[1]), 2);
	ft_putchar_fd('\n', 2);
	ft_putchar_fd('-', 2);
	ft_putnbr_fd(tab[0], 2);
	ft_putchar_fd('-', 2);
	kill(-tab[0], SIGINT);
	while (1)
		;
	return (0);
}
