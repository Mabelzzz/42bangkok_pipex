#include "pipex.h"

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
	{
		p->cur_path = cmd;
		return(access(cmd, F_OK));
	}
	else
	{
		i = -1;
		while (p->path[++i])
		{
			p->cur_path = ft_strjoin(p->path[i], cmd);
			if (access(p->cur_path, F_OK) == 0)
				return (0);
			free(p->cur_path);
			i++;
		}
	}
	return (-1);
	// while (access())
}
void	create_pipe(char **argv, t_cmd *p)
{
	int	i;

	i = 0;
		//sth error
	while (i < p->ac - 4)
	{
		if(pipe(p->pfd[i]) == -1)
		{
			err_msg("cant creating pipe\n");
			// close_px();
			//sth error
		}
		printf("creating pipe\n");
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
		dup2(p->pfd[i - 1][0], 0);

	if (i == p->ac - 4)
	{
		p->fd_outfile = open(argv[i - 4], O_RDONLY);
		dup2(p->fd_outfile, 1);
		close(p->fd_outfile);
	}
	else
	{
		dup2(p->pfd[i + 1][1], 1);
		// close()
	}

	// execve(p->path, p->cmd, env);

}

void	create_fork(char** argv, t_cmd *p)
{
	int	i;

	i = 0;
	while (i < p->ac - 3)
	{
		p->pid[i] = fork();
		if(p->pid[i] == -1)
		{
			err_msg("cant creating fork\n");
			//sth error
		}
		else
		{
			if (check_access_path(p, argv[i + 1]) == -1)
				err_msg("error, invalid path\n");
				//sth error
			else
			{
				p->cmd = ft_split(argv[i + 2], ' ');
				if(p->pid[i] == 0)
				{
					printf("Child process\n");
					child_process(p, argv, i);

				}
				else
				{
					//parent process
					printf("Paraent process\n");
				}
			}
		}
		i++;
	}
}

int main(int argc, char** argv, char **env)
{
	t_cmd 	*p;

	if (argc != 5)
		err_msg("Invalid argument");

	*p->pfd = malloc(sizeof(int *) * (argc - 4));
	p->pid = malloc(sizeof(int) * (argc - 3));
	p->ac = argc;
	init_value(p);
	if (find_path(p, env) != 1)
		p->path = ft_split(&env[p->found_path][5], ':');

	int i = -1;
	while (p->path[++i])
		printf("path %d = |%s|\n", i, p->path[i]);
	printf("path %d = |%s|\n", 9, p->path[9]);
	// 	find_access_path(p, &env[p->found_path][5])
	create_pipe(argv, p);
	// create_fork(argv, p);

	// char *cmd1[2];
	//cmd1 = ft_split(argv[2])
	// cmd1[0] = 'ls';
	// cmd1[1] = '-la';
	// cmd1[2] = 0;
	// execve("/bin/ls", cmd1, env);
	printf("-------------------------------------------------\n");
	// execve("/bin/cat", &argv[3], env);


	// if (found_path == 0)
	// 	perror()

}
