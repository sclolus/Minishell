/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps_completion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 09:50:12 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/13 01:25:16 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int32_t	ft_is_shell_reserved(t_string *buf, uint32_t i)
{
	if (ft_strchr("|&;<>()$`\"' \t\n", buf->string[i])
		&& !ft_is_quoted(buf->string, i))
		return (1);
	return (0);
}

static char		*ft_get_current_token(t_string *buf)
{
	char		*token;
	uint32_t	i;
	uint32_t	start;

	if (buf->offset > 0)
		i = buf->offset - 1;
	start = 0;
	while (buf->offset)
	{
		if (ft_is_shell_reserved(buf, i))
		{
			start = i + 1;
			break ;
		}
		else if (i == 0)
			break ;
		i--;
	}
	if (!(token = ft_strndup(buf->string + start, buf->offset - start)))
		exit(EXIT_FAILURE);
	return (token);
}

static uint32_t	*ft_get_lens_tab(char **strings, uint32_t n)
{
	uint32_t	*tab;
	uint32_t	i;

	if (!(tab = (uint32_t*)malloc(sizeof(uint32_t) * (n + 1))))
		exit(EXIT_FAILURE);
	tab[n] = 0;
	i = 0;
	while (i < n)
	{
		tab[i] = ft_strlen(strings[i]);
		if (tab[i] > tab[n])
			tab[n] = tab[i];
		i++;
	}
	tab[n]++;
	return (tab);
}

int32_t		ft_put_completions(t_string *buf, char **completions, uint32_t n)
{
	static struct winsize	window;
	static char				buffer[1024];
	uint32_t				*lens;
	uint32_t				i;
	uint32_t				offset;
	
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	if (buffer[0] == 0)
		ft_memset(buffer, ' ', 1023);
	i = 0;
	ft_sort_strings(completions, n);
	lens = ft_get_lens_tab(completions, n);
	ft_move_end_line(buf);
	ft_static_put("\n", 1, 0);
	offset = 0;
	while (i < n)
	{
		if ((offset + lens[n]) / window.ws_col)
		{
			ft_static_put("\n", 1, 0);
			offset = 0;
		}
		ft_static_put(completions[i], lens[i], 0);
		ft_static_put(buffer, lens[n] - lens[i], 0);
		offset += lens[n];
		i++;
	}
	ft_static_put("\n", 1, 0);
	ft_static_put(PROMPT, 2, 0);
	ft_static_put(buf->string, buf->len, 0);
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
	free(lens);
	return (n);
}

int32_t		ft_put_completion(t_ltree *ltree, char **completions
							  , t_string *buf, char *prefix)
{
	char		*max_completion;
	uint32_t	i;
	uint32_t	n;

	n = 0;
	i = 0;
	if (!completions)
	{
		ft_putchar(7);
		return (0);
	}
	while (completions[n])
		n++;
	if ((max_completion = ft_ltree_get_completion(ltree, prefix)))
	{
		if (*max_completion)
		{
			ft_putstr(max_completion);
			ft_t_string_insert(buf, max_completion);			 // TODO: test/
			free(max_completion);
			free(completions);
			return (1);
		}
		else
			ft_putchar(7);
		free(max_completion);
		if (n < 2)
			return (1);
	}
	else
	{
		ft_putchar(7);
		return (0);
	}
	if (n > 1)
		ft_put_completions(buf, completions, n);
	free(completions);
	return (1);
}

int32_t		ft_complete_path_commands(t_string *buf, t_env *env, char *command_prefix)
{
	char		**completions;
	char		**path;
	t_ltree		*ltree;
	uint32_t	i;
	int32_t		ret;

	ltree = NULL;
	path = ft_get_env_value(env->env, "PATH");
	i = 0;
	while (path[i])
	{
		if (!(ft_ltree_add_directory(&ltree, path[i++])))
		{
			free(path);
			return (0);
		}
	}
	free(path);
	if (!(completions = ft_get_ltree_suffixes(ltree, command_prefix)))
		return (0);
	ret = ft_put_completion(ltree, completions
							, buf, command_prefix);
	ft_free_ltree(ltree);
	return (ret);
}

int32_t		ft_complete_command_directory(t_string *buf, t_env *env, char *command_prefix)
{
	char		**completions;
	t_ltree		*ltree;
	char		*path;
	char		*filename;
	uint32_t	ret;

	ltree = NULL;
	if (env) // use of env ?
		;
	if (!(path = ft_get_path_name(command_prefix)))
		return (0);
	if (!(ft_ltree_add_directory_bin(&ltree, path)))
		return (0);
	if (!(filename = ft_get_file_name(command_prefix)))
		return (0);
	if (!(completions = ft_get_ltree_suffixes(ltree, filename)))
		return (0);
	ret = ft_put_completion(ltree, completions, buf, filename);
	ft_free_ltree(ltree);
	return (ret);
}

int32_t		ft_complete_command_name(t_string *buf, t_env *env)
{
	char		*command_prefix;
	int32_t		ret;

    command_prefix = ft_get_current_token(buf);
	if ((ret = ft_complete_path_commands(buf, env, command_prefix)))
	{
		free(command_prefix);
		return (1);
	}
	else
	{
		ret = ft_complete_command_directory(buf, env, command_prefix);
		if (!ret)
			ft_putchar(7);
		free(command_prefix);
		return (ret);
	}
}

int32_t		ft_complete_argv(t_string *buf, t_env *env)
{
	char	*command_prefix;

	
	char		**completions;
	t_ltree		*ltree;
	char		*path;
	char		*filename;
	uint32_t	ret;

	ltree = NULL;
	command_prefix = ft_get_current_token(buf);
	if (env) // use of env ?
		;
	if (!(path = ft_get_path_name(command_prefix)))
		return (0);
	if (!(ft_ltree_add_directory(&ltree, path)))
		return (0);
	if (!(filename = ft_get_file_name(command_prefix)))
		return (0);
	if (!(completions = ft_get_ltree_suffixes(ltree, filename)))
		return (0);
	ft_sanitize_completions(completions);
	ret = ft_put_completion(ltree, completions, buf, filename);
	ft_free_ltree(ltree);
	return (ret);
}

int32_t		ft_completion(t_string *buf, t_env *env)
{
	static const t_comp_event	events[] = {
		NULL,
		NULL,
		&ft_complete_command_name,
		&ft_complete_argv,
	};
	t_termcaps_state			*state;

	state = ft_get_term_state();
	*state = 2;
	return (events[*state](buf, env));
}
