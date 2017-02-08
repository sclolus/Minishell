#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int		fd;
	int		stdin;
	char	*line;
	pid_t	pid;

	fd = open("test.txt", O_RDONLY);
//	pipe(fd);
	close(0);
	stdin = dup(fd);
	ft_putnbr(stdin);
	while (get_next_line(stdin, &line) > 0)
	{
		ft_putendl(line);
		free (line);
	}
/*		pid = fork();

	if (pid > 0)
	{
		//	close(fd[1]);
		while (1)
		{
			get_next_line(fd[0], &line);
			ft_putstr(line);
		}
	}
	else
	{
//		close(fd[0]);
		while (1)
		{
			ft_putstr_fd("salut\n", fd[0]);
		}
		}*/
	return (0);
}
