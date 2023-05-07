#include "../includes/pipex_bonus.h"

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

void	read_heredoc(t_cmd *p, char **env, char** argv)
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
	free(line);

	close(fd_heredoc);
}

int main(int argc, char** argv, char **env)
{
	t_cmd 	p;

	if (argc < 5)
		err_msg(&p, "Invalid argument");
	p.found_path = find_path(env);
	if (ft_strncmp(argv[1], "heredoc", 8) == 0)
		// ft_heredoc --> read gnl
	else
		//
	while ()
	
	if (p.found_path != -1)
		p.path = ft_split(&env[p.found_path][5], ':');
	prep_cmd(&p, argc, argv[1]);
	get_cmd(&p, argc, argv, env);
	if ()

		



	if(pipe(p.pfd) == -1)
		err_msg(&p, "Can not create pipe");
	p.cmd1 = ft_split(argv[2], ' ');
	p.cmd2 = ft_split(argv[3], ' ');

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

void	prep_cmd(t_cmd *p, int argc, char *argv)
{
	if (argc >= 6 && !ft_strncmp(argv, "here_doc", 8))
		p->cmd_nbr = argc - 4;
	else
		p->cmd_nbr = argc - 3;
	p = malloc(sizeof(t_cmd) * p->cmd_nbr);
	if (!p)
		return ;
}

void	get_cmd(t_cmd *p, int argc, char **argv, char **env)
{
	int id;
	int	tmp_fd;

	tmp_fd = dup(STDIN_FILENO);
	p->i = argc - (p->cmd_nbr + 1);
	while (p->i < (argc - 1))
	{
		p->cmd = ft_split(argv, ' ');
		if (check_access_path(p, argv[p->i]) != 0)
			err_msg(p, "Can not access path");
		if(pipe(p->pfd) == -1)
			err_msg(&p, "Can not create pipe");
		p->pid[id] = fork();
		if (p->pid[id] == -1)
			err_msg(&p, "Can not create fork");
		if (p->pid[id] == 0 && id == 0)
			first_child(p, env, argv);
		else if (p->pid[id] == 0 && id != 0)
			mid_child(p, env, argv);
		else
			parent_process(p, env, argv);
		
		if (p->pid[id] == 0 && id == (argc - 2))
			last_child(p, env, argv);
		else
			last_parent(p, env, argv);
		id++;
		p->i++;
	}
}
void	first_child(t_cmd *p, char **env, char **argv)
{
	int fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	// dprintf(2, "acess = %d | cur path1 = %s \n", access(p->cur_path, F_OK & X_OK), p->cur_path);
	dup2(fd_infile, STDIN_FILENO);
	dup2(STDOUT_FILENO, p->pfd[1]);
	dup2(p->pfd[0], STDIN_FILENO);
	close(fd_infile);
	close(p->pfd[0]);
	close(p->pfd[1]);
	// dprintf(2, "acess = %d | cur path1 = %s | exv = %d\n", access(p->cmd1[0], F_OK & X_OK), p->cur_path, execve(p->cur_path, p->cmd1, env));
	if (execve(p->cur_path, p->cmd1, env) == -1)
		err_msg(p, "fail child1\n");
}

void	mid_child(t_cmp *p, char **env, char **argc)
{
	dup2(p->pfd[0], STDIN_FILENO);
	dup2(p->pfd[1], STDOUT_FILENO);
	close(fd_infile);
	close(p->pfd[0]);
	close(p->pfd[1]);
	// dprintf(2, "acess = %d | cur path1 = %s | exv = %d\n", access(p->cmd1[0], F_OK & X_OK), p->cur_path, execve(p->cur_path, p->cmd1, env));
	if (execve(p->cur_path, p->cmd1, env) == -1)
		err_msg(p, "fail child1\n");
}