#include "../includes/pipex_bonus.h"
#include "../gnl/get_next_line.h"

int		find_path(char **env);
int 	check_access_path(t_cmd *p, char *cmd);
void 	get_access_path(t_cmd *p, char *cmd);
void	child_process(t_cmd *p, char** argv,  char **env, int id);
void	parent_process(t_cmd *p);
void	read_heredoc(t_cmd *p, char** argv);
int		check_all_access(t_cmd *p, char** argv);
void	init_value(t_cmd *p, int argc);
void	prep_cmd(t_cmd *p, char *argv);
void	ft_dup2(t_cmd *p, char **argv, int id);
void	create_process(t_cmd *p, char **argv, char **env);

int	find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strstr(env[i], "PATH=") == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

// void	init_value(t_cmd *p)
// {
// 	p->found_path = -1;
// 	p->path = NULL;
// }

int check_access_path(t_cmd *p, char *cmd)
{
	size_t	i;
	printf("cmd = %s\n", cmd);
	if (ft_find_slash(cmd) == 0 || cmd[0] == '.')
	{
		printf("hi");
		p->cur_path = ft_strdup(cmd);
		return (free(p->cur_path), access(cmd, F_OK & X_OK));
	}
	else
	{
		i = 0;
		while (p->path[i])
		{
			p->cur_path = ft_strjoin(p->path[i], cmd);
			printf("cur path = %s\n", p->cur_path);
			if (access(p->cur_path, F_OK & X_OK) == 0)
				return (free(p->cur_path), 0);
			free(p->cur_path);
			i++;
		}
	}
	printf("h0");
	return (-1);
}

void get_access_path(t_cmd *p, char *cmd)
{
	size_t	i;
	
	if (ft_find_slash(cmd) == 0 || cmd[0] == '.')
	{
		if (access(cmd, F_OK & X_OK) != -1)
		{
			p->cur_path = ft_strdup(cmd);

		}
	}
	else
	{
		i = 0;
		while (p->path[i])
		{
			p->cur_path = ft_strjoin(p->path[i], cmd);
			if (access(p->cur_path, F_OK & X_OK) == 0)
				return ;
			free(p->cur_path);
			i++;
		}
	}
	// return (p->cur_path);
}
// void	child_process1(t_cmd *p, char **env, char** argv)
// {
// 	int fd_infile;

// 	fd_infile = open(argv[1], O_RDONLY);
// 	if (check_access_path(p, p->cmd1[0]) != 0)
// 		err_msg(p, "Can not access path\n");
// 	dprintf(2, "acess = %d | cur path1 = %s \n", access(p->cur_path, F_OK & X_OK), p->cur_path);
// 	dup2(fd_infile, 0);
// 	dup2(p->pfd[1], 1);
// 	close(fd_infile);
// 	close(p->pfd[0]);
// 	close(p->pfd[1]);
// 	// dprintf(2, "acess = %d | cur path1 = %s | exv = %d\n", access(p->cmd1[0], F_OK & X_OK), p->cur_path, execve(p->cur_path, p->cmd1, env));
// 	if (execve(p->cur_path, p->cmd1, env) == -1)
// 		err_msg(p, "fail child1\n");
// }

// void	child_process2(t_cmd *p, char **env, char** argv)
// {
// 	int fd_outfile;

// 	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	// free(p->cur_path);
// 	if (check_access_path(p, p->cmd2[0]) != 0)
// 		err_msg(p, "Can not access path");
// 	dprintf(2, "acess = %d | cur path2 = %s \n", access(p->cur_path, F_OK & X_OK), p->cur_path);
// 	dup2(p->pfd[0], 0);
// 	dup2(fd_outfile, 1);
// 	close(fd_outfile);
// 	close(p->pfd[0]);
// 	close(p->pfd[1]);
// 	if (execve(p->cur_path, p->cmd2, env) == -1)
// 		err_msg(p, "fail child2\n");
// 	else
// 		exit(0);
// }

void	child_process(t_cmd *p, char** argv,  char **env, int id)
{
	p->cmd = ft_split(argv[p->cur], ' ');
	get_access_path(p, p->cmd[0]);
	printf("hd = %d\n", p->heredoc);
	if (id == 0 && p->heredoc == 1)
		read_heredoc(p, argv);
	else
		ft_dup2(p, argv, id);
	close(p->pfd[0]);
	close(p->pfd[1]);
	dprintf(2, "p->cur = %d | id = %d| p->cmd[0] = %s| p->cmd[1] = %s | p->cmd[1] = %s\n", p->cur, id, p->cmd[0], p->cmd[1], p->cmd[2]);
	dprintf(2, "cur_path = %s\n", p->cur_path);
	// int i = 0;
	// while (p->cmd[i])
	// {
	// 	printf("p->cmd[%d] = %s", i, p->cmd[i]);
	// 	i++;
	// }
	if (execve(p->cur_path, p->cmd, env) == -1)
		err_msg(p, "fail child2\n");
	// get_cmd(argv[p->cur]);
}

void	parent_process(t_cmd *p)
{
	close(p->pfd[0]);
	close(p->pfd[1]);
	waitpid(p->pid, NULL, 0);
	// get_cmd(argv[p->cur]);
}

void	ft_dup2(t_cmd *p, char **argv, int id)
{
	p->fd_file = 0;
	printf("id = %d, cmd_nbr = %d\n", id, p->cmd_nbr);
	if(id == 0)
	{
		printf("first = %d\n", id);
		p->fd_file = open(argv[1], O_RDONLY);
		printf("fd_in = %d\n", p->fd_file);
		dup2(p->fd_file, STDIN_FILENO);
		// dup2(STDOUT_FILENO, p->pfd[1]);
		dup2(p->pfd[1], STDOUT_FILENO);
		close(p->fd_file);
	}
	else if(id > 0 && id < p->cmd_nbr - 1)
	{
		printf("mid = %d\n", id);
		dup2(p->pfd[0], STDIN_FILENO);
		dup2(p->pfd[1], STDOUT_FILENO);
	}
	else if (id == p->cmd_nbr - 1)
	{
		printf("last = %d\n", id);
		p->fd_file = open(argv[p->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		printf("fd_out = %d\n", p->fd_file);
		dup2(p->pfd[0], STDIN_FILENO);
		dup2(p->fd_file, STDOUT_FILENO);
		close(p->fd_file);
	}
	// close(p->pfd[0]);
	// close(p->pfd[1]);
}

void	read_heredoc(t_cmd *p, char** argv)
{
	char	*line;
	int		fd_heredoc;
	size_t	len;
	size_t	l;

	l = ft_strlen(argv[2]);
	fd_heredoc = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, argv[2], l) == 1)
	{
		len = ft_strlen(line);
		write(fd_heredoc, &line, len);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (line)
		free(line);
	dup2(fd_heredoc, STDIN_FILENO);
	dup2(STDOUT_FILENO, p->pfd[1]);
	close(fd_heredoc);
}
void free_cmd(t_cmd *p)
{
	int	i;

	i = 0;
	while(p->cmd[i])
	{
		free(p->cmd[i]);
		i++;
	}
	free(p->cmd);
}

int	check_all_access(t_cmd *p, char** argv)
{
	int	i;
	int	j;

	i = -1;
	j = p->cur;
	while (++i < p->cmd_nbr && j < p->argc - 1)
	{
		p->cmd = ft_split(argv[j], ' ');
		printf("j = %d, argv = %s, ac = %d\n", j, argv[j], check_access_path(p, argv[j]));
		if (check_access_path(p, p->cmd[0]) == -1)
			return (free_cmd(p), -1);
		free_cmd(p);
		j++;
	}
	printf("Can asses\n");
	return (1);
}

void	init_value(t_cmd *p, int argc)
{
	p->argc = argc;
	p->cur = 0;
	p->heredoc = 0;	
	p->path = NULL;
	p->found_path = -1;

}
int main(int argc, char** argv, char **env)
{
	t_cmd 	p;

	if (argc < 5)
		err_msg(&p, "Invalid argument");
	init_value(&p, argc);
	p.found_path = find_path(env);
	printf("path = |%s|\n", env[p.found_path]);
	if (p.found_path != -1)
		p.path = ft_split(&env[p.found_path][5], ':');
	prep_cmd(&p, argv[1]);
	if (check_all_access(&p, argv) == -1)
		err_msg(&p, "Can not access path");
	create_process(&p, argv, env);
	// get_cmd(&p, argc, argv, env);

	// if (ft_strncmp(argv[1], "heredoc", 8) == 0)
	// 	// ft_heredoc --> read gnl
	// else
	// 	//
	

		



	// if(pipe(p.pfd) == -1)
	// 	err_msg(&p, "Can not create pipe");
	// p.cmd1 = ft_split(argv[2], ' ');
	// p.cmd2 = ft_split(argv[3], ' ');

	// p.pid[0] = fork();
	// if (p.pid[0] == -1)
	// 	err_msg(&p, "Can not create fork");
	// if (p.pid[0] == 0)
	// 	child_process1(&p, env, argv);
	// p.pid[1] = fork();
	// if (p.pid[1] == 0 && p.pid[0] != 0)
	// 	child_process2(&p, env, argv);
	// if ((p.pid[0] > 0 || p.pid[1] > 0) && p.cur_path)
	// 	free(p.cur_path);
	// close(p.pfd[0]);
	// close(p.pfd[1]);
	
	// waitpid(p.pid[0], NULL, 0);
	// waitpid(p.pid[1], &p.status, 0);
	return (WEXITSTATUS(p.status));
}

void	prep_cmd(t_cmd *p, char *argv)
{
	if (p->argc >= 6 && !ft_strncmp(argv, "here_doc", 8))
	{
		p->heredoc = 1;	
		p->cmd_nbr = p->argc - 4;
	}
	else
		p->cmd_nbr = p->argc - 3;
	p->cur = p->argc - (p->cmd_nbr + 1);
	// p = malloc(sizeof(t_cmd) * p->cmd_nbr);
	// if (!p)
	// 	return ;
}
// void	create_pipe(char **argv, t_cmd *p)
// {
// 	int	i;

// 	*p->pfd = malloc(sizeof(int *) * p->cmd_nbr);
// 	if (!p->pfd)
// 		return (NULL);
// 	i = -1;
// 	if (!p->pfd)
// 		err_msg(p, "can not malloc, then free");
// 	i = 0;
// 	while (i < p->cmd_nbr)
// 	{
// 		if(pipe(p->pfd[i]) == -1)
// 		{
// 			i = -1;
// 			while (p->pfd[++i])
// 				free(p->pfd[i]);
// 			free(p->pfd);
// 			err_msg(p, "cant creating pipe\n");
// 		}
// 		i++;
// 	}
// }
void	create_process(t_cmd *p, char **argv, char **env)
{
	int id;
	// int	tmp_fd;
	// int	i;

	id = 0;
	// tmp_fd = dup(STDIN_FILENO);
	while (p->cur < (p->argc - 1) && id < p->cmd_nbr)
	{
		// p->cmd = ft_split(argv, ' ');
		// if (check_access_path(p, argv[p->cur]) != 0)
		// 	err_msg(p, "Can not access path");
		printf("-------------------------------------\n");
		printf("%d < %d && %d < %d\n", p->cur, (p->argc - 1) ,id, p->cmd_nbr);
		if(pipe(p->pfd) == -1)
			err_msg(p, "Can not create pipe");
		p->pid = fork();
		if (p->pid == -1)
			err_msg(p, "Can not create fork");
		else if (p->pid == 0)
		{
			printf("-->c\n");
			child_process(p, argv, env, id);
		}
		else
		{
			printf("-->pr\n");
			parent_process(p);
		}
		id++;
		p->cur++;
	}
}
// void	first_child(t_cmd *p, char **env, char **argv)
// {
// 	int fd_infile;

// 	fd_infile = open(argv[1], O_RDONLY);
// 	// dprintf(2, "acess = %d | cur path1 = %s \n", access(p->cur_path, F_OK & X_OK), p->cur_path);
// 	dup2(fd_infile, STDIN_FILENO);
// 	dup2(STDOUT_FILENO, p->pfd[1]);
// 	dup2(p->pfd[0], STDIN_FILENO);
// 	close(fd_infile);
// 	close(p->pfd[0]);
// 	close(p->pfd[1]);
// 	// dprintf(2, "acess = %d | cur path1 = %s | exv = %d\n", access(p->cmd1[0], F_OK & X_OK), p->cur_path, execve(p->cur_path, p->cmd1, env));
// 	if (execve(p->cur_path, p->cmd1, env) == -1)
// 		err_msg(p, "fail child1\n");
// }

// void	mid_child(t_cmp *p, char **env, char **argc)
// {
// 	dup2(p->pfd[0], STDIN_FILENO);
// 	dup2(p->pfd[1], STDOUT_FILENO);
// 	close(fd_infile);
// 	close(p->pfd[0]);
// 	close(p->pfd[1]);
// 	// dprintf(2, "acess = %d | cur path1 = %s | exv = %d\n", access(p->cmd1[0], F_OK & X_OK), p->cur_path, execve(p->cur_path, p->cmd1, env));
// 	if (execve(p->cur_path, p->cmd1, env) == -1)
// 		err_msg(p, "fail child1\n");
// }