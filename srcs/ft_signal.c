#include "minishell.h"
#include "libft.h"


static void	ft_handler_int(int signum) //stdin not reopened
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


static void	ft_handler_cont(int signum)
{
	if (signum == SIGCONT)
	{
		shell->shell_pgid = getpid();
		shell->interactive = isatty(shell->terminal);
		while (tcgetpgrp(shell->interactive)
			   != (shell->shell_pgid))
			kill(-shell->shell_pgid, SIGSTOP);
		ft_set_term();
	}
	else
		ft_putstr_fd("signal handling error", 2);
}

int32_t		ft_setup_sighandlers(void)
{
	if (signal(SIGINT, &ft_handler_int) == SIG_ERR)
		return (ft_error(1, (char*[]){"Signal handling error"}, -1));
	if (signal(SIGCHLD, SIG_DFL) == SIG_ERR)
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
