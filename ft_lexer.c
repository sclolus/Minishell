#include "minishell.h"

#if 1
/*
int32_t	ft_count_sub_statements(char *statement)
{
	uint32_t	count;
	uint32_t	i;
	int8_t		bool;

	i = 0;
	count = 0;
	bool = 0;
	while (statement[i])
	{
		if (!ft_strchr(CHARSET_SPECIAL_DELIMITORS, statement[i]) && !bool)
		{
			bool = 1;
			count++;
		}
		else
			bool = 0;
		i++;
	}
	return (count);
}

int32_t	ft_count_delimitors(char *statement)
{
	uint32_t	count;
	uint32_t	i;

	i = 0;
	count = 0;
	while (statement[i])
	{
		if (ft_strchr(CHARSET_SPECIAL_DELIMITORS, statement[i]))
		{
			while (ft_strchr(CHARSET_SPECIAL_DELIMITORS, statement[i]))
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

int32_t	ft_is_statement_balanced(char *statement)
{
	char		*tmp;

	tmp = statement[i];
	statements[i] = ft_strtrim(statement[i]);
	free(tmp);
	
}

char	**ft_get_statements(char *command)
{
	
}
*/
char	*ft_get_token(char *str)
{
	uint32_t	i;
	char		*tmp;
	uint32_t	count;
	int8_t		bool;
	char		tmp_char;

	i = 0;
	count = 0;
	bool = 0;
	tmp_char = 0;
	tmp = NULL;
	if (ft_strchr(CHARSET_SPECIAL_DELIMITORS, str[i]))
	{
		while (str[i] == str[0])
			i++;
		if (!(tmp = ft_strsub(str, 0, i)))
			exit (EXIT_FAILURE);
		return (tmp);
	}
	while (str[i])
	{
		if (ft_strchr("\"\'", str[i]) && !bool)
		{
			bool = 1;
			tmp_char = str[i];
			count = 1;
		}
		else if (str[i] == tmp_char && count && str[i - 1] == '\\')
			count %= 2;
		if (!count && ft_strchr(CHARSET_SPECIAL_DELIMITORS, str[i]))
			break ;
		i++;
	}
	tmp = ft_strsub(str, 0, i);
	if (!(tmp))
		exit (EXIT_FAILURE);
	return (tmp);
}

char	 **ft_lexer(char *command_line, char **env)
{
	char		**tokens;
	char		*tmp;
	t_list		*new;
	t_list		*lst;
	uint32_t	i;
	uint32_t	count;

	i = 0;
	count = 0;
	lst = NULL;
	tmp = NULL;
	tokens = NULL;
	while (command_line[i])
	{
		while (command_line[i]
			   && ft_strchr(" \t\n", command_line[i]))
			   i++;
		tmp = ft_get_token(command_line + i);
		i += ft_strlen(tmp);
		if (!(new = ft_lstnew(NULL, 0)))
			exit(EXIT_FAILURE);
		ft_lstadd(&lst, new);
		lst->content = tmp;
		count++;
	}
	if (!(tokens = (char**)malloc(sizeof(char*) * count + 1)))
		exit (EXIT_FAILURE);
	tokens[count] = NULL;
	while (lst)
	{
		tokens[count - 1] = lst->content;
		count--;
		lst = lst->next;
	}
	tokens = ft_preparse(tokens, env);
/*	while (*tokens)
	{
		ft_putendl(*tokens);
		ft_putchar('|');
		tokens++;
		}*/
	return (tokens);
}
#endif
