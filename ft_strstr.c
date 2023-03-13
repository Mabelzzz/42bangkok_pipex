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

int	find_path(t_cmd *p, char **env)
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

void	init_value(t_cmd *p)
{
	p->found_path = -1;
	p->path = NULL;
}

int check_access_path(t_cmd *p, char *cmd)
{
	int	i;

	if (cmd[0] == '/')
		return(access(cmd, F_OK));
	else
	{
		i = -1;
		while (p->path[++i])
		{
			if (access(ft_strjoin(p->path[i], cmd), F_OK) == 0)
				return (0);
			i++;
		}
	}
	return (-1);
	// while (access())
}
void	create_pipe(int argc, t_cmd *p)
{
	int	i;

	i = 0;
	while (i < argc - 4)
	{
		if(pipe(p[i].pipe->pfd) == -1)
		{
			err_msg("cant creating pipe\n");
			//sth error
		}
		i++;
	}
}
void	child_process(t_cmd *p, char** argv, int i)
{
	if (i == 0)
	{
		p->fd_infile = open(argv[1], O_RDONLY);
		dup2(p->fd_infile, 0);
		close(p->fd_infile);
	}
	else
		dup2(p[i - 1].pipe->pfd[0], 0);

	if (i == p->ac - 4)
	{
		p->fd_outfile = open(argv[i - 4], O_RDONLY);
		dup2(p->fd_outfile, 1);
		close(p->fd_outfile);
	}
	else
	{
		dup2(p[i + 1].pipe->pfd[1], 1);
	}


}

void	create_fork(char** argv, t_cmd *p)
{
	int	i;

	i = 0;

	while (i < p->ac - 3)
	{
		p[i].pipe->pid[i] = fork();
		if(p[i].pipe->pid[i] == -1)
		{
			err_msg("cant creating fork\n");
			//sth error
		}
		else if(p[i].pipe->pid[i] == 0)
		{
			if (check_access_path(p, argv[i + 1]) == -1)
				err_msg("error, invalid path\n");
				//sth error
			else
			{
				
				child_process(p, argv, i);
			}
		}
		else
		{
			//parent process
			printf("Paraent process\n");
		}
		i++;
	}
}
int main(int argc, char** argv, char **env)
{
	(void) argc;
	// (void) argv;
	t_cmd 	*p;

	// char *cmd1[2];
	// cmd1[0] = argv[2];
	// cmd1[1] = 0;

	if (argc != 5)
		err_msg("Invalid argument");
	p = malloc(sizeof(t_cmd) * (argc - 4));
	p->ac = argc;
	init_value(p);
	if (find_path(p, env) != 1)
		p->path = ft_split(&env[p->found_path][5], ':');
	int i = -1;
	while (p->path[++i])
		printf("path %d = |%s|\n", i, p->path[i]);
	// 	find_access_path(p, &env[p->found_path][5])
	// create_pipe(argc, p);
	// create_fork(argc, argv, p);
	// execve("/bin/ls", cmd1, env);
	printf("-------------------------------------------------\n");
	// execve("/bin/cat", &argv[3], env);
	// if (found_path == 0)
	// 	perror()

}
