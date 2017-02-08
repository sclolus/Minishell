#include "minishell.h"
#include "libft.h"

char	*ft_find_command(char *filename, char **path)
{
	static char oldpwd[MAX_PATH];
	uint32_t	i;

	i = 0;
	getcwd(oldpwd, MAX_PATH); // not protected;
	while (path[i])
	{
		if (chdir(path[i]) == -1)
		{
			ft_putendl_fd("chdir() failed", 2);
			exit(EXIT_FAILURE); // not necessary
		}
		if (!(access(filename, F_OK)))
		{
			if (!(access(filename, X_OK)))
			{
				if (chdir(oldpwd) == -1)
					ft_putendl_fd("chdir() failed", 2);
				return (path[i]);
			}
			else
			{
				ft_putstr_fd(SHELL_NAME, 2);
				ft_putstr_fd(filename, 2);
				ft_putstr_fd(": Permission denied", 2);
				if (chdir(oldpwd) == -1)
					ft_putendl_fd("chdir() failed", 2);
				return (NULL);
			}
		}
		else
			i++;
	}
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(filename, 2);
	if (chdir(oldpwd) == -1)
		ft_putendl_fd("chdir() failed", 2);
	return (NULL);
}

char		**ft_parse_line(char *line)
{
	static uint32_t		offset = 0;
	static char			*memorizer = 0;
	static char			**command_list = 0;
	char				**tmp;

	tmp = NULL;
	if (line != memorizer)
	{
		offset = 0;
		memorizer = line;
		if (!(command_list = ft_strsplit(line, ';')))
			exit (EXIT_FAILURE);
	}
	if (command_list[offset] == NULL)
		return (NULL);
	if (!(tmp = ft_strsplit(command_list[offset++], ' ')))
		exit (EXIT_FAILURE);
	ft_normalize_command(tmp);
	return (tmp);
}

void		ft_normalize_command(char **command)
{
	uint32_t	i;

	i = 1;
	while (command[i])
	{
		command[i] = ft_parse_arg(command[i]);
		i++;
	}
}

char		*ft_parse_arg(char *line)
{
	char		*tmp;
	uint32_t	i;
	uint32_t	u;
	char		string_char;

	// matching not supported
	string_char = -1;
	i = 0;
	u = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"' ) // not recognized?|| line[i] == '\`')
		{
			string_char = line[i];
			break ;
		}
		i++;
	}
	i = 0;
	if (string_char == -1)
		return (line);
	else
	{
		if (!(tmp = (char*)ft_strnew(ft_strlen(line))))
			exit (EXIT_FAILURE);
		while (line[i])
		{
			if (line[i] != string_char)
				tmp[u++] = line[i];
			i++;
		}
	}
	free(line);
	return (tmp);
}
