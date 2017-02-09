#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int		fd[2];
	char	*line;
	pid_t	pid;

	
	pipe(fd);
	pid = fork();
	line = NULL;
	if (pid > 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
		execve("/bin/cat", NULL, NULL);
		while (get_next_line(0, &line) > 0)
		{
			ft_putstr(line);
			ft_putendl("_______");
			free(line);
		}			
	}
	else
	{
		close(*fd);
		dup2(fd[1], 1);
		execve("./gnl", NULL, NULL);
	}
	return (0);
}
