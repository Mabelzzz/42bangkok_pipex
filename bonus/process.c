/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:52:22 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 01:03:29 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	start_process(t_cmd *p, char **argv, char **env);
void	create_process(t_cmd *p, char **argv, char **env);
void	child_process(t_cmd *p, char **argv, char **env, int id);
void	parent_process(t_cmd *p);
void	waiting_process(t_cmd *p);

void	start_process(t_cmd *p, char **argv, char **env)
{
	p->found_path = find_path(env);
	if (p->found_path != -1)
		p->path = ft_split(&env[p->found_path][5], ':');
	count_cmd(p, argv[1]);
	p->pid = malloc(sizeof(pid_t) * p->cmd_nbr);
	if (p->heredoc == 1)
		read_heredoc(p, argv);
	create_process(p, argv, env);
	close(p->pfd[0]);
	close(p->pfd[1]);
	waiting_process(p);
	free_path(p);
}

void	create_process(t_cmd *p, char **argv, char **env)
{
	int	id;

	id = 0;
	while (p->cur < (p->argc - 1) && id < p->cmd_nbr)
	{
		if (id != p->cmd_nbr - 1)
		{
			if (pipe(p->pfd) == -1)
				err_msg_free(p, "Pipe error: ");
		}
		p->pid[id] = fork();
		if (p->pid[id] == -1)
			err_msg_free(p, "Fork error: ");
		else if (p->pid[id] == 0)
			child_process(p, argv, env, id);
		else
			parent_process(p);
		id++;
		p->cur++;
	}
}

void	child_process(t_cmd *p, char **argv, char **env, int id)
{
	close(p->pfd[0]);
	ft_dup2(p, argv, id);
	close(p->pfd[1]);
	p->cmd = ft_split(argv[p->cur], ' ');
	if (check_access_path(p, p->cmd[0]) == 0)
	{
		if (execve(p->cur_path, p->cmd, env) == -1)
		{
			free(p->cur_path);
			err_cmd(p, p->cmd[0], 13);
		}
	}
}

void	parent_process(t_cmd *p)
{
	close(p->pfd[1]);
	p->tmp_fd = dup(p->pfd[0]);
	close(p->pfd[0]);
}

void	waiting_process(t_cmd *p)
{
	int	id;

	id = -1;
	while (++id < p->cmd_nbr)
		waitpid(p->pid[id], &p->status, WUNTRACED);
}
