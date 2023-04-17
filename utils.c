#include "pipex.h"

void	err_msg(char *msg)
{
	int	i;

	i = 0;
	if (!msg)
		return ;
	while (msg[i] != '\0')
	{
		write(1, &msg[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int ft_find_slash(char *str)
{
	if (*str == '/')
		return (0);
	while (*str++ != '\0')
	{
		if (*str == '/')
			return (0);
	}
	return (-1);
}