#include "minishell.h"

int32_t	ft_execve(char *filename, char *path, char **argv, char **env)
{
	char	*bin;

	if (!(bin = ft_strjoin(path, "/")))
		exit(EXIT_FAILURE);
	if (!(bin = ft_strjoin_f(bin, filename, 0)))
		exit(EXIT_FAILURE);
	if (filename)
	{
		if (execve(bin, argv, env))
			ft_putstr("error has occured");
		exit (EXIT_FAILURE);
	}
	return (-1);
}
