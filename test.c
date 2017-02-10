#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int32_t	ft_is_escaped(char *line, uint32_t index)
{
	int32_t	ret;
	
	ret = 0;
	if (line)
	{
		while (index && *(line + index - 1) == '\\')
		{
			ret ^= 1;
			index--;
		}
	}
	else
		return (-1);
	return (ret);
}

int32_t	ft_is_unbalanced(char *line)
{
	int32_t		single_quotes;
	int32_t		double_quotes;
	uint32_t	i;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !ft_is_escaped(line, i) && !double_quotes)
			single_quotes ^= 1;
		else if (line[i] == '\"' && !ft_is_escaped(line, i) && !single_quotes)
			double_quotes ^= 2;
		i++;
	}
	return (single_quotes ^ double_quotes);
}

int main(int argc, char **argv)
{
/*	char	*line;
	char	*tmp;

	line = NULL;
	tmp = NULL;
	while (get_next_line(0, &line) > 0)
	{
		while (ft_is_unbalanced(line))
		{
			if (get_next_line(0, &tmp) > 0)
			{
				if (!(line = ft_strjoin_f(line, tmp, 0)))
					exit (EXIT_FAILURE);
			}
			free (tmp);
		}
		ft_putstr(line);
		ft_putstr("____is well balanced");
		free(line);
		}*/
# if 0
	uint32_t	i;

	i = 0;
	while (argv[1][i])
	{
		if (argv[1][i] == '*')
			break ;
		i++;
	}
	ft_putnbr(ft_is_escaped(argv[1], i));
#endif
	char	*line;
	int32_t	ret;
	char	*tmp_line;

	tmp_line = NULL;
	line = ft_strnew(0);
	while (get_next_line(0, &tmp_line) > 0)
	{
		line = ft_strjoin_f(line, tmp_line, 0);
		if ((ret = ft_is_unbalanced(line)) >= 2)
		{
			ft_putstr("dquote>");
			continue ;
		}
		else if (ret == 1)
		{
			ft_putstr("quote>");
			continue ;
		}
		else
			break ;
	}
	ft_putstr(line);
	free(line);
	return (0);
}
