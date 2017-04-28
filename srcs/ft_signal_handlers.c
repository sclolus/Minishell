/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:17:24 by aalves            #+#    #+#             */
/*   Updated: 2017/04/28 18:37:04 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void		ft_handler_int(int signum)
{
	if (signum == SIGINT)
		ft_exit_shell();
	else
		ft_putstr_fd("signal handling error", 2);
}

void		ft_handler_tstp(int signum)
{
	if (signum == SIGTSTP)
		;
}

void		ft_handler_cont(int signum)
{
	if (signum == SIGCONT)
	{
		shell->shell_pgid = getpgrp();
		shell->interactive = isatty(shell->terminal);
		while (tcgetpgrp(shell->interactive)
				!= (shell->shell_pgid))
			kill(-shell->shell_pgid, SIGSTOP);
	}
	else
		ft_putstr_fd("signal handling error", 2);
}
