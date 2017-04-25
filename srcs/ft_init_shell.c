/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 03:24:20 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/25 16:19:35 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_shell(void)
{
	if (!(shell = (t_shell*)malloc(sizeof(t_shell))))
		ft_error_exit(1, (char*[]){"Shell initialization failed"}, 1);
	shell->terminal = STDIN_FILENO;
	shell->interactive = isatty(shell->terminal);
	if (shell->interactive)
	{
		while (tcgetpgrp(shell->interactive)
			   != (shell->shell_pgid = getpgrp()))
			kill(-shell->shell_pgid, SIGSTOP);
		ft_ignore_signals();
		shell->shell_pgid = getpid();
		if (-1 == (setpgid(shell->shell_pgid, shell->shell_pgid)))
			ft_error_exit(1, (char*[]){"Shell initialization failed"}, 1);
		tcsetpgrp(shell->terminal, shell->shell_pgid);
		tcgetattr(shell->terminal, &shell->backup_term);
		if (-1 == ft_set_term())
			ft_error_exit(1, (char*[]){"Shell initialization failed"}, 1);
		ft_setup_sighandlers();
	}
}

void	ft_exit_shell(void)
{
	ft_unset_term();
	ft_unset_insert();
	exit(EXIT_SUCCESS);
}

void	ft_put_shell_in_foreground(void)
{
	ft_set_term();
	tcsetpgrp(shell->terminal, shell->shell_pgid);
}
