/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 22:14:37 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/10 09:32:44 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#if 0
int32_t	ft_exec_list(t_parser *parser, t_env *env)
{
	uint32_t	i;
	uint32_t	n;

	if (IS_RETAINED(OR_PARSER_N(parser, 0)))
	{
		parser = OR_PARSER_N(parser, 0);
		i = 0;
		n = MULTIPLY_N(AND_PARSER_N(parser, 0));
		ft_putendl("____");
		ft_put_ast_tokens(AND_PARSER_N(parser, 1));
		ft_putendl("____");
		while (i < n)
		{
			ft_exec_and_or(AND_PARSER_N(MULTIPLY_PARSER_N(AND_PARSER_N(parser, 0), i), 0), env);
			i++;
		}
		CHECK(TEST);
		ft_put_ast_tokens(AND_PARSER_N(parser, 1));
		ft_exec_and_or(AND_PARSER_N(parser, 1), env);
		return (1);
	}
	else if (IS_RETAINED(OR_PARSER_N(parser, 1)))
	{
		parser = OR_PARSER_N(parser, 1);
		ft_exec_simple_cmd(AND_PARSER_N(parser, 0), env);
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

int32_t	ft_exec_pipeline(t_parser *parser, t_env *env)
{
	if (OR_PARSER_N(parser, 0)->retained)
		return (ft_exec_pipe_sequence(OR_PARSER_N(parser, 0), env));
	else
		return (!ft_exec_pipe_sequence(AND_PARSER_N(OR_PARSER_N(parser, 1), 1), env));
}

t_process		*ft_create_pipeline(t_parser *pipe_sequence, t_env *env)
{
	t_process	*processes;
	int	curr_stdin;
	int	curr_stdout;
	int	pipe[2];
	int	i;

	i = 0;
	curr_stdin = 0;
	while (i < MULTIPLY_N(AND_PARSER_N(parser, 0)))
	{
		if (pipe(pipe) == -1)
			return (ft_error(1, (char*[]){"Pipe() failed"}, EXIT_REDIREC_ERROR));
		curr_stdout = pipe
		i++;
	}
	
}

int32_t	ft_exec_pipe_sequence(t_parser *parser, t_env *env)
{
	t_process	*processes;
	t_process	*tmp;
	pid_t		pipeline_pgid;
	uint32_t	i;
	uint32_t	n;
	int			pipe[2];
	
	if (IS_RETAINED(OR_PARSER_N(parser, 0)))
	{
		parser = OR_PARSER_N(parser, 0);
		processes = ft_start_process(parser, 0, (int[]){1, 0}, env);
		waitpid(processes->pid, &i, 0);
		free(processes->argv);
		free(argv);
		return (i);
	}
	else
	{
		parser = OR_PARSER_N(parser, 1);
		n = MULTIPLY_N(AND_PARSER_N(parser, 0));
		i = 0;
		if (pipe(pipe) == -1)
			return (ft_error(1, (char*[]){"Pipe() failed"}, EXIT_REDIREC_ERROR));
		processes = ft_start_process(MULTIPLY_PARSER_N(
										 AND_PARSER_N(parser, 0), 0), 0, (int[]){pipe[1], 0}, env);
		pipeline_pgid = processes->pid;
		tmp = processes;
		while (i < n - 1)
		{
			tmp->next = ft_start_process(MULTIPLY_PARSER_N(
											 AND_PARSER_N(parser, 0), i), pipeline_pgid
										 , , env);
			i++;
		}
	}
}

t_process	*ft_start_process(t_parser *simple_cmd, pid_t gpid, int *stdfd, t_env *env)
{
	t_process	*process;
	pid_t		pid;
	char		**argv;


	if (IS_RETAINED(OR_PARSER_N(parser, 0)))
		argv = ft_get_argv(parser);
	if (-1 == (pid = fork()))
	{
		ft_error(1, "fork() failed due to insufficient ressource", 0);
		return (NULL);
	}
	if (pid)
	{
		if (!(process = (t_process*)malloc(sizeof(t_process))))
			exit(EXIT_FAILURE);
		setpgid(pid, gpid);
		process->pid = pid;
		process->next = NULL;
		process->prev = NULL;
		process->argv = argv;
		return (process);
	}
	else
	{
		setpgid(0, gpid);
		dup2(stdfd[1], STDIN_FILENO);
		close(stdfd[1]);
		dup2(stdfd[0], STDOUT_FILENO);
		close(stdfd[0]);
		ft_exec_simple_cmd(argv, simple_cmd, env)
	}
}



int32_t	ft_exec_env_assignment(t_parser *parser, t_env *env)
{
	/* todo */
	if (parser || env)
		;
	return (0);
}


void	ft_exec_cmd(char **argv, t_env *env) //last arg test
{
	char	*bin;
	char	*path;

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
	if (!(path = ft_strjoin(path, "/")))
		ft_error_exit(2, (char *[]){"Internal memory management failed at: ", argv[0]}, EXIT_FAILURE);
	if (!(bin = ft_strjoin(path, argv[0])))
		ft_error_exit(2, (char *[]){"Internal memory management failed at: ", bin}, EXIT_FAILURE);
	if (access(bin, X_OK))
		ft_error_exit(2, (char *[]){"Permission denied: ", bin}, EXIT_NO_PERM);
	execve(bin, argv, env->env);
	ft_error_exit(2, (char *[]){"Permission denied: ", bin}, EXIT_NO_PERM);
	exit(EXIT_FAILURE);
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



void		ft_exec_simple_cmd(char **argv, t_parser *parser, t_env *env)
{
	if (IS_RETAINED(OR_PARSER_N(parser, 0)))
	{
//		ft_expansions(parser, env);
		parser = OR_PARSER_N(parser, 0);
	   	if (ft_redirections(parser) == -1)
			exit(EXIT_REDIREC_ERROR);
		if (ft_built_in(argv, env) == EXIT_ILLEGAL_CMD)
			ft_exec_cmd(argv, env, parser);
		exit(EXIT_ILLEGAL_CMD);
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
#endif
