/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 06:54:33 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/28 22:49:43 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_shenv		*ft_modify_env(char **argv, uint32_t count, t_shenv *shenv)
{
	uint32_t	i;

	i = 1;
	if (!shenv)
		ft_error_exit(1
		, (char*[]){"malloc() failed to init subshell environnement"}, 1);
	while (i < count + 1)
	{
		ft_modify_var(shenv, argv[i]);
		ft_set_var_to_export(shenv, argv[i]);
		i++;
	}
	return (shenv);
}

static t_shenv		*ft_create_new_shenv(char **argv
										, uint32_t count)
{
	uint32_t	i;
	t_shenv		*new_shenv;

	i = 1;
	if (!(new_shenv = (t_shenv*)ft_memalloc(sizeof(t_shenv))))
		exit(EXIT_FAILURE);
	while (i < count + 1)
	{
		ft_modify_var(new_shenv, argv[i]);
		ft_set_var_to_export(new_shenv, argv[i++]);
	}
	return (new_shenv);
}

static uint32_t		ft_count_values(char **argv)
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

void				ft_built_in_exec_env_cmd(char **argv
						, t_shenv *shenv, t_shenv *exec_env)
{
	char	*bin;
	char	*path;

	if (!(path = ft_find_command(argv[0], ft_get_env_value(shenv->env->env,
																"PATH"))))
	{
		if (ft_find_file(argv[0], shenv->env) > 0)
		{
			if (!ft_check_exec_perm(argv[0]))
				ft_error_exit(2, (char *[]){ERR_PERM_DENIED
							, argv[0]}, EXIT_NO_PERM);
			execve(argv[0], argv, exec_env->env->env);
			ft_error_exit(2, (char *[]){ERR_PERM_DENIED
						, argv[0]}, EXIT_NO_PERM);
		}
		ft_error_exit(2, (char *[]){ERR_ILL_CMD, argv[0]}, EXIT_ILLEGAL_CMD);
	}
	if (!(path = ft_strjoin_f(path, "/", 0)))
		ft_error_exit(2, (char *[]){ERR_MALLOC, argv[0]}, EXIT_FAILURE);
	if (!(bin = ft_strjoin(path, argv[0])))
		ft_error_exit(2, (char *[]){ERR_MALLOC, bin}, EXIT_FAILURE);
	if (access(bin, X_OK))
		ft_error_exit(2, (char *[]){ERR_PERM_DENIED, bin}, EXIT_NO_PERM);
	execve(bin, argv, exec_env->env->env);
	ft_error_exit(2, (char *[]){ERR_PERM_DENIED, bin}, EXIT_NO_PERM);
}

static int32_t		ft_built_in_print_env(t_shenv *shenv)
{
	uint32_t	i;

	i = 0;
	while (i < shenv->count)
	{
		if (shenv->attr[i])
			ft_putendl(shenv->var[i]);
		i++;
	}
	return (0);
}

int32_t				ft_built_in_env(char **argv, t_shenv *shenv)
{
	int32_t		flag;
	uint32_t	argc;
	int32_t		ret;
	pid_t		pid;
	t_shenv		*exec_env;

	if (!argv[1])
		return (ft_built_in_print_env(shenv));
	if ((pid = fork()) == -1)
		ft_error_exit(1, (char*[]){"env: Fork() failed"}, 1);
	if (pid)
	{
		waitpid(pid, &ret, 0);
		ft_put_shell_in_foreground();
		return (POSIX_EXIT_STATUS(ret));
	}
	else
	{
		flag = 0;
		if ((flag = ft_get_flag(argv[1])) == -1)
			exit(EXIT_FAILURE);
		argc = ft_count_values(argv + flag);
		if (flag == 1)
			exec_env = ft_create_new_shenv(argv + 1, argc);
		else
			exec_env = ft_modify_env(argv, argc
			, ft_init_shenv(shenv->env->variable_count, shenv->env->env));
		if (!argv[argc + flag + 1])
		{
			ft_built_in_print_env(exec_env);
			exit(EXIT_SUCCESS);
		}
		shenv->env = ft_get_env(shenv);
		exec_env->env = ft_get_env(exec_env);
		setpgid(0, getpid());
		tcsetpgrp(shell->terminal, getpid());
		ft_built_in_exec_env_cmd(argv + argc + 1 + flag, shenv, exec_env);
	}
	return (0);
}
