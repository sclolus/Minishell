#include "minishell.h"
#include "libft.h"

char	*ft_find_command(char *filename, char **path)
{
	static char oldpwd[MAX_PATH];
	uint32_t	i;

	i = 0;
	getcwd(oldpwd, MAX_PATH); // not protected;
	if (!path)
		return (NULL);
	if (*filename == '/')
		filename++;
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
	if (chdir(oldpwd) == -1)
		ft_putendl_fd("chdir() failed", 2);
	return (NULL);
}
