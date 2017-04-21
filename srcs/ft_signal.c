#include "minishell.h"
#include "libft.h"


/*static void	ft_handler_cont(int signum) //stdin not reopened
{
	if (signum == SIGCONT)		
		ft_set_term();
	else
		ft_putstr_fd("signal handling error", 2);
		}*/

static void	ft_handler_int(int signum)
{
	if (signum == SIGINT)
	{
/*		ft_set_term();
		kill(0, SIGINT);
		exit(0);*/
	}
	else
		ft_putstr_fd("signal handling error", 2);
}



void		ft_handler_tstp(int signum)
{
	if (signum == SIGTSTP)
		;
}


int32_t		ft_setup_sighandlers(void)
{
	if (signal(SIGINT, &ft_handler_int) == SIG_ERR)
		return (ft_error(1, (char*[]){"Signal handling error"}, -1));
	if (signal(SIGCHLD, SIG_DFL) == SIG_ERR)
		return (ft_error(1, (char*[]){"Signal handling error"}, -1));

	if (signal(SIGTSTP, &ft_handler_tstp) == SIG_ERR)
	return (ft_error(1, (char*[]){"Signal handling error"}, -1));
/*	if (signal(SIGCONT, &ft_handler_cont) == SIG_ERR)
	{
		ft_putstr_fd("signal handling error", 2);
		return (-1);
		}*/
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
