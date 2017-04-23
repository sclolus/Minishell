 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps_completion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 09:50:12 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/23 07:57:47 by sclolus          ###   ########.fr       */
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

# if 1
static void	ft_termcaps_go_back_to_offset(t_string *buf, int64_t old_offset)
{
	char	*res;

	while (buf->offset > 0 && buf->offset > old_offset)
	{
		buf->offset--;
		res = tgetstr("le", NULL);
		tputs(res, 1, &ft_putterm);
	}
}
#endif

int32_t		ft_put_completions(t_string *buf, char **completions, uint32_t n, char *prefix)
{
	static struct winsize	window;
	static char				buffer[1024];
	uint32_t				*lens;
	uint32_t				i;
	uint32_t				offset;
	int64_t					old_offset;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	if (!window.ws_col)
		return (0);
	if (buffer[0] == 0)
		ft_memset(buffer, ' ', 1023);
	i = 0;
	ft_sort_strings(completions, n);
	lens = ft_get_lens_tab(completions, n);
	old_offset = buf->offset;
	ft_move_end_line(buf);
	ft_static_put("\n", 1, 0);
	offset = 0;
	while (i < n)
	{
		if (*completions[i] == '.' && *prefix != '.')
		{
			i++;
			continue ;
		}
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
	ft_termcaps_go_back_to_offset(buf, old_offset);
	free(lens);
	return (n);
}

int32_t		ft_put_max_completion(t_ltree *ltree, t_string *buf, char *prefix, uint32_t n)
{
	char		*max_completion;
	
	if ((max_completion = ft_ltree_get_completion(ltree, prefix)))
	{
		if (*max_completion)
		{
			ft_t_string_insert(buf, max_completion);
			ft_termcaps_putstr(buf, max_completion);
			free(max_completion);
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
	return (-1);
}

int32_t		ft_put_completion(t_ltree *ltree, char **completions
							  , t_string *buf, char *prefix)
{
	uint32_t	i;
	uint32_t	n;
	int32_t		ret;

	n = 0;
	i = 0;
	if (!completions)
	{
		ft_putchar(7);
		return (0);
	}
	while (completions[n])
		n++;
	if ((ret = ft_put_max_completion(ltree, buf, prefix, n)) > -1)
	{
		free(completions);
		return (ret);
	}
	if (n > 1)
		ft_put_completions(buf, completions, n, prefix);
	free(completions);
	return (1);
}

int32_t		ft_complete_path_commands(t_string *buf, t_shenv *shenv, char *command_prefix)
{
	char		**completions;
	char		**path;
	t_ltree		*ltree;
	uint32_t	i;
	int32_t		ret;

	ltree = NULL;
	ft_free_t_env(shenv->env);
	shenv->env = ft_get_env(shenv);
	path = ft_get_env_value(shenv->env->env, "PATH");
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

int32_t		ft_complete_command_directory(t_string *buf, t_shenv *shenv, char *command_prefix)
{
	char		**completions;
	t_ltree		*ltree;
	char		*path;
	char		*filename;
	uint32_t	ret;

	ltree = NULL;
	if (shenv) // use of env ?
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

int32_t		ft_complete_command_name(t_string *buf, t_shenv *shenv)
{
	char		*command_prefix;
	int32_t		ret;

    command_prefix = ft_get_current_token(buf);
	if ((ret = ft_complete_path_commands(buf, shenv, command_prefix)))
	{
		free(command_prefix);
		return (1);
	}
	else
	{
		ret = ft_complete_command_directory(buf, shenv, command_prefix);
		if (!ret)
			ft_putchar(7);
		free(command_prefix);
		return (ret);
	}
}

int32_t		ft_complete_argv(t_string *buf, t_shenv *shenv)
{
	char	*command_prefix;
	char		**completions;
	t_ltree		*ltree;
	char		*path;
	char		*filename;
	uint32_t	ret;

	ltree = NULL;
	command_prefix = ft_get_current_token(buf);
	if (shenv) // use of env ?
		;
	if (!(path = ft_get_path_name(command_prefix))
		|| !ft_ltree_add_directory(&ltree, path)
		|| !(filename = ft_get_file_name(command_prefix))
		|| !(completions = ft_get_ltree_suffixes(ltree, filename)))
	{
		free(command_prefix);
		ft_putchar(7);
		return (0);
	}
	ret = ft_put_completion(ltree, completions, buf, filename);
	ft_free_ltree(ltree);
	free(command_prefix);
	return (ret);
}

int32_t		ft_completion_normal_state(t_string *buf, t_shenv *shenv)
{
	if (buf && shenv)
		;
	ft_putchar(7);
	return (0);
}

int32_t		ft_completion(t_string *buf, t_shenv *shenv)
{
	static const t_comp_event	events[] = {
		NULL,
		&ft_completion_normal_state,
		&ft_complete_command_name,
		&ft_complete_argv,
	};
	t_termcaps_state			*state;

	ft_set_term_state(buf);
	state = ft_get_term_state();
	return (events[*state](buf, shenv));
}
