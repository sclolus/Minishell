#include "minishell.h"

char	*ft_find_command(char *filename, char **path)
{
	static char oldpwd[MAX_PATH];
	uint32_t	i;

	i = 0;
	getcwd(oldpwd, MAX_PATH); // not protected;
	while (path[i])
	{
		if (chdir(path[i]) == -1)
		{
			ft_putendl_fd("chdir() failed", 2);
			exit(EXIT_FAILURE); // not necessary
		}
		if (!(access(filename, F_OK)))
		{
			if (!(access(filename, X_OK)))
			{
				if (chdir(oldpwd) == -1)
					ft_putendl_fd("chdir() failed", 2);
				return (path[i]);
			}
			else
			{
				ft_putstr_fd(SHELL_NAME, 2);
				ft_putstr_fd(filename, 2);
				ft_putstr_fd(": Permission denied", 2);
				if (chdir(oldpwd) == -1)
					ft_putendl_fd("chdir() failed", 2);
				return (NULL);
			}
		}
		else
			i++;
	}
	ft_putstr_fd(filename, 2);
	ft_putendl_fd(" : Could not be found", 2);
	if (chdir(oldpwd) == -1)
		ft_putendl_fd("chdir() failed", 2);
	return (NULL);
}
