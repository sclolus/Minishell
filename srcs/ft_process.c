/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 21:30:16 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/20 12:37:40 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*ft_t_process_add(t_process **processes, t_process *new)
{
	new->next = *processes;
	*processes = new;
	if (new->next)
		new->next->prev = new;
	(*processes)->prev = NULL;
	return (new);
}

static void	ft_print_argv(char **argv)
{
	while (*argv)
		ft_putendl_fd(*argv++, 2);
}

void		ft_t_process_print(t_process *process)
{
	while (process)
	{
		ft_putstr_fd("\ncurrent process: ", 2);
		ft_print_argv(process->argv);
		ft_putstr_fd("\npid: ", 2);
		ft_putnbr_fd(process->pid, 2);
		ft_putstr_fd("\ngpid: ", 2);
		ft_putnbr_fd(process->gpid, 2);
		
		process = process->next;
	}
}

void		ft_clear_processes(t_process **processes)
{
	t_process	*curr_process;
	t_process	*tmp;

	curr_process = *processes;
	while (curr_process)
	{
		ft_free_argv(curr_process->argv);
		tmp = curr_process;
		curr_process = curr_process->next;
		free(tmp);
	}
}

void		ft_put_processes_in_foreground(t_process *process, int cont)
{
	ft_unset_term();
	tcsetpgrp(shell->terminal, process->gpid);
	if (cont)
	{
		ft_unset_term();
		kill(-process->gpid, SIGCONT);
	}
}
