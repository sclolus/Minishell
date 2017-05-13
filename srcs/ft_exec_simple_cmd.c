/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 22:20:45 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/13 18:36:31 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t		ft_exec_env_assignment(t_parser *parser, t_shenv *shenv)
{
	char	*var;

	var = ft_strjoin(AND_PARSER_N(parser, 0)->parser.str_any_of.str, "=");
	var = ft_strjoin_f(var, AND_PARSER_N(parser, 2)->parser.str_any_of.str, 0);
	ft_modify_var(shenv, var);
	free(var);
	return (0);
}

int32_t		ft_exec_cmd_prefix(t_parser *cmd_prefix, t_shenv *shenv)
{
	uint32_t	i;
	uint32_t	n;

	i = 0;
	n = MULTIPLY_N(cmd_prefix);
	while (i < n)
	{
		if (IS_RETAINED(OR_PARSER_N(MULTIPLY_PARSER_N(cmd_prefix, i), 0)))
			ft_exec_env_assignment(AND_PARSER_N(
				OR_PARSER_N(MULTIPLY_PARSER_N(cmd_prefix, i), 0), 0), shenv);
		i++;
	}
	return (0);
}

static void	ft_exec_cmd_bin(char **argv, t_shenv *shenv, char *path
							, char **env_values)
{
	char	*bin;

	if (!(path = ft_strjoin(path, "/")))
		ft_error_exit(2, (char *[]){ERR_MALLOC, argv[0]}, EXIT_FAILURE);
	if (!(bin = ft_strjoin(path, argv[0])))
		ft_error_exit(2, (char *[]){ERR_MALLOC, bin}, EXIT_FAILURE);
	if (access(bin, X_OK))
		ft_error_exit(2, (char *[]){ERR_PERM_DENIED, bin}
		, EXIT_NO_PERM);
	ft_free_strsplit(env_values);
	execve(bin, argv, shenv->env->env);
	ft_error_exit(2, (char *[]){ERR_PERM_DENIED, bin}, EXIT_NO_PERM);
	exit(EXIT_FAILURE);
}

void		ft_exec_cmd(char **argv, t_shenv *shenv)
{
	char	**env_values;
	char	*path;

	env_values = ft_get_env_value(shenv->env->env, "PATH");
	if (!(path = ft_find_command(argv[0], env_values)))
	{
		if (ft_find_file(argv[0], shenv->env) > 0)
		{
			if (!ft_check_exec_perm(argv[0]))
				ft_error_exit(2, (char *[]){ERR_PERM_DENIED, argv[0]}, 126);
			execve(argv[0], argv, shenv->env->env);
			ft_free_strsplit(env_values);
			ft_error_exit(2, (char *[]){ERR_PERM_DENIED, argv[0]}, 126);
		}
		ft_free_strsplit(env_values);
		ft_error_exit(2, (char *[]){ERR_ILL_CMD, argv[0]}, EXIT_ILLEGAL_CMD);
	}
	ft_exec_cmd_bin(argv, shenv, path, env_values);
}

int32_t		ft_exec_simple_cmd(t_parser *simple_cmd, t_shenv *shenv)
{
	char	**argv;
	int		ret;

	ret = 0;
	ft_expansions(simple_cmd, shenv);
	if (IS_RETAINED(OR_PARSER_N(simple_cmd, 0)))
	{
		shenv->env = ft_get_env(shenv);
		simple_cmd = OR_PARSER_N(simple_cmd, 0);
		ft_exec_cmd_prefix(AND_PARSER_N(simple_cmd, 1), shenv);
		argv = ft_get_argv(simple_cmd);
		if (ft_redirections(simple_cmd) == -1)
			exit(EXIT_REDIREC_ERROR);
		if ((ret = ft_built_in(argv, shenv)) == EXIT_ILLEGAL_CMD)
			ft_exec_cmd(argv, shenv);
		free(argv);
		ft_free_t_env(shenv->env);
		shenv->env = NULL;
	}
	else
	{
		simple_cmd = OR_PARSER_N(simple_cmd, 1);
		ft_exec_cmd_prefix(AND_PARSER_N(simple_cmd, 0), shenv);
	}
	return (ret);
}
