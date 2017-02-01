#include "minishell.h"

void	ft_echo(char **argv) // remember env
{
	uint32_t	i;
	uint32_t	argc;
	uint8_t		flags;

	i = 1;
	flags = 0;
	while (argv[argc])
		argc++;
	if (argc >= 2 && !ft_strcmp(argv[1], "-n"))
	{
		flags = 1;
		i++;
	}
	while (i < argc)
	{
		ft_putstr(argv[i++]);
		if (i < argc)
			ft_putchar(' ');
	}
	if (!flags)
		ft_putchar('\n');
}
