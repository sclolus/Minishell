/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 22:14:37 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/26 17:33:16 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (OR_PARSER_N(AND_PARSER_N(MULTIPLY_PARSER_N(cmd_postfixes, i),
														0), 1)->retained)
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
		if (OR_PARSER_N(AND_PARSER_N(MULTIPLY_PARSER_N(AND_PARSER_N(simple_cmd,
													4), i), 0), 1)->retained)
		{
			argv[count + 1] = OR_PARSER_N(AND_PARSER_N(MULTIPLY_PARSER_N(
						AND_PARSER_N(simple_cmd, 4), i), 0),
						1)->parser.str_any_of.str;
			count++;
		}
		i++;
	}
	return (argv);
}

int32_t	ft_exec_list(t_parser *parser, t_shenv *shenv)
{
	uint32_t	i;
	uint32_t	n;
	
	if (IS_RETAINED(OR_PARSER_N(parser, 1)))
	{
		parser = OR_PARSER_N(parser, 1);
		i = 0;
		n = PLUS_N(parser);
		while (i < n)
			ft_exec_and_or(AND_PARSER_N(PLUS_PARSER_N(parser
														, i++), 0), shenv);
		return (1);
	}
	else if (IS_RETAINED(OR_PARSER_N(parser, 0)))
	{
		parser = OR_PARSER_N(parser, 0);
		i = 0;
		n = MULTIPLY_N(AND_PARSER_N(parser, 0));
		while (i < n)
			ft_exec_and_or(AND_PARSER_N(MULTIPLY_PARSER_N(AND_PARSER_N(parser,
															0), i++), 0), shenv);
		ft_exec_and_or(AND_PARSER_N(parser, 1), shenv);
		return (1);
	}
	else
		return (-1);
}

int32_t	ft_exec_and_or(t_parser *parser, t_shenv *shenv)
{
	uint32_t	i;
	uint32_t	n;
	uint32_t	ret;

	i = 0;
	n = PLUS_N(parser);
	while (i < n)
	{
		if (OR_PARSER_N(PLUS_PARSER_N(parser, i), 0)->retained && !ret)
			ret = ft_exec_pipeline(AND_PARSER_N(OR_PARSER_N(
				PLUS_PARSER_N(parser, i), 0), 3), shenv);
		else if (OR_PARSER_N(PLUS_PARSER_N(parser, i), 1)->retained && ret)
			ret = ft_exec_pipeline(AND_PARSER_N(OR_PARSER_N(
				PLUS_PARSER_N(parser, i), 1), 3), shenv);
		else if (OR_PARSER_N(PLUS_PARSER_N(parser, i), 2)->retained)
			ret = ft_exec_pipeline(AND_PARSER_N(OR_PARSER_N(
				PLUS_PARSER_N(parser, i), 2), 1), shenv);
		i++;
	}
	return (ret);
}

int32_t	ft_exec_pipeline(t_parser *parser, t_shenv *shenv)
{
	if (OR_PARSER_N(parser, 0)->retained)
		return (ft_exec_pipe_sequence(OR_PARSER_N(parser, 0), shenv));
	else
		return (!ft_exec_pipe_sequence(AND_PARSER_N(OR_PARSER_N(parser,
														1), 1), shenv));
}

t_process		*ft_create_pipeline(t_parser *pipe_sequence, t_shenv *shenv)
{
	t_process	*processes;
	pid_t		pipeline_pgid;
	int			curr_stdin;
	int			curr_stdout;
	int			mypipe[5];
	uint32_t	i;

	i = 0;
	curr_stdin = 0;
	if (pipe(mypipe + 3) == -1)
		exit(ft_error(1, (char*[]){"Pipe() failed"}, EXIT_REDIREC_ERROR));
	processes = ft_start_process(AND_PARSER_N(pipe_sequence, 1), 0,
									(int[]){mypipe[3], 1, mypipe[4], 1}, shenv);
	pipeline_pgid = processes->pid;
	mypipe[2] = 0;
	while (i < MULTIPLY_N(AND_PARSER_N(pipe_sequence, 0)))
	{
		if (i == MULTIPLY_N(AND_PARSER_N(pipe_sequence, 0)) - 1)
		{
			curr_stdout = mypipe[4];
			mypipe[3] = 1;
		}
		else if (pipe(mypipe) == -1)
			exit(ft_error(1, (char*[]){"Pipe() failed"}, EXIT_REDIREC_ERROR));
		else
		{
			curr_stdout = mypipe[1];
			mypipe[3] = mypipe[0];
		}
		ft_t_process_add(&processes, ft_start_process(AND_PARSER_N(
			MULTIPLY_PARSER_N(AND_PARSER_N(pipe_sequence, 0), i), 0),
			pipeline_pgid, (int[]){curr_stdin, curr_stdout, mypipe[2],
			mypipe[3]}, shenv));
		i++;
		if (curr_stdin != STDIN_FILENO)
			close(curr_stdin);
		if (curr_stdout != STDOUT_FILENO)
			close(curr_stdout);
		curr_stdin = mypipe[0];
		mypipe[2] = mypipe[1];
	}
	return (processes);
}

int32_t	ft_exec_built_in(t_parser *parser, t_shenv *shenv)
{
	char	**argv;
	int32_t	ret;

	if (IS_RETAINED(OR_PARSER_N(parser, 0)))
		parser = OR_PARSER_N(parser, 0);
	else
		return (EXIT_ILLEGAL_CMD);
	if (ft_is_built_in(parser))
	{
		argv = ft_get_argv(parser);
		shenv->env = ft_get_env(shenv);
		ft_expansions(parser, shenv);
	   	if (ft_redirections(parser) == -1)
			exit(EXIT_REDIREC_ERROR);
		ret = ft_built_in(argv, shenv);
		free(argv);
		return (POSIX_EXIT_STATUS(ret));
	}
	return (EXIT_ILLEGAL_CMD);
}

int32_t	ft_exec_pipe_sequence(t_parser *parser, t_shenv *shenv)
{
	t_process	*processes;
	int			ret;

	if (IS_RETAINED(OR_PARSER_N(parser, 1)))
	{
		parser = OR_PARSER_N(parser, 1);
		if (!(ft_is_built_in(parser) || IS_RETAINED(OR_PARSER_N(parser, 1))))
		{
			processes = ft_start_process(parser, 0, (int[]){0, 1, 0, 1}, shenv);
			ft_putnbr(ft_get_cmd_heredoc_count(parser));
			ft_put_processes_in_foreground(processes, 1);
			waitpid(processes->gpid, &ret, WUNTRACED);
			ft_put_shell_in_foreground();
			kill(-processes->gpid, SIGKILL);
			ft_clear_processes(&processes);
		}
		else
			ret = ft_exec_simple_cmd(parser, shenv);
	}
	else
	{
		parser = OR_PARSER_N(parser, 0);
		processes = ft_create_pipeline(parser, shenv);
		ft_put_processes_in_foreground(processes, 1);
		waitpid(processes->gpid, &ret, WUNTRACED);
		kill(-processes->gpid, SIGKILL);
		ft_put_shell_in_foreground();
		ft_clear_processes(&processes);
	}
	return (POSIX_EXIT_STATUS(ret));
}

void		ft_put_stds(char **argv, int *stdfd)
{
	ft_putendl("");
	ft_putstr(argv[0]);
	ft_putstr(": stdin:");
	ft_putnbr(stdfd[0]);
	ft_putstr(": stdout:");
	ft_putnbr(stdfd[1]);
	ft_putendl("");
}

t_process	*ft_start_process(t_parser *simple_cmd, pid_t gpid,
									int *stdfd, t_shenv *shenv)
{
	t_process	*process;
	pid_t		pid;
	char		**argv;
	int			ret;

	if (-1 == (pid = fork()))
		exit(ft_error(1, (char*[]){"fork() failed due to insufficient \
			ressource"}, EXIT_REDIREC_ERROR));
	if (pid)
	{
		while (!waitpid(pid, &ret, WNOHANG | WUNTRACED) && !WIFSTOPPED(ret))
			kill(pid, SIGTSTP);
		if (IS_RETAINED(OR_PARSER_N(simple_cmd, 0)))
			argv = ft_get_argv(OR_PARSER_N(simple_cmd, 0));
		if (!(process = (t_process*)ft_memalloc(sizeof(t_process))))
			exit(EXIT_FAILURE);
		if (!gpid)
			gpid = pid;
		setpgid(pid, gpid);
		process->pid = pid;
		process->gpid = gpid;
		process->argv = argv;
		CHECK(HEREDOC_COUNT);
		ft_putnbr(ft_get_cmd_heredoc_count(simple_cmd));
		CHECK(HEREDOC_COUNT);
		return (process);
	}
	else
	{
		if (!gpid)
			gpid = getpid();
		setpgid(0, gpid);
		tcsetpgrp(shell->terminal, gpid);
		ft_reset_signals();
		dup2(stdfd[0], STDIN_FILENO);
		dup2(stdfd[1], STDOUT_FILENO);
		stdfd[2] == STDIN_FILENO ? 0 : close(stdfd[2]);
		stdfd[3] == STDOUT_FILENO ? 0 : close(stdfd[3]);
		ft_exec_simple_cmd(simple_cmd, shenv);
		exit(EXIT_FAILURE);
	}
}

int32_t	ft_exec_env_assignment(t_parser *parser, t_shenv *shenv)
{
	char	*var;

	var = ft_strjoin(AND_PARSER_N(parser, 0)->parser.str_any_of.str, "=");
	var = ft_strjoin_f(var, AND_PARSER_N(parser, 2)->parser.str_any_of.str, 0);
	ft_modify_var(shenv, var);
	free(var);
	return (0);
}

int32_t	ft_exec_cmd_prefix(t_parser *cmd_prefix, t_shenv *shenv)
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
	return (0); // ?
}

void	ft_exec_cmd(char **argv, t_shenv *shenv) //last arg test
{
	char	*bin;
	char	*path;

	if (!(path = ft_find_command(argv[0], ft_get_env_value(shenv->env->env,
																"PATH"))))
	{
		if (ft_find_file(argv[0], shenv->env) > 0)
		{
			if (!ft_check_exec_perm(argv[0])) // use stat with geteuid
				ft_error_exit(2, (char *[]){"Permission denied: ", argv[0]}, EXIT_NO_PERM);
			execve(argv[0], argv, shenv->env->env);
			ft_error_exit(2, (char *[]){"Permission denied: ", argv[0]}, EXIT_NO_PERM);
		}
		ft_error_exit(2, (char *[]){"Command not found: ", argv[0]}, EXIT_ILLEGAL_CMD);
	}
	if (!(path = ft_strjoin_f(path, "/", 0)))
		ft_error_exit(2, (char *[]){"Internal memory management failed at: ", argv[0]}, EXIT_FAILURE);
	if (!(bin = ft_strjoin(path, argv[0])))
		ft_error_exit(2, (char *[]){"Internal memory management failed at: ", bin}, EXIT_FAILURE);
	if (access(bin, X_OK))
		ft_error_exit(2, (char *[]){"Permission denied: ", bin}, EXIT_NO_PERM);
	execve(bin, argv, shenv->env->env);
	ft_error_exit(2, (char *[]){"Permission denied: ", bin}, EXIT_NO_PERM);
	exit(EXIT_FAILURE);
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
	}
	else
	{
		simple_cmd = OR_PARSER_N(simple_cmd, 1);
		ft_exec_cmd_prefix(AND_PARSER_N(simple_cmd, 0), shenv);
	}
	return (ret);
}

int32_t	ft_exec_command(t_parser *parser, t_shenv *shenv)
{
	if (IS_RETAINED(parser))
	{
		// debug ?
		return (ft_exec_list(AND_PARSER_N(parser, 1), shenv));
	}
	else
		return (-1);
}

int32_t	ft_exec_parser(t_parser *parser, t_shenv *shenv)
{
	CHECK(TEST);
	return (ft_exec_command(parser->parser.multiply.parsers[0], shenv));
}
