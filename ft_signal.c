#include "minishell.h"
#include "libft.h"


void	ft_sighandler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar('\n');
		kill(0, SIGINT);
		exit(0);
	}
	else if (signum == SIGSTOP)
	{
		kill(1, SIGSTOP);
		ft_putstr("test");
	}
	else if (signum == SIGCONT)
	{
		ft_putstr("continued");
		kill(1, SIGCONT);
	}
}
