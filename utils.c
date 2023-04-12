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
}
