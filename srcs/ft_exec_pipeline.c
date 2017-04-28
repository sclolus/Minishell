/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 22:19:15 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/29 00:06:40 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	shenv->heredocs_index += ft_get_cmd_heredoc_count(AND_PARSER_N(pipe_sequence, 1));
	pipeline_pgid = processes-> pid;
	mypipe[2] = 0;
	while (i < MULTIPLY_N(AND_PARSER_N(pipe_sequence, 0)))
	{
		if (i == MULTIPLY_N(AND_PARSER_N(pipe_sequence, 0)) - 1)
		{
			curr_stdout = mypipe[4];
			mypipe[3] = 1;
		}
		else if (pipe(mypipe) == -1)
x			exit(ft_error(1, (char*[]){"Pipe() failed"}, EXIT_REDIREC_ERROR));
		else
		{
			curr_stdout = mypipe[1];
			mypipe[3] = mypipe[0];
		}
		ft_t_process_add(&processes, ft_start_process(AND_PARSER_N(
			MULTIPLY_PARSER_N(AND_PARSER_N(pipe_sequence, 0), i), 0),
			pipeline_pgid, (int[]){curr_stdin, curr_stdout, mypipe[2],
			mypipe[3]}, shenv));
		shenv->heredocs_index += ft_get_cmd_heredoc_count(AND_PARSER_N(
						MULTIPLY_PARSER_N(AND_PARSER_N(pipe_sequence, 0), i), 0));
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

static void	ft_restore_fds(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	dup2(fd[2], STDERR_FILENO);
	close(fd[2]);
}

static void	ft_store_fds(int *restored_fds)
{
	restored_fds[0] = dup(STDIN_FILENO);
	restored_fds[1] = dup(STDOUT_FILENO);
	restored_fds[2] = dup(STDERR_FILENO);
}

int32_t	ft_exec_pipe_sequence(t_parser *parser, t_shenv *shenv)
{
	int			restored_fds[3];
	t_process	*processes;
	int			ret;

	if (IS_RETAINED(OR_PARSER_N(parser, 1)))
	{
		parser = OR_PARSER_N(parser, 1);
		ft_store_fds(restored_fds);
		if (!(ft_is_built_in(parser) || IS_RETAINED(OR_PARSER_N(parser, 1))))
		{
			processes = ft_start_process(parser, 0, (int[]){0, 1, 0, 1}, shenv);
			ft_put_processes_in_foreground(processes, 1);
			waitpid(processes->gpid, &ret, WUNTRACED);
			ft_put_shell_in_foreground();
			kill(-processes->gpid, SIGKILL);
			ft_clear_processes(&processes);
		}
		else
			ret = ft_exec_simple_cmd(parser, shenv);
		shenv->heredocs_index += ft_get_cmd_heredoc_count(parser);
		ft_restore_fds(restored_fds);
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
