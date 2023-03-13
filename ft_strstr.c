#include "pipex.h"

int	ft_strstr(char *str, char *find)
{
	int	i;
	int	j;
	int cp;

	i = 0;
	cp = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == find[0])
		{
			j = 0;
			while (find[j])
			{
				if (str[i] == find[j])
					cp++;
				j++;
				i++;
			}
			if (cp == j)
				return (i);
		}
		i++;
	}
	return (0);
}

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

int	find_path(t_pipe *p, char **env)
{
	int	i;


	i = 0;
	while (env[i])
	{
		printf("env : |%s| %d\n", env[i], i);
		if (ft_strstr(env[i], "PATH=") != 0)
		{
			p->found_path = i;
			// printf("path : |%s|\n", &env[i][5]);
			break ;
		}
		i++;
	}
	return (p->found_path);
}

void	init_value(t_pipe *p)
{
	p->found_path = -1;
	p->path = NULL;
}

void find_access_path(t_pipe *p, char *str)
{
	int	i;

	i = 0;
	// while (access())
}
void	create_pipe()
{

}
int main(int argc, char** argv, char **env)
{
	(void) argc;
	// (void) argv;
	t_pipe *p;
	char *cmd1[2];
	cmd1[0] = argv[2];
	cmd1[1] = 0;



	if (argc != 5)
		err_msg("Invalid argument");
	// init_value(p);
	// if (find_path(p, env) != 1)
	// 	find_access_path(p, &env[p->found_path][5])
	create_pipe();
	create_fork();
	execve("/bin/ls", cmd1, env);
	printf("-------------------------------------------------\n");
	// execve("/bin/cat", &argv[3], env);
	// if (found_path == 0)
	// 	perror()

}
