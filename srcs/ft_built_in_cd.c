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
			break;
		else if (argv[i][0] == '-')
		{
			ret = ft_set_flags(argv[i]);;
			if (ret == -1)
				return (-1);
			flags |= ret;
		}
		else
			break;
		i++;
	}
	return (flags);
}
//
// static int32_t	check_path(char *path, char *end, char *op)
// {
// 	DIR				*dir;
// 	size_t			len;
// 	char 			full_path[MAX_PATH_NAME];
//
// 	if ((len = (end) ? end - path : ft_strlen(path)) > MAX_PATH_NAME)
// 		return (0);
// 	ft_memcpy(full_path, path, len);
// 	if (path[len - 1] != '/')
// 		full_path[len++ - 1] = '/';
// 	if (len + ft_strlen(op) > MAX_PATH_NAME)
// 		return (0);
// 	ft_strcpy(full_path + len, op);
// 	if (!(dir = opendir(full_path)))
// 		return (0);
// 	closedir(dir);
// 	return (1);
// }

static char		cdpath_search(t_string *curpath, char *op, t_shenv *shenv)
{
	char	**cdpath;
	char	*path;
	char	*end;
	size_t	len;
	DIR		*dir;

	if (!(cdpath = ft_find_var(shenv, "CDPATH")))
		return (0);
	path = ft_strchr(*cdpath, '=') + 1;
	while (path && *path)
	{
		end = ft_strchr(path, ':');
		len = end ? end - path : ft_strlen(path);
		if (!len)
		{
			ft_t_string_concat(curpath, "./");
			len = 2;
		}
		else
			ft_memcpy(curpath->string, path, len);
		curpath->string[len] = (curpath->string[len - 1] == '/') ? '\0' : '/';
		ft_t_string_concat(curpath, op);
		if ((dir = opendir(curpath->string)))
		{
                  closedir(dir);
                  return (1);
		}
		ft_bzero(curpath->string, MAX_PATH_NAME);
		curpath->len = 0;
		curpath->offset = 0;
		path = (end) ? end + 1 : NULL;
	}
	return (0);
}

static int32_t	get_home(t_string *curpath, t_shenv *shenv)
{
	char **home;

	if (!(home = ft_find_var(shenv, "HOME")))
		return (0);
	ft_t_string_concat(curpath, *home + 5);
	return (1);
}

static int32_t	create_path(t_string *dst, char *path, char *op)
{
	uint64_t	is_data;

	is_data = dst->len;
	dst->offset = 0;
	ft_t_string_insert(dst, path);
	if (path[ft_strlen(path) - 1] != '/')
		ft_t_string_insert(dst, "/");
	if (!is_data)
		ft_t_string_concat(dst, op);
	return (1);
}

/*************************************************************************/
/* static void	trim(t_string *path)                                     */
/* {                                                                     */
/*   if (path->string[ft_strlen(path->string) - 1] == '.')               */
/*     {                                                                 */
/*       while (path->string[ft_strlen(path->string) - 1] != '/')        */
/*         path->string[ft_strlen(path->string) - 1] = '\0';             */
/*     }                                                                 */
/* }                                                                     */
/*************************************************************************/

static int32_t	convert_path(t_string *path)
{
	int64_t	i;


        //todo trucate /. & /..
        //todo convert /// to /
	i = 2;

        if (path->string[ft_strlen(path->string) - 1] != '/')
          ft_t_string_concat(path, "/");
	path->offset = 0;
	while (path->string[path->offset])
	{
		if (!ft_strncmp(path->string + path->offset, "./", 2))
		{
			ft_strcpy(path->string + path->offset, path->string + path->offset + 2);
			path->len -= 2;
			continue;
		}
		else if (!ft_strncmp(path->string + path->offset, "../", 3))
		{
			while (path->offset > i && path->string[path->offset - i] != '/')
				i++;
			if (path->offset < i)
				return (0);
			ft_strcpy(path->string + path->offset - i, path->string + path->offset + 2);
			path->len -= i + 2;
			path->offset -= i;
			i = 2;
			continue;
		}
                else if (!ft_strncmp(path->string + path->offset, "///", 3))
                {
                    	ft_strcpy(path->string + path->offset, path->string + path->offset + 2);
			path->len -= 2;
                        continue;
                }
                path->offset++;
	}
        /* trim(path); */
	return (1);
}

static int32_t	set_env(char *cwd, t_shenv *shenv)
{
        char		tmp[MAX_PATH_NAME + 10];
        
        ft_strcpy(tmp, "OLDPWD=");
        ft_strcpy(tmp + 7, cwd);
        ft_modify_var(shenv, tmp);
        ft_bzero(tmp, sizeof(tmp));
        ft_strcpy(tmp, "PWD=");
       	if (!getcwd(cwd, MAX_PATH_NAME))
		return (ft_error(1, (char*[]){"cd: Unable to get current working directory"}, -1));
        ft_strcpy(tmp + 4, cwd);
        ft_modify_var(shenv, tmp);
        return (0);
}

int32_t	ft_built_in_cd(char **argv, t_shenv *shenv)
{
	char				cwd[MAX_PATH_NAME];
	static t_string		curpath;
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
	op = 1 + (flags & 1) + ((flags>>1) & 1);
        if (!getcwd(cwd, MAX_PATH_NAME))
		return (ft_error(1, (char*[]){"cd: Unable to get current working directory"}, -1));
	if (!argv[1] && !get_home(&curpath, shenv))
		return (ft_error(1, (char*[]){"cd: ENV or path required"}, -1));
	else if (argv[op] && (*argv[op] == '/' || *argv[op] == '.'))
		ft_t_string_concat(&curpath, argv[op]);
	else
		cdpath_search(&curpath, argv[op], shenv);
	if (!(flags & 2) && curpath.string[0] != '/')
		create_path(&curpath, cwd, argv[op]);
	if (!convert_path(&curpath))
		return (ft_error(3, (char*[]){"cd: ", curpath.string, ": Invalid pathname"}, -1));
	if (curpath.len > MAX_PATH_NAME)
		return (ft_error(3, (char*[]){"cd: ", curpath.string, ": File name too long"}, -1));
	if (chdir(curpath.string) == -1)
            return(ft_error(3, (char*[]){"cd: ", argv[op], ": No such file or directory"}, -1));
        return (set_env(cwd, shenv));
}
