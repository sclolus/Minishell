/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 06:54:33 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/15 20:50:16 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			**ft_find_env_value(t_env *env, char *variable)
{
	uint32_t	i;
	uint32_t	u;

	i = 0;
	u = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	while (env->env[u])
	{
		if (!ft_strncmp(variable, env->env[u], i))
			return (env->env + u);
		else
			u++;
	}
	return (NULL);
}

static void			ft_extand_env(char *argv, char **tmp, t_env *env)
{
	if (!(tmp = (char**)malloc(sizeof(char*)
							* (env->variable_count + 2))))
		exit(EXIT_FAILURE);
	tmp[env->variable_count + 1] = NULL;
	ft_memcpy(tmp, env->env, sizeof(char**) * env->variable_count);
	if (!(tmp[env->variable_count] = ft_strnew(ft_strlen(argv))))
		exit(EXIT_FAILURE);
	ft_strcpy(tmp[env->variable_count], argv);
	free(env->env);
	env->env = tmp;
	env->variable_count++;
}

static int32_t		ft_modify_env(char **argv, int32_t count, t_env *env)
{
	uint32_t	i;
	char		**tmp;

	i = 1;
	while (i < count + 1)
	{
		tmp = ft_find_env_value(env, argv[i]);
		if (tmp)
		{
			free(*tmp);
			if (!(*tmp = ft_strdup(argv[i])))
				exit(EXIT_FAILURE);
		}
		else
			ft_extand_env(argv[i], tmp, env);
		i++;
	}
	return (0);
}

static void			ft_create_new_env(char **argv, int32_t count, t_env *env)
{
	uint32_t	i;
	char		*tmp;

	i = 1;
	free(env->env);
	env->variable_count = count;
	if (!(env->env = (char**)malloc(sizeof(char*) * (count + 1))))
		exit(EXIT_FAILURE);
	env->env[count] = NULL;
	while (i < count + 1)
	{
		if (!(tmp = ft_strdup(argv[i])))
			exit(EXIT_FAILURE);
		env->env[i - 1] = tmp;
		i++;
	}
}

static int32_t		ft_count_values(char **argv)
{
	uint32_t	i;
	uint32_t	count;

	i = 1;
	count = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
			count++;
		i++;
	}
	return (count);
}

static int32_t		ft_get_flag(char *flag)
{
	static const char	flags[] = "i";
	static char			buf[] = "--";
	uint32_t			ret;
	uint32_t			i;
	char				tmp;

	i = 1;
	tmp = 0;
	if (*flag != '-')
		return (0);
	while (flag[i])
	{
		if ((ret = ft_strchr_index((char*)flags, flag[i])) < 1)
			tmp |= 1 << ret;
		else
		{
			buf[1] = flag[i];
			ft_error(3, (char*[]){"env: ", buf, ": invalid option"}, 0);
			return (ft_error(1, (char*[]){"usage: env \
[-i] [name=value ...] [utility [argument ...]]"}, -1));
		}
		i++;
	}
	return (tmp);
}

//void	ft_exec_cmd_test(char **argv, t_env *env); //

int32_t				ft_built_in_env(char **argv, t_env *env)
{
	int32_t	flag;
	int32_t	argc;
	int32_t	ret;
	pid_t	pid;

	if ((pid = fork()) == -1)
		ft_error_exit(1, (char*[]){"env: Fork() failed"}, 1);
	if (pid)
	{
		waitpid(pid, &ret, 0);
		return (POSIX_EXIT_STATUS(ret));
	}
	else
	{
		flag = 0;
		if ((flag = ft_get_flag(argv[1])) == -1)
			return (1);
		argc = ft_count_values(argv + flag);
		if (flag == 1)
			ft_create_new_env(argv + 1, argc, env);
		else
			ft_modify_env(argv, argc, env);
		ft_exec_cmd_test(argv + argc + 1 + flag, env);
	}
	return (0);
}
