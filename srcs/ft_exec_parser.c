/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 22:14:37 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/05 15:08:25 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	ft_exec_list(t_parser *parser, t_env *env)
{
	uint32_t	i;
	uint32_t	n;

	if (IS_RETAINED(OR_PARSER_N(parser, 0)))
	{
		parser = OR_PARSER_N(parser, 0);
		i = 0;
		n = MULTIPLY_N(AND_PARSER_N(parser, 0));
		while (i < n)
		{
			ft_exec_and_or(AND_PARSER_N(MULTIPLY_PARSER_N(AND_PARSER_N(parser, 0), i), 0), env);
			i++;
		}
		ft_exec_and_or(AND_PARSER_N(parser, 1), env);
		return (1);
	}
	else if (IS_RETAINED(OR_PARSER_N(parser, 1)))
	{
		parser = OR_PARSER_N(parser, 1);
		ft_exec_and_or(AND_PARSER_N(parser, 0), env);
		return (1);
	}
	else
		return (-1);
}

int32_t	ft_exec_and_or(t_parser *parser, t_env *env)
{
	uint32_t	i;
	uint32_t	n;
	uint32_t	ret;

	i = 0;
	n = PLUS_N(parser);
	while (i < n)
	{
		if (OR_PARSER_N(PLUS_PARSER_N(parser, i), 0)->retained && !ret)
			ret = ft_exec_simple_cmd(AND_PARSER_N(OR_PARSER_N(PLUS_PARSER_N(parser, i), 0), 3), env);
		else if (OR_PARSER_N(PLUS_PARSER_N(parser, i), 1)->retained && ret)
			ret = ft_exec_simple_cmd(AND_PARSER_N(OR_PARSER_N(PLUS_PARSER_N(parser, i), 1), 3), env);
		else if (OR_PARSER_N(PLUS_PARSER_N(parser, i), 2)->retained)
			ret = ft_exec_simple_cmd(AND_PARSER_N(OR_PARSER_N(PLUS_PARSER_N(parser, i), 2), 1), env);
		i++;
	}
	return (ret);
}

int32_t	ft_exec_env_assignment(t_parser *parser, t_env *env)
{
	/* todo */
	if (parser || env)
		;
	return (0);
}

int32_t	ft_exec_cmd(char **argv, t_env *env, t_parser *simple_cmd) //last arg test
{
	pid_t	pid;
	char	*bin;
	char	*path;
	int		ret;

	if ((pid = fork()) == -1)
	{
		ft_putstr_fd("fork() failed due to insufficient ressource", 2); // ft_error
		return (-1);
	}
	if (pid > 0)
	{
		waitpid(pid, &ret, 0);
		return (ret);
	}
	else
	{
		if (ft_redirections(simple_cmd) == -1)
			exit(EXIT_REDIREC_ERROR);
		if (!(path = ft_find_command(argv[0], ft_get_env_value(env->env, "PATH"))))
		{
			if (ft_find_file(argv[0], env) > 0)
			{
				if (access(argv[0], X_OK)) // use stat with geteuid
					exit(EXIT_NO_PERM);
				execve(argv[0], argv, env->env);
				ft_error_exit(2, (char *[]){"Permission denied: ", argv[0]}, EXIT_NO_PERM);
			}
			ft_error_exit(2, (char *[]){"Command not found: ", argv[0]}, EXIT_ILLEGAL_CMD);
		}
		if (!(path = ft_strjoin(path, "/"))) // wtf on ~
			ft_error_exit(2, (char *[]){"Internal memory management failed at: ", argv[0]}, EXIT_FAILURE);
		if (!(bin = ft_strjoin(path, argv[0])))
			ft_error_exit(2, (char *[]){"Internal memory management failed at: ", bin}, EXIT_FAILURE);
		if (access(bin, X_OK))
			ft_error_exit(2, (char *[]){"Permission denied: ", bin}, EXIT_NO_PERM);
		execve(bin, argv, env->env);
		ft_error_exit(2, (char *[]){"Permission denied: ", bin}, EXIT_NO_PERM);
		exit(EXIT_FAILURE);
	}
}

static uint32_t	ft_get_arg_count(t_parser *cmd_postfixes)
{
	uint32_t	i;
	uint32_t	count;
	uint32_t	n;

	i = 0;
	count = 0;
	n = MULTIPLY_N(cmd_postfixes);
	while (i < n)
	{
		if (OR_PARSER_N(AND_PARSER_N(MULTIPLY_PARSER_N(cmd_postfixes, i), 0), 1)->retained)
			count++;
		i++;
	}
	return (count);
}

static char		**ft_get_argv(t_parser *simple_cmd)
{
	char		**argv;
	uint32_t	argc;
	uint32_t	n;
	uint32_t	i;
	uint32_t	count;

	argc = ft_get_arg_count(AND_PARSER_N(simple_cmd, 4)) + 2;
	if (!(argv = (char**)malloc(sizeof(char*) * (argc))))
		exit(EXIT_FAILURE);
	argv[argc - 1] = NULL;
	argv[0] = AND_PARSER_N(simple_cmd, 2)->parser.str_any_of.str;
	n = MULTIPLY_N(AND_PARSER_N(simple_cmd, 4));
	count = 0;
	i = 0;
	while (i < n)
	{
		if (OR_PARSER_N(AND_PARSER_N(MULTIPLY_PARSER_N(AND_PARSER_N(simple_cmd, 4), i), 0), 1)->retained)
		{
			argv[count + 1] = OR_PARSER_N(AND_PARSER_N(MULTIPLY_PARSER_N(AND_PARSER_N(simple_cmd, 4), i), 0), 1)->parser.str_any_of.str;
			count++;
		}
		i++;
	}
	return (argv);
}

int32_t		ft_exec_simple_cmd(t_parser *parser, t_env *env)
{
	char		**argv;
	int32_t		ret;

	if (IS_RETAINED(OR_PARSER_N(parser, 0)))
	{
//		ft_expansions(parser, env);
		parser = OR_PARSER_N(parser, 0);

		argv = ft_get_argv(parser); // NULL ?
		if ((ret = ft_built_in(argv, env)) == EXIT_ILLEGAL_CMD)
			ret = ft_exec_cmd(argv, env, parser);
		free(argv);
		return (ret);
		//	return (ft_exec_env_assignment(OR_PARSER_N(parser, 0), env));
	}
	else
	{
		return (-1);
	}
}

int32_t	ft_exec_command(t_parser *parser, t_env *env)
{
	if (IS_RETAINED(parser))
	{
		// debug ?
		return (ft_exec_list(AND_PARSER_N(parser, 1), env));
	}
	else
		return (-1);
}

int32_t	ft_exec_parser(t_parser *parser, t_env *env)
{
	return (ft_exec_command(parser->parser.multiply.parsers[0], env));
}
