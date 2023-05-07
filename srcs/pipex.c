#include "../includes/pipex.h"

int	find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strstr(env[i], "PATH=") == 0)
		{
			return (i);
			exit(0);
		}
		i++;
	}
	return (-1);
}

void	init_value(t_cmd *p)
{
	p->found_path = -1;
	p->path = NULL;
}

int check_access_path(t_cmd *p, char *cmd)
{
	size_t	i;
	
	if (ft_find_slash(cmd) == 0 || cmd[0] == '.')
	{
		p->cur_path = ft_strdup(cmd);
		return(access(cmd, F_OK & X_OK));
	}
	else
	{
		i = 0;
		while (p->path[i])
		{
			// printf("i = %zu\n", i);
			p->cur_path = ft_strjoin(p->path[i], cmd);
			if (access(p->cur_path, F_OK & X_OK) == 0)
			{
				// printf("acc = %d\n", access(p->cur_path, F_OK & X_OK));
				return (0);
			}
			free(p->cur_path);
			i++;
		}
	}
	// printf("last i = %zu\n", i);
	return (-1);
}

void	child_process1(t_cmd *p, char **env, char** argv)
{
	int fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	if (check_access_path(p, p->cmd1[0]) != 0)
		err_msg(p, "Can not access path\n");
	dprintf(2, "acess = %d | cur path1 = %s \n", access(p->cur_path, F_OK & X_OK), p->cur_path);
	dup2(fd_infile, 0);
	dup2(p->pfd[1], 1);
	close(fd_infile);
	close(p->pfd[0]);
	close(p->pfd[1]);
	// dprintf(2, "acess = %d | cur path1 = %s | exv = %d\n", access(p->cmd1[0], F_OK & X_OK), p->cur_path, execve(p->cur_path, p->cmd1, env));
	if (execve(p->cur_path, p->cmd1, env) == -1)
		err_msg(p, "fail child1\n");
}

void	child_process2(t_cmd *p, char **env, char** argv)
{
	int fd_outfile;

	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// free(p->cur_path);
	if (check_access_path(p, p->cmd2[0]) != 0)
		err_msg(p, "Can not access path");
	dprintf(2, "acess = %d | cur path2 = %s \n", access(p->cur_path, F_OK & X_OK), p->cur_path);
	dup2(p->pfd[0], 0);
	dup2(fd_outfile, 1);
	close(fd_outfile);
	close(p->pfd[0]);
	close(p->pfd[1]);
	if (execve(p->cur_path, p->cmd2, env) == -1)
		err_msg(p, "fail child2\n");
	else
		exit(0);
}


int main(int argc, char** argv, char **env)
{
	t_cmd 	p;

	if (argc != 5)
		err_msg(&p, "Invalid argument");
	p.found_path = find_path(env);
	if (p.found_path != -1)
		p.path = ft_split(&env[p.found_path][5], ':');
	if(pipe(p.pfd) == -1)
		err_msg(&p, "Can not create pipe");
	p.cmd1 = ft_split(argv[2], ' ');
	p.cmd2 = ft_split(argv[3], ' ');
	// printf("cmd2 0: %s exv = %d\n", p.cmd1[0], execve("/usr/bin/tail", p.cmd1, env));
	// printf("cmd2 0: %s exv = %d\n", p.cmd2[0], execve("/usr/bin/tail", p.cmd2, env));
	// exit(0);
	// printf("cmd1 1: %s \n", p.cmd1[1]);
	// printf("cmd2 0: %s \n", p.cmd2[0]);
	p.pid[0] = fork();
	if (p.pid[0] == -1)
		err_msg(&p, "Can not create fork");
	if (p.pid[0] == 0)
		child_process1(&p, env, argv);
	p.pid[1] = fork();
	if (p.pid[1] == 0 && p.pid[0] != 0)
		child_process2(&p, env, argv);
	if ((p.pid[0] > 0 || p.pid[1] > 0) && p.cur_path)
		free(p.cur_path);
	close(p.pfd[0]);
	close(p.pfd[1]);
	waitpid(p.pid[0], NULL, 0);
	waitpid(p.pid[1], &p.status, 0);
	return (WEXITSTATUS(p.status));
}
