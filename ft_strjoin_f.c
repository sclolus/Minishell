#include "minishell.h"

char	*ft_strjoin_f(char *a, char *b, int32_t mode)
{
	char	*str;
	size_t	len;
	size_t	s1_len;

	if (!a || !b)
		return (0);
	s1_len = ft_strlen(a);
	len = s1_len + ft_strlen(b);
	if (!(str = ft_strnew(len)))
		return (0);
	ft_strcpy(str, a);
	ft_strcpy(str + s1_len, b);
	if (mode == 0)
		free(a);
	else if (mode == 1)
		free(a);
	else
	{
		free(a);
		free(b);
	}
	return (str);
}
