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
void	free_pipe(t_cmd *p);

int	find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strstr(env[i], "PATH=") == 0)
			return (i);
		i++;
	}
	return (-1);
}

int check_access_path(t_cmd *p, char *cmd)
{
	size_t	i;
	if (ft_find_slash(cmd) == 0 || cmd[0] == '.')
	{
		p->cur_path = ft_strdup(cmd);
		return (free(p->cur_path), access(cmd, F_OK & X_OK));
	}
	else
	{
		i = 0;
		while (p->path[i])
		{

			p->cur_path = ft_strjoin(p->path[i], cmd);
			// printf("ac = %d cur = %s cmd = %s\n", access(p->cur_path, F_OK & X_OK), p->cur_path, cmd);
			if (access(p->cur_path, F_OK & X_OK) == 0)
				return (free(p->cur_path), 0);
			free(p->cur_path);
			i++;
		}
	}
	return (-1);
}

// int get_access_path(t_cmd *p, char *cmd)
// {
// 	size_t	i;

// 	if (ft_find_slash(cmd) == 0 || cmd[0] == '.')
// 	{
// 		if (access(cmd, F_OK & X_OK) != -1)
// 		{
// 			p->cur_path = ft_strdup(cmd);
// 			return (0);
// 		}
// 	}
// 	else
// 	{
// 		i = 0;
// 		while (p->path[i])
// 		{
// 			p->cur_path = ft_strjoin(p->path[i], cmd);
// 			if (access(p->cur_path, F_OK & X_OK) == 0)
// 				return (0);
// 			free(p->cur_path);
// 			i++;
// 		}
// 	}
// 	return (-1);
// }

void	child_process(t_cmd *p, char** argv,  char **env, int id)
{
	close(p->pfd[0]);
	if (id == 0 && p->heredoc == 1)
		read_heredoc(p, argv);
	else
		ft_dup2(p, argv, id);
	close(p->pfd[1]);
	p->cmd = ft_split(argv[p->cur], ' ');
	if (check_access_path(p, p->cmd[0]) == -1)
	{
		if (ft_find_slash(p->cmd[0]) == 0)
			err_file(p, p->cmd[0], 1);
		else
			err_file(p, p->cmd[0], 3);
	}
	if (execve(p->cur_path, p->cmd, env) == -1)
		err_msg(p, "fail child2\n");
}

void	parent_process(t_cmd *p)
{
	// waitpid(p->pid, NULL, 0);
	// p->tmp_fd = p->pfd[0];
	close(p->pfd[1]);
	p->tmp_fd = dup(p->pfd[0]);
	close(p->pfd[0]);
}

void	ft_dup2(t_cmd *p, char **argv, int id)
{
	if (id == 0)
	{
		p->fd_file = open(argv[1], O_RDONLY);
		if(p->fd_file == -1)
			err_file(p, argv[1], 1);
		dup2(p->fd_file, STDIN_FILENO);
		dup2(p->pfd[1], STDOUT_FILENO);
		close(p->fd_file);
	}
	else if(id > 0 && id < p->cmd_nbr - 1)
	{
		dup2(p->tmp_fd, STDIN_FILENO);
		dup2(p->pfd[1], STDOUT_FILENO);
	}
	else if (id == p->cmd_nbr - 1)
	{
		if (p->heredoc == 1)
			p->fd_file = open(argv[p->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			p->fd_file = open(argv[p->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p->fd_file == -1)
			err_file(p, argv[p->argc - 1], 2);
		dup2(p->tmp_fd, STDIN_FILENO);
		dup2(p->fd_file, STDOUT_FILENO);
		close(p->fd_file);
	}
}

void	read_heredoc(t_cmd *p, char** argv)
{
	char	*line;
	int		fd_heredoc;
	size_t	len;
	size_t	l;

	l = ft_strlen(argv[2]);
	fd_heredoc = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_heredoc == -1)
		err_file(p, argv[1], 1);
		// err_msg(p, "can not open file heredoc");
	ft_putstr_fd("heredoc> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line && check_limiter(line, argv[2], l) == 1)
	{
		len = ft_strlen(line);
		write(fd_heredoc, line, len);
		free(line);
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	if (line)
		free(line);
	close(fd_heredoc);
	fd_heredoc = open(argv[1], O_RDONLY);
	dup2(fd_heredoc, STDIN_FILENO);
	dup2(p->pfd[1], STDOUT_FILENO);
	close(fd_heredoc);
	unlink(argv[1]);
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
		if (check_access_path(p, p->cmd[0]) == -1)
			return (free_cmd(p), -1);
		free_cmd(p);
		j++;
	}
	return (1);
}

void	init_value(t_cmd *p, int argc)
{
	p->argc = argc;
	p->cur = 0;
	p->fd_file = 0;
	p->tmp_fd = 0;
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
	if (p.found_path != -1)
		p.path = ft_split(&env[p.found_path][5], ':');
	prep_cmd(&p, argv[1]);
	// if (check_all_access(&p, argv) == -1)
	// 	err_msg(&p, "Can not access path");
	create_process(&p, argv, env);
	// return (WEXITSTATUS(p.status));
	// exit(EXIT_SUCCESS);
	// return (WEXITSTATUS(p.status));
	return WIFEXITED(p.status) && WEXITSTATUS(p.status);
}

void	prep_cmd(t_cmd *p, char *argv)
{
	if (p->argc >= 6 && !ft_strncmp(argv, "here_doc", 9))
	{
		p->heredoc = 1;
		p->cmd_nbr = p->argc - 4;
	}
	else
		p->cmd_nbr = p->argc - 3;
	p->cur = p->argc - (p->cmd_nbr + 1);
}

void	create_process(t_cmd *p, char **argv, char **env)
{
	int id;
	int		sl;

	sl = p->cur;
	id = 0;
	p->pid = malloc(sizeof(pid_t) * p->cmd_nbr);
	while (p->cur < (p->argc - 1) && id < p->cmd_nbr)
	{
		if (id != p->cmd_nbr - 1)
		{
			if(pipe(p->pfd) == -1)
				err_msg(p, "Pipe error: ");
		}
		p->pid[id] = fork();
		if (p->pid[id] == -1)
			err_msg(p, "Fork error: ");
		else if (p->pid[id] == 0)
			child_process(p, argv, env, id)
		else
		{
			// dprintf(2, "parent pc = %d\n", id);
			parent_process(p);
			// p->tmp_fd = p->pfd[0];
			// close(p->pfd[1]);
		}
		id++;
		p->cur++;
	}
	close(p->pfd[0]);
	close(p->pfd[1]);
	id = -1;
	while (++id < p->cmd_nbr)
	{
		// if (ft_strncmp(argv[sl], "sleep", 5) == 0)
		// 	waitpid(p->pid[id], NULL, 0);
		waitpid(p->pid[id], &p->status,0);

	}
	// waitpid(p->pid[p->cmd_nbr - 1], NULL, 0);
	// while (waitpid(-1, NULL, 0) != -1)
	// {
	// 	// dprintf(2, "id = %d\n",id++);
	// }

		// waitpid(-1, NULL, WNOHANG);
	// close(p->pfd[0]);
	if (WEXITSTATUS(p->status) != 0)
		exit(WEXITSTATUS(p->status));
	// exit(EXIT_SUCCESS);
}
