#include "minishell.h"

static uint32_t		set_flags(char **argv)
{
	uint32_t	i;
	uint32_t	flags;

	i = 0;
	flags = 0;
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "-L"))
			flags ^= 1;
		else if (!ft_strcmp(argv[i], "-P"))
			flags ^= 2;
		else
			return (flags);
		++i:
	}
	return (flags);
}

static char		cdpath_search(char *curpath, char *op, t_env *env)
{

}

static int32_t	get_home(char *curpath, t_env *env)
{

}

static int32_t	create_path(char *dst, char *path, char *op)
{
	uint32_t	i;

	i = 0;
	while (op[i])
	{


	}
}

int32_t	ft_cd(char **argv, t_env *env)
{
	char		cwd[MAX_PATH_NAME];
	char		curpath[MAX_PATH_NAME];
	uint32_t	flags;
	uint32_t	op;

	//flags
	// 1 > -L
	// 2 > -P
	// 3 > relative

	ft_bzero(curpath, MAX_PATH_NAME);
	flags = set_flags(argv);
	op = 1 + (flags & 1) + ((flags>>1) & 1);
	if (argv[1] && ft_strlen(argv[op]) + 1 > MAX_PATH_NAME)
		return (ft_error(3, (char*[]){"cd: ", argv[op], ": File name too long"}, -1));
	if (!getcwd(cwd, 4096))
		return (ft_error(1, (char*[]){"cd: Unable to get current working directory"}, -1));
	if (!argv[1] && !get_home(curpath, env))
		return (ft_error(1, (char*[]){"cd: ENV or path required"}, -1));
	else if (*argv[op] == '/')
		ft_strcpy(curpath, argv[op]);
	else if (*argv[op] == '.')
		;
	else
		cdpath_search(curpath, argv[op], env));
	if (!(flags & 2) && curpath[0] != '/' && !create_path(curpath, cwd, argv[op]))
		return (ft_error(1, (char*[]){"cd: Full path too long"}, -1));
	if (chdir(curpath) == -1)
		return(ft_error(1, (char*[]){"cd: chdir failed"}, -1));
	//Set oldpwd to cwd
	//Set pwd to getcwd
	return (0);
}
