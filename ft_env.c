#include "minishell.h"

t_list	*ft_get_lstenv(char **env)
{
	t_list		*lst;
	t_list		*lst_tmp;
	char		*tmp;
	uint32_t	i;

	i = 0;
	tmp = NULL;
	while (env[i])
	{
		if (!(tmp = ft_strdup(env[i])))
			exit(EXIT_FAILURE);
		if (!(lst_tmp = (t_list*)malloc(sizeof(t_list))))
			exit(EXIT_FAILURE);
		lst_tmp->content = tmp;
		ft_lstadd(&lst, lst_tmp);
		i++;
	}
	return (lst);
}

t_list	*ft_find_lst_env(t_list *env, char const *variable)
{
	uint32_t	i;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	while (env)
	{
		if (!ft_strncmp(variable, env->content, i))
			return (env);
		else
			env = env->next;
	}
	return (NULL);
}

int32_t		ft_setenv(t_list **env, char const **argv)
{
	t_list	*tmp;
	char	*tmp_str;

	tmp = NULL;
// if buf *= ?
	if (!argv[1])
		return (-1);
	if ((tmp = ft_find_lst_env(*env, (char*)argv[1])))
	{
		free((*env)->content);
		if (!(tmp_str = ft_strdup((char*)argv[1])))
			exit(EXIT_FAILURE);
		if (!(tmp_str = ft_strjoin_f(tmp_str, "=", 0)))
			exit(EXIT_FAILURE);
		if (!((*env)->content = ft_strjoin_f(tmp_str, (char*)argv[2], 0)))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (!(tmp = ft_lstnew(NULL, 0)))
			exit (EXIT_FAILURE);
		ft_lstadd(env, tmp);
		if (!(tmp_str = ft_strdup((char*)argv[1])))
			exit(EXIT_FAILURE);
		if (!argv[2])
		{
			if (!((*env)->content = ft_strjoin(tmp_str, "=")))
				exit (EXIT_FAILURE);
		}
		else
		{
			if (!(tmp_str = ft_strjoin_f(tmp_str, "=", 0)))
				exit(EXIT_FAILURE);
			if (!((*env)->content = ft_strjoin_f(tmp_str, (char*)argv[2], 0)))
				exit(EXIT_FAILURE);
		}
	}
	return (0);
}

int32_t		ft_unsetenv(t_list **env, char const **argv)
{
	t_list	*tmp;
	t_list	*buf;
	t_list	*tmp_env;

	tmp = NULL;
	tmp_env = *env;
	if (!argv[1])
		return (-1);
	if ((tmp = ft_find_lst_env(*env, (char*)argv[1])))
	{
		if (tmp == *env)
		{
			buf = (*env)->next;
			free(*env);
			*env = buf;
			return (0);
		}
		while (tmp->next != tmp_env)
			tmp = tmp->next;
		buf = tmp->next;
		free(tmp);
		tmp_env->next = buf;
		return (0);
	}
	return (-1);
}
