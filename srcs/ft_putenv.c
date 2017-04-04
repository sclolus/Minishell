#include "minishell.h"

int32_t		ft_putenv(t_list *env, char **argv)
{
	t_list	*lst;

	lst = NULL;
	if (!argv[1])
	{
		while (env)
		{
			ft_putendl((char*)env->content);
			env = env->next;
		}
		return (0);
	}
	if ((lst = ft_find_lst_env(env, argv[1])))
	{
		if (lst->content)
			ft_putendl((char*)lst->content);
		return (0);
	}
	else
		return (-1);
}
