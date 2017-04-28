/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 00:10:50 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/29 00:15:14 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
