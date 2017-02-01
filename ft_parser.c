#include "minishell.h"

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
	ft_putstr_fd(filename, 2);
	ft_putendl_fd(" : Could not be found", 2);
	if (chdir(oldpwd) == -1)
		ft_putendl_fd("chdir() failed", 2);
	return (NULL);
}

char		*ft_variable_expansion(char *token, char **env)
{
	uint32_t	i;
	uint32_t	u;
	char		*tmp;
	char		*cpy;

	i = 0;
	u = 0;
	while (token[i])
	{
		if (token[i] == '$' && token[i + 1] != '(')
		{
			u = i;
			while (token[i] && (!ft_strchr(CHARSET_SPECIAL_DELIMITORS, token[i]) || !ft_strchr(" \t\n", token[i])))
				i++;
			if (!(tmp = ft_strsub(token, u + 1, i - u - 1)))
				exit(EXIT_FAILURE);
			cpy = ft_find_env((char const**)env, (char const*)tmp);
			free(tmp);
			while (*cpy && *cpy != '=')
				cpy++;
			tmp = token;
			if (!(token = ft_strreplace(token, u, i - 1, cpy + 1)))
				exit(EXIT_FAILURE);
			free(tmp);
			i = 0;
		}
		i++;
	}
	return (token);
}

char		**ft_preparse(char **tokens, char **env)
{
	uint32_t	i;

	i = 0;
	while (tokens[i])
	{
		tokens[i] = ft_variable_expansion(tokens[i], env);
		// put command expansion in it
		i++;
	}
	return (tokens);
}
