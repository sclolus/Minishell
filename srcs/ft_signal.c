#include "minishell.h"
#include "libft.h"


static void	ft_handler_cont(int signum) //stdin not reopened
{
	if (signum == SIGCONT)		
		ft_set_term();
	else
		ft_putstr_fd("signal handling error", 2);
}

static void	ft_handler_int(int signum)
{
	if (signum == SIGINT)
	{
		ft_set_term();
		kill(0, SIGINT);
		exit(0);
	}
	else
		ft_putstr_fd("signal handling error", 2);
}

int32_t		ft_setup_sighandlers(void)
{
	if (signal(SIGINT, &ft_handler_int) == SIG_ERR)
	{
		ft_putstr_fd("signal handling error", 2);
		return (-1);
	}
	if (signal(SIGCONT, &ft_handler_cont) == SIG_ERR)
	{
		ft_putstr_fd("signal handling error", 2);
		return (-1);
	}
	return (1);
}