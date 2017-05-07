/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 01:21:08 by sclolus           #+#    #+#             */
/*   Updated: 2017/05/07 10:18:38 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"

t_process	*current_process = NULL; // not used

char		*ft_find_env(char const **env, char const *variable)
{
	uint32_t	i;

	i = 0;
	while (variable[i] && variable[i] != '=')
		i++;
	while (*env)
	{
		if (!ft_strncmp(variable, *env, i))
			return ((char*)*env);
		else
			env++;
	}
	return (NULL);
}


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
		exit (EXIT_FAILURE);
	if (!(tmp = ft_strdup(*path)))
		exit(EXIT_FAILURE);
	len = ft_strlen(tmp) - variable_len - 1;
	ft_strncpy(*path, tmp + variable_len + 1, len + 1);
	free(tmp);
	return (path);
}

// TODO ctrl+d ctrl+c

int main(int argc, char **argv, char **env)
{
	char		*line;
	t_parser	*parser;

	line = NULL;
	ft_init_shell();
	(void)argc;
	(void)argv;
	t_shenv *shenv;
	t_tokens	*tokens;

	parser = ft_get_shell_parser();
	shenv = ft_init_shenv(ft_get_env_count(env), env);
	*ft_get_shenv() = shenv;
	ft_putchar('\n');
	while (1)
	{
		ft_putstr("\n$>");
		ft_termget_complete_line(&line, shenv);
/* 		if (!*line) */
/* 			continue ; */
		char	*tmp;
		tmp = line;
		if (!(tokens = ft_get_tokens(line)))
			exit(EXIT_FAILURE);
		if (!*tokens->tokens)
		{
			ft_free_tokens(tokens);
			continue ;
		}
		if (ft_eval_tokens_input(parser, tokens))
		{
			ft_create_heredocs(tokens, shenv);
			ft_get_heredocs(shenv);
			ft_exec_command(parser, shenv);
		}
		else
		{
			ft_putendl("parsing error ::= ");
			ft_put_ast_tokens(parser);
		}
		ft_clear_heredocs(shenv);
		ft_free_tokens(tokens);
		ft_sanitize_parser(parser);
	}
	ft_free_t_shenv(shenv);
	ft_free_t_shell();
	ft_free_parser(parser);
	ft_exit_shell(0);
	exit(EXIT_FAILURE);
	ft_putstr("test");
	return (0);
}
