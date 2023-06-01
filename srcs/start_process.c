/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:49:05 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 00:49:06 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	start_process(t_cmd *p, char **argv, char **env);
void	child_process1(t_cmd *p, char **env, char **argv);
void	child_process2(t_cmd *p, char **env, char **argv);

void	start_process(t_cmd *p, char **argv, char **env)
{
	if (pipe(p->pfd) == -1)
		err_msg_free(p, "Pipe error: ");
	p->pid[0] = fork();
	if (p->pid[0] == -1)
		err_msg_free(p, "Fork error: ");
	if (p->pid[0] == 0)
		child_process1(p, env, argv);
	p->pid[1] = fork();
	if (p->pid[1] == 0 && p->pid[0] != 0)
		child_process2(p, env, argv);
}

void	child_process1(t_cmd *p, char **env, char **argv)
{
	int	fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		err_file(p, argv[1]);
	dup_close_evth(p, fd_infile, 1);
	p->cmd1 = ft_split(argv[2], ' ');
	if (check_access_path(p, p->cmd1[0], 1) == 0)
	{
		if (execve(p->cur_path, p->cmd1, env) == -1)
		{
			free(p->cur_path);
			err_cmd(p, p->cmd1[0], 13, 1);
		}
	}
}

void	child_process2(t_cmd *p, char **env, char **argv)
{
	int	fd_outfile;

	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
		err_file(p, argv[4]);
	dup_close_evth(p, fd_outfile, 2);
	p->cmd2 = ft_split(argv[3], ' ');
	if (check_access_path(p, p->cmd2[0], 2) == 0)
	{
		if (execve(p->cur_path, p->cmd2, env) == -1)
		{
			free(p->cur_path);
			err_cmd(p, p->cmd2[0], 13, 2);
		}
	}
}
