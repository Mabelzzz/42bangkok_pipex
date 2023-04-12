#include "pipex.h"

// int	get_path(t_cmd *p, char **env)
// {
// 	int	i;


// 	i = 0;
// 	while (env[i])
// 	{
// 		printf("env : |%s| %d\n", env[i], i);
// 		if (ft_strstr(env[i], "PATH="))
// 		{
// 			p->path = ft_split(&env[i][5], ':');
// 			return (0);
// 			// printf("path : |%s|\n", &env[i][5]);
// 			// break ;
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// void	init_value(t_cmd *p)
// {
// 	p->found_path = -1;
// 	p->path = NULL;
// }

// int check_access_path(t_cmd *p, char *cmd)
// {
// 	int	i;

// 	if (cmd[0] != '/')
// 	{
// 		i = -1;
// 		while (p->path[++i])
// 		{
// 			p->cur_path = ft_strjoin(p->path[i], cmd);
// 			if (access(p->cur_path, F_OK) == 0)
// 				return (0);
// 			free(p->cur_path);
// 			i++;
// 		}
// 	}
// 	return(access(cmd, F_OK));
// 	// while (access())
// }
// void close_pipe(t_cmd *p)
// {
// 	int i;

// 	i = 0;
// 	while (i < p->ac - 4)
// 	{
// 		close(p->fd_pipe[i][0]);
// 		close(p->fd_pipe[i][1]);
// 		i++;
// 	}
// }
// void	create_pipe(char **argv, t_cmd *p)
// {
// 	int	i;

// 	p->fd_pipe = malloc(sizeof(int *) * (p->ac - 4));
// 	i = -1;
// 	while (++i < p->ac - 4)
// 		p->fd_pipe[i] = malloc(sizeof(int) * 2);
// 	if (!p->fd_pipe)
// 		err_msg("can not malloc, then free");
// 	i = 0;
// 	while (i < p->ac - 4)
// 	{
// 		if(pipe(p->fd_pipe[i]) == -1)
// 		{
// 			err_msg("cant creating pipe\n");
// 			i = -1;
// 			while (p->fd_pipe[++i])
// 				free(p->fd_pipe[i]);
// 			free(p->fd_pipe);
// 			// close_px();
// 			//sth error
// 		}
// 		printf("creating pipe\n");
// 		i++;
// 	}
// }
// void	child_process(t_cmd *p, char** argv, int i)
// {
// 	if (i == 0)
// 	{
// 		p->fd_infile = open(argv[1], O_RDONLY);
// 		dup2(p->fd_infile, 0);
// 		close(p->fd_infile);
// 	}
// 	else
// 		dup2(p->fd_pipe[i - 1][0], 0);

// 	if (i == p->ac - 4)
// 	{
// 		p->fd_outfile = open(argv[i - 4], O_RDONLY);
// 		dup2(p->fd_outfile, 1);
// 		close(p->fd_outfile);
// 	}
// 	else
// 	{
// 		dup2(p->fd_pipe[i + 1][1], 1);
// 		// close()
// 	}

// 	// execve(p->path, p->cmd, env);

// }
// void	forking(char** argv, t_cmd *p, int i)
// {
// 	int	a;
// 	p->pid[i] = 4;
// 	printf("%d try fork %d\n", i, p->pid[i]);

// 	a = fork();
// 	printf("a = %d\n", a);
// 	exit(0);
// 	// p->pid[i] = fork();
// 	printf("%d first fork %d\n", i, p->pid[i]);
// 	if (p->pid[i] == -1)
// 	{
// 		err_msg("cant creating fork\n");
// 		printf("%d fork fail %d\n", i, p->pid[i]);
// 		//sth error
// 	}
// 	if (p->pid[i] == 0)
// 	{
// 		printf("%d Child process %d\n", i, p->pid[i]);
// 		// child_process(p, argv, i);

// 	}
// 	if(p->pid[i] != 0 && p->pid[i] != -1)
// 	{
// 		//parent process
// 		printf("%d Paraent process %d\n", i, p->pid[i]);
// 	}
// }

// void	create_fork(char** argv, t_cmd *p)
// {
// 	int	i;

// 	p->pid = malloc(sizeof(int) * (p->ac - 3));
// 	if (!p->pid)
// 	{
// 		err_msg("can not malloc process id");
// 		//error + do not forgot to free
// 	}
// 	else
// 		err_msg("success\n");
// 	i = 0;
// 	while (i < p->ac - 3)
// 	{
// 		forking(argv, p, i);
// 		i++;
// 	}
// }

// int main(int argc, char** argv, char **env)
// {
// 	t_cmd 	*p;

// 	if (argc != 5)
// 		err_msg("Invalid argument");

// 	p->ac = argc;
// 	init_value(p);

// 	if (get_path(p, env))
// 		err_msg("can not find path");


// 	p->cmd = malloc(sizeof(char **) * (argc - 2));
// 	if (!p->cmd)
// 	{
// 		printf("hello\n");
// 		return 0;
// 	}
// 	// p->cmd[0] = NULL;
// 	// p->cmd = NULL;
// 	pid_t a = fork();
// 	printf("hello\n");
// 	printf("pid = %d\n", a);
// 	printf("hello\n");
// 	exit(0);
// 	int i = 0;
// 	while (i < argc - 3)
// 	{
// 		p->cmd[i] = ft_split(argv[i + 2], ' ');
// 		if (check_access_path(p, p->cmd[i][0]))
// 			err_msg("error path, can not acces\n");
// 		// while (cm)
// 		printf("cmd0 %d = |%s|\n", i, p->cmd[i][0]);
// 		printf("cmd1 %d = |%s|\n", i, p->cmd[i][1]);
// 		// printf("cmd2 %d = |%s|\n", i, p->cmd[i][2]);
// 		i++;
// 	}
// 	int j = -1;
// 	while(p->path[++j])
// 	{
// 		printf("path %d = |%s|\n", j, p->path[j]);
// 	}

// 	// 	find_access_path(p, &env[p->found_path][5])
// 	create_pipe(argv, p);
// 	create_fork(argv, p);

// 	// char *cmd1[2];
// 	//cmd1 = ft_split(argv[2])
// 	// cmd1[0] = 'ls';
// 	// cmd1[1] = '-la';
// 	// cmd1[2] = 0;
// 	// execve("/bin/ls", cmd1, env);
// 	printf("-------------------------------------------------\n");
// 	// execve("/bin/cat", &argv[3], env);


// 	// if (found_path == 0)
// 	// 	perror()

// }

int main(void)
{
	char *hello = (char *)malloc(sizeof(char) * 5);
	int	fd[2];
	// int i = 5;
	for (int i = 0; i < 4; i++)
		pipe(fd);
	int pid[5];
	for (int i = 0; i < 5; i++)
	{
		// pid[i] = fork();
		if (i == 0)
		{
			pid[i] = fork();
		}
		if (pid[i - 1] != 0 && pid[i - 1] != -1 && i != 0)
			pid[i] = fork();
		printf("pid[%d] -> %d\n", i, pid[i]);
	}
	// for (int i = 0; i < 5; i++)
	return (0);
}
