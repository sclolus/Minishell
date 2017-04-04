#include "minishell.h"

static int32_t		ft_setenv_cd(t_list **env, char *variable, char *value)
{
	t_list	*tmp;
	char	*tmp_str;

	tmp = NULL;
// if buf *= ?
	if (!variable)
		return (-1);
	if ((tmp = ft_find_lst_env(*env, variable)))
	{
		free((*env)->content);
		if (!(tmp_str = ft_strdup(variable)))
			exit(EXIT_FAILURE);
		if (!(tmp_str = ft_strjoin_f(tmp_str, "=", 0)))
			exit(EXIT_FAILURE);
		if (!((*env)->content = ft_strjoin_f(tmp_str, value, 0)))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(tmp = ft_lstnew(NULL, 0)))
			exit (EXIT_FAILURE);
		ft_lstadd(env, tmp);
		if (!(tmp_str = ft_strdup(variable)))
			exit(EXIT_FAILURE);
		if (!value)
		{
			if (!((*env)->content = ft_strjoin(tmp_str, "=")))
				exit (EXIT_FAILURE);
		}
		else
		{
			if (!(tmp_str = ft_strjoin_f(tmp_str, "=", 0)))
				exit(EXIT_FAILURE);
			if (!((*env)->content = ft_strjoin_f(tmp_str, value, 0)))
				exit(EXIT_FAILURE);
		}
	}
	return (0);
}

int32_t	ft_cd(char **argv, t_list **env)
{
	static char	oldpwd[4096] = "";

	getcwd(oldpwd, 4096);
	if (!argv[1] || !ft_strcmp("~", argv[1]))
	{
		if (chdir(5 + (char*)((t_list)*ft_find_lst_env(*env, "HOME")).content) == -1)
		{
			ft_putendl_fd("ERROR FT_CD", 2);
			return (-1);
		}
		ft_setenv_cd(env, "PWD", (char*)((t_list)*ft_find_lst_env(*env, "HOME")).content);
		return (0);
	}
	if (!ft_strcmp("-", argv[1]))
	{
		ft_putstr(oldpwd);
		if (chdir(oldpwd) == -1)
		{
			ft_putendl_fd("ERROR FT_CD", 2);
			return (-1);
		}
		ft_setenv_cd(env, "PWD", oldpwd);
		ft_strclr(oldpwd);
		ft_strcpy(oldpwd, argv[1]);
	}
	else
	{
		if (chdir(argv[1]) == -1)
		{
			ft_putendl_fd("ERROR FT_CD", 2);
			return (-1);
		}
		ft_setenv_cd(env, "PWD", argv[1]);
	}
	return (0);
}
