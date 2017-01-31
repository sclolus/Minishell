#include "minishell.h"
#include "libft.h"

/*char	*ft_find_command(char *filename, char **path, char **argv, char **env)
{
	char		*tmp;
	char		*tmp_2;

	tmp = NULL;
	tmp_2 = NULL;
	if (ft_buildin(filename, path, argv, env) != -1)
		return (NULL);
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		tmp_2 = tmp;
		tmp = ft_strjoin(tmp, filename);
		free(tmp_2);
		if (!(access(tmp, F_OK)))
		{
			if (!(access(tmp, X_OK)))
			{
				if (execve(tmp, argv, env))
					ft_putstr("error has occured");
				exit (EXIT_FAILURE);
			}
			else
			{
				ft_putstr_fd(SHELL_NAME, 2);
				ft_putstr_fd(tmp, 2);
				ft_putstr_fd(": Permission denied", 2);
				exit (-1);
			}
		}
		else
			path++;
		//might want to put permissions checking here
	}
	free (tmp);
	return (tmp); // wtf returning something
	}*/


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
