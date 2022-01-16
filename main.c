#include <unistd.h>
#include <stdio.h>
#include "minipaint.h"


int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	write (fd, str, ft_strlen(str));
}

int main(int ac, char **av)
{
	char *pathname;
	FILE *fd;

	if (ac != 2)
	{
		ft_putstr_fd(ERROR_ARGS, 1);
		return (0);
	}
	pathname = av[1];
	fd = fopen(pathname, "r");
	if (fd == NULL)
		ft_putstr_fd(ERROR_FD, 1);
		
		
}
