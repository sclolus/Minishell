/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:17:55 by aalves            #+#    #+#             */
/*   Updated: 2017/05/11 15:04:12 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	ft_sigchld_handler(int signum)
{
	if (signum == SIGCHLD)
		ft_putstr("a child exited");
}

int32_t		ft_setup_sighandlers(void)
{
	if (signal(SIGINT, &ft_handler_int) == SIG_ERR)
		return (ft_error(1, (char*[]){"Signal handling error"}, -1));
	if (signal(SIGCHLD, &ft_sigchld_handler) == SIG_ERR)
		return (ft_error(1, (char*[]){"Signal handling error"}, -1));
	if (signal(SIGTSTP, &ft_handler_tstp) == SIG_ERR)
		return (ft_error(1, (char*[]){"Signal handling error"}, -1));
	if (signal(SIGCONT, &ft_handler_cont) == SIG_ERR)
		return (ft_error(1, (char*[]){"Signal handling error"}, -1));
	return (1);
}

void		ft_reset_signals(void)
{
	int	i;

	i = 1;
	while (i < 32)
		signal(i++, SIG_DFL);
}

void		ft_ignore_signals(void)
{
	int	i;

	i = 1;
	while (i < 32)
		signal(i++, SIG_IGN);
}
