/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built-in_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 13:23:24 by sclolus           #+#    #+#             */
/*   Updated: 2017/04/05 13:34:06 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static uint32_t	ft_get_history_len(t_list *history_list)
{
	t_list		*base;
	uint32_t	len;

	len = 0;
	base = history_list;
	while (history_list)
	{
		history_list = history_list->next;
		len++;
		if (base == history_list)
			return (len);
	}
	return (len);
}

int32_t			ft_print_history_list(char *offset)
{
	t_list		*history_list;
	uint32_t	offset_nbr;
	uint32_t	i;
	uint32_t	len;

	i = 0;
	history_list = *ft_get_history_list();
	if (offset)
	{
		if (*offset == '-') // if offset isn't a nubmer 
			return (ft_error(3, (char*[]){"history: ", offset, ": Numeric offset required"}, -1)); //
		offset_nbr = ft_atoi(offset);
		len = ft_get_history_len(history_list);
	}
	else
	{
		len = 0;
		offset_nbr = 0;
	}
	history_list = *ft_get_history_list();
	while (history_list && i < len - offset_nbr)
	{
		i++;
		history_list = history_list->next;
	}
	while (history_list)
	{
		ft_putstr("    ");
		ft_putnbr(i);
		ft_putstr("    ");
		ft_putstr(history_list->content);
		ft_putchar('\n');
		i++;
		history_list = history_list->next;
	}
	return (0);
}

static int32_t	ft_expand_argv(t_env *env, char **argv)
{
	t_list	*tmp;
	t_list	*base;
	t_list	*history_list;
	t_list	*string;

	history_list = ft_get_history_list();
	base = history_list;
	if (!history_list)
		return (-1);
	while (history_list->next && history->next != base)
		history_list = history_list->next;
	if (!(string = ft_implode_strings(argv)))
		return (-1);
	if (!(tmp = ft_lstnew(0, 0)))
		exit(EXIT_FAILURE);
	tmp->content = string;
	tmp->prev = history_list;
	history_list->next = tmp;
	tmp->next = base;
	return (0);
}

static int32_t	ft_delete_history_list(t_env *env, char *offset)
{
	int32_t		offset_nbr;
	int32_t		i;
	t_list		*history_list;
	t_list		*base;

	if (env) //
		;
	offset_nbr = ft_atoi(offset);
	if (offset_nbr < 0)
		return (ft_error(2, (char*[]){"history: ", "offset out of range"}, -1));
	history_list = *ft_get_history_list();
	base = history_list;
	i = 0;
	while (history_list && history_list->next != base && i < offset_nbr)
	{
		history_list = history_list->next;
		i++;
	}
	if (i == offset_nbr && history_list)
	{
		base = history_list;
		history_list->prev->next = history_list->next;
		free(history_list->content);
		free(history_list);
		return (0);
	}
	else
		return (ft_error(2, (char*[]){"history: ", "offset out of range"}, -1));
}

static int32_t	ft_clear_history_list(t_env *env)
{
	t_list	**history;
	t_list	*history_list;
	t_list	*base;
	t_list	*tmp;

	history = ft_get_history_list();
	history_list = *history;
	base = history_list;
	while (history_list && history_list->next != base)
	{
		tmp = history_list;
		history_list = history_list->next;
		free(tmp->content);
		free(tmp);
	}
	history = NULL;
	return (0);
}

/*
**	history -cdanrwps
**	static char	flags[8] = "cdanrwps";
**	history: usage: history [-c] [-d offset] [n] or history -awrn [filename] or history -ps arg [arg...]
*/

static char		ft_set_flags(char *string)
{
	static const char	flags[] = "cdanrwps";
	static char			buf[] = "--";
	uint32_t			ret;
	uint32_t			i;
	char				tmp;

	i = 1;
	tmp = 0;
	while (string[i])
	{
		if ((ret = ft_strchr_index(flags, string[i])) < 8)
			tmp |= 1 << ret;
		else
		{
			buf[1] = string[i];
			ft_error(3, (char*[]){"history: ", buf, ": invalid option"}, 0);
			return (ft_error(1, (char*[]){"history: usage: history [-c] [-d offset] [n] or \n
history -awrn [filename] or history -ps arg [arg...]", 1)));
		}
		i++;
	}
	return (tmp);
}

static char		ft_get_history_flags(char **argv)
{
	char		flags;
	uint32_t	i;
	uint32_t	u;

	i = 1;
	u = 0;
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "--"))
			break;
		else if (argv[i][u] == '-')
			ret = ft_set_flags(argv[i]);
		else
			break;
		i++;
	}
	return (flags);
}

int32_t			ft_built_in_history(char **argv, t_env *env)
{
	static char	history_file[MAX_PATH_NAME + MAX_FILENAME];
	char		*tmp;
	int32_t		fd;
	char		flags;

	flags = ft_get_history_flags(argv);
	if (!*history_file)
	{
		if (!(tmp = ft_find_env((const char**)env->env, "HOME")))
			return (1, (char*[]){ft_error("HOME not defined, tilde expansion not possible", 2)}, -1);
		ft_strcat(history_file, tmp + 5);
		ft_strcat(history_file, "/.42sh_history");
	}
	if ((fd = open(history_file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
		return (-1);
	if (env && fd)
		;
	ft_print_history_list(argv[1]);
	if (0)
		ft_delete_history_list(env, 0);
	
	close(fd);
	return (0);
}
