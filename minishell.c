#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"

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

	path = NULL;
	tmp = NULL;
	variable_len = ft_strlen(variable);
	if (!(path = ft_strsplit(ft_find_env((char const**)env, variable), ':')))
		exit (EXIT_FAILURE);
	if (!(tmp = ft_strdup(*path)))
		exit(EXIT_FAILURE);
	len = ft_strlen(tmp) - variable_len - 1; 
	ft_strncpy(*path, tmp + variable_len + 1, len + 1);
	return (path);
}

int main(int argc, char **argv, char **env)
{
	char		*line;
	char		**command_argv;
	char		**path;
	char		*tmp;
	t_list		*env_lst;
	char		**env_tab;
	pid_t		pid;

	line = NULL;
	if (argc || argv)
	{};
	path = ft_get_env_value(env, "PATH");
	ft_putstr("$>");
	if (signal(SIGINT, &ft_sighandler))
		ft_putstr("salut");
	if (!(env_lst = ft_get_lstenv(env)))
		exit (EXIT_FAILURE);
	while (line || (get_next_line(0, &line) >= 0))
	{
		if (*line == 0)
		{
			ft_strdel(&line);
			continue ;
		}
		if (!(env_tab = ft_lsttotab(env_lst, sizeof(t_list))))
			exit (EXIT_FAILURE);
		ft_lexer(line, env_tab);
		if ((command_argv = ft_parse_line(line)) == NULL)
		{
			line = NULL;
			continue ;
		}
		if (ft_buildin(*command_argv, command_argv, env_tab, &env_lst) == -2) // buf inc.
		{
			pid = fork();
			if (pid > 0)
			{
				wait(NULL);
				ft_putstr("$>");
			}
			else
			{
				if (!(tmp = ft_find_command(*command_argv, path)))
					exit (EXIT_FAILURE);
				if (ft_execve(*command_argv, tmp
							  , command_argv, env_tab) == -1)
					ft_putendl_fd("ft_execve() failed", 2);
				return (EXIT_FAILURE);
			}
		}
		free(env_tab);
//		ft_putstr("$>");
	}
	return (0);
}
