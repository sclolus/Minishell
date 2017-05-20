/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <sclolus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 01:21:08 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/20 05:19:55 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"

char		**ft_get_env_value(char **env, char *variable)
{
	char		**path;
	char		*tmp;
	uint32_t	len;
	uint32_t	variable_len;
	char		*var;

	path = NULL;
	tmp = NULL;
	variable_len = ft_strlen(variable);
	if (!(var = ft_find_env((char const**)env, variable)))
		return (NULL);
	if (!(path = ft_strsplit(var, ':')))
		exit(EXIT_FAILURE);
	if (!(tmp = ft_strdup(*path)))
		exit(EXIT_FAILURE);
	len = ft_strlen(tmp) - variable_len - 1;
	ft_strncpy(*path, tmp + variable_len + 1, len + 1);
	free(tmp);
	return (path);
}

void		ft_main_cleanup(t_parser *parser, t_shenv *shenv)
{
	ft_free_t_shenv(shenv);
	ft_free_t_shell();
	ft_free_parser(parser);
	ft_exit_shell(0);
}

static void	ft_clean_loop(t_parser *parser, char **line,
							t_shenv *shenv, t_tokens *tokens)
{
	if ((*ft_get_line_attributes()).multiple_lines)
	{
		free(*line);
		*line = NULL;
	}
	ft_clear_heredocs(shenv);
	ft_free_tokens(tokens);
	ft_sanitize_parser(parser);
}

static void	ft_main_loop(t_parser *parser, char **line, t_shenv *shenv)
{
	t_tokens	*tokens;

	while (42)
	{
		ft_set_and_put_prompt(NORMAL_PROMPT);
		ft_termget_complete_line(line, shenv);
		if (!(tokens = ft_get_tokens(*line)))
			exit(EXIT_FAILURE);
		if (!*tokens->tokens)
		{
			ft_free_tokens(tokens);
			continue ;
		}
		ft_fix_tokens(tokens);
		if (ft_eval_tokens_input(parser, tokens))
		{
			ft_create_heredocs(tokens, shenv);
			ft_get_heredocs(shenv);
			ft_exec_command(parser, shenv);
		}
		else
			ft_putendl("Parsing error in command line");
		ft_clean_loop(parser, line, shenv, tokens);
	}
}

int			main(int argc __attribute__((unused))
				, char **argv __attribute__((unused)), char **env)
{
	char		*line;
	t_parser	*parser;
	t_shenv		*shenv;

	line = NULL;
	ft_init_shell();
	parser = ft_get_shell_parser();
	shenv = ft_init_shenv(ft_get_env_count(env), env);
	*ft_get_shenv() = shenv;
	ft_putchar('\n');
	ft_main_loop(parser, &line, shenv);
	ft_main_cleanup(parser, shenv);
	return (0);
}
