#include "minishell.h"

#if 0
t_btree *ft_lexer(char *statement, char **env)
{
	
}
#endif
char	*ft_get_token(char *statement)
{
	uint32_t	i;
	char		*tmp;

	i = 0;
	while (statement[i])
	{
		if (ft_strchr(CHARSET_END_OF_EXPRESSION, statement[i]))
		{
			--i;
			break ;
		}
		i++;
	}
	if (!(tmp = ft_strsub(statement, 0, i)))
		exit (EXIT_FAILURE);
	return (tmp);
}

