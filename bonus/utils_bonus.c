#include "../includes/pipex_bonus.h"

void	err_msg(t_cmd *p, char *msg)
{
	// int	i;

	// i = 0;
	// if (!msg)
	// 	return ;
	// while (msg[i] != '\0')
	// {
	// 	write(1, &msg[i], 1);
	// 	i++;
	// }
	ft_free_path(p);
	perror(msg);
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
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

void ft_free_path(t_cmd *p)
{
	int	i;

	i = 0;
	while(p->path[i])
	{
		free(p->path[i]);
		i++;
	}
	free(p->path);
}