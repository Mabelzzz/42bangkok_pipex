#include "../includes/pipex_bonus.h"
#include "../gnl/get_next_line.h"

void	err_file(t_cmd *p, char *file, int err)
{
	ft_free_path(p);
	// perror("pipex: No such file or directory: ");
	write(STDERR_FILENO, "pipex: ", 8);
	write(STDERR_FILENO, file, ft_strlen(file));
	if (err == 1)
		write(STDERR_FILENO, ": No such file or directory\n", 29);
	else if (err == 2)
		write(STDERR_FILENO, ": Permission denied\n", 21);
	else if (err == 3)
		write(STDERR_FILENO, ": command not found\n", 21);
	exit(EXIT_FAILURE);
}

void	err_msg(t_cmd *p, char *msg)
{
	ft_free_path(p);
	perror(msg);
	write(STDERR_FILENO, "\n", 1);
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

	if (!p->path)
		return ;
	i = 0;
	while(p->path[i])
	{
		free(p->path[i]);
		i++;
	}
	free(p->path);
}
