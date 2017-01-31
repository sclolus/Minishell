#include "minishell.h"

int32_t	ft_cd(char **argv, char **env)
{
	static char	oldpwd[4096] = "";

	if (!argv[1])
		if (chdir(5 + ft_find_env(env, "HOME")) == -1)
		{
			ft_putendl_fd("ERROR FT_CD", 2);
			return (-1);
		}
	if (!ft_strcmp("-", argv[1]))
	{
		ft_putstr(oldpwd);
		if (chdir(oldpwd) == -1)
		{
			ft_putendl_fd("ERROR FT_CD", 2);
			return (-1);
		}
		ft_strclr(oldpwd);
		ft_strcpy(oldpwd, argv[1]);
	}
	else
	{
		ft_putnbr(123);
		if (chdir(argv[1]) == -1)
		{
			ft_putendl_fd("ERROR FT_CD", 2);
			return (-1);
		}
	}
	return (0);
}
