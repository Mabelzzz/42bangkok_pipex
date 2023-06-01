/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:49:38 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 00:49:39 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_dup2(t_cmd *p, char **argv, int id);
void	dup_first_child(t_cmd *p, char *infile);
void	dup_last_child(t_cmd *p, char *outfile);

void	ft_dup2(t_cmd *p, char **argv, int id)
{
	if (id == 0)
		dup_first_child(p, argv[1]);
	else if (id > 0 && id < p->cmd_nbr - 1)
	{
		dup2(p->tmp_fd, STDIN_FILENO);
		dup2(p->pfd[1], STDOUT_FILENO);
	}
	else if (id == p->cmd_nbr - 1)
		dup_last_child(p, argv[p->argc - 1]);
}

void	dup_first_child(t_cmd *p, char *infile)
{
	p->fd_file = open(infile, O_RDONLY);
	if (p->fd_file == -1)
		err_file(p, infile);
	dup2(p->fd_file, STDIN_FILENO);
	dup2(p->pfd[1], STDOUT_FILENO);
	close(p->fd_file);
	if (p->heredoc == 1)
		unlink(infile);
}

void	dup_last_child(t_cmd *p, char *outfile)
{
	if (p->heredoc == 1)
		p->fd_file = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		p->fd_file = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->fd_file == -1)
		err_file(p, outfile);
	dup2(p->tmp_fd, STDIN_FILENO);
	dup2(p->fd_file, STDOUT_FILENO);
	close(p->fd_file);
}
