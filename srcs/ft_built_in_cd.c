/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalves <aalves@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 18:51:10 by aalves            #+#    #+#             */
/*   Updated: 2017/04/28 19:20:55 by aalves           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		ft_set_flags(char *string)
{
	static const char	flags[] = "PL";
	static char			buf[] = "--";
	uint32_t			ret;
	uint32_t			i;
	char				tmp;

	i = 1;
	tmp = 0;
	while (string[i])
	{
		if ((ret = ft_strchr_index((char*)flags, string[i])) < 8)
			tmp |= 1 << ret;
		else
		{
			buf[1] = string[i];
			ft_error(3, (char*[]){"cd: ", buf, ": invalid option"}, 0);
			return (ft_error(1, (char*[]){"cd: usage: cd [-L|-P] [dir]"}, 1));
		}
		i++;
	}
	return (tmp);
}

static char		ft_get_cd_flags(char **argv)
{
	char		flags;
	char		ret;
	uint32_t	i;

	i = 1;
	flags = 0;
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "--"))
			break ;
		else if (argv[i][0] == '-')
		{
			ret = ft_set_flags(argv[i]);
			if (ret == -1)
				return (-1);
			flags |= ret;
		}
		else
			break ;
		i++;
	}
	return (flags);
}

static int32_t	get_home(t_string *curpath, t_shenv *shenv)
{
	char **home;

	if (!(home = ft_find_var(shenv, "HOME")))
	    return (0);
	ft_bzero(curpath->string, MAX_PATH_NAME);
	curpath->len = 0;
	curpath->offset = 0;
	ft_t_string_concat(curpath, *home + 5);
	return (1);
}


static int32_t	convert_path(t_string *p)
{
	int64_t	i;

	i = 2;
	if (p->string[ft_strlen(p->string) - 1] != '/')
		ft_t_string_concat(p, "/");
	p->offset = 0;
	while (p->string[p->offset])
	{
		if (!ft_strncmp(p->string + p->offset, "./", 2))
		{
			ft_strcpy(p->string + p->offset, p->string + p->offset + 2);
			p->len -= 2;
			continue;
		}
		else if (!ft_strncmp(p->string + p->offset, "../", 3))
		{
			while (p->offset > i && p->string[p->offset - i] != '/')
				i++;
			if (p->offset < i)
			{
			    ft_bzero(p->string, MAX_PATH_NAME);
			    ft_t_string_concat(p, "/");
			    return (1);
			}
			ft_strcpy(p->string + p->offset - i, p->string + p->offset + 2);
			p->len -= i + 2;
			p->offset -= i;
			i = 2;
			continue;
		}
		else if (!ft_strncmp(p->string + p->offset, "///", 3))
		{
			ft_strcpy(p->string + p->offset, p->string + p->offset + 2);
			p->len -= 2;
			continue;
		}
		else if (!ft_strncmp(p->string + p->offset, ".../", 4))
		{
		    p->offset += 4;
		    continue;
		}
		p->offset++;
	}
	return (1);
}

static int32_t	ft_cd_set_env(char *cwd, t_shenv *shenv)
{
	char		tmp[MAX_PATH_NAME + 10];

	ft_strcpy(tmp, "OLDPWD=");
	ft_strcpy(tmp + 7, cwd);
	ft_modify_var(shenv, tmp);
	ft_bzero(tmp, sizeof(tmp));
	ft_strcpy(tmp, "PWD=");
	if (!getcwd(cwd, MAX_PATH_NAME))
		return (ft_error(1, (char*[]){"cd: Unable to get CWD"}, -1));
	ft_strcpy(tmp + 4, cwd);
	ft_modify_var(shenv, tmp);
	return (0);
}


int32_t	ft_built_in_cd(char **argv, t_shenv *shenv)
{
	char				cwd[MAX_PATH_NAME];
	static t_string			curpath;
	char				flags;
	uint32_t			op;

	if (!curpath.string)
	{
		curpath.string = ft_strnew(MAX_PATH_NAME);
		curpath.capacity = MAX_PATH_NAME;
	}
	ft_bzero(curpath.string, MAX_PATH_NAME);
	curpath.len = 0;
	flags = ft_get_cd_flags(argv);
	op = 1 + (flags & 1) + ((flags >> 1) & 1);
	if (!getcwd(cwd, MAX_PATH_NAME) && !ft_get_pwd(&curpath, shenv))
		return (ft_error(1, (char*[]){"cd: Unable to get CWD or PWD"}, -1));
	if (!argv[1] && !get_home(&curpath, shenv))
		return (ft_error(1, (char*[]){"cd: HOME or path required"}, -1));
	else if (argv[op] && !ft_strcmp(argv[op], "-"))
		return (ft_cd_set_oldpath(shenv));
	else if (argv[op] && (*argv[op] == '/' || *argv[op] == '.'))
		ft_t_string_concat(&curpath, argv[op]);
	else
		ft_cdpath_search(&curpath, argv[op], shenv);
	if (!(flags & 2) && curpath.string[0] != '/')
		ft_create_path(&curpath, cwd, argv[op]);
	if (!convert_path(&curpath))
		return (ft_error(3, (char*[]){"cd: "
		, curpath.string, ": Invalid pathname"}, -1));
		if (curpath.len > MAX_PATH_NAME)
		return (ft_error(3, (char*[]){"cd: "
		, curpath.string, ": File name too long"}, -1));
		if (chdir(curpath.string) == -1)
		return (ft_error(3, (char*[]){"cd: "
		, argv[op], ": No such file or directory"}, -1));
		return (ft_cd_set_env(cwd, shenv));
}
