#include "minishell.h"

int32_t	ft_buildin(char *filename, char **argv, char **env, t_list **env_lst)
{
	if (filename || env)
	{};
	if (!ft_strcmp(filename, "echo"))
	{
		ft_echo(argv);
		return (0);
	}
	else if (!ft_strcmp(filename, "cd"))
		return (ft_cd(argv, env));
	else if (!ft_strcmp(filename, "setenv"))
		return (ft_setenv(env_lst, (char const**)argv));
	else if (!ft_strcmp(filename, "unsetenv"))
   		return (ft_unsetenv(env_lst, (char const**)argv));
	else if (!ft_strcmp(filename, "putenv"))
		return (ft_putenv(*env_lst, argv));
	return (-2);
}
