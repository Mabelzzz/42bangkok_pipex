/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:49:13 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 00:49:14 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_value(t_cmd *p);
void	dup_close_evth(t_cmd *p, int fd, int child);
void	close_pipe(t_cmd *p);

void	init_value(t_cmd *p)
{
	p->found_path = -1;
	p->path = NULL;
}

void	close_pipe(t_cmd *p)
{
	close(p->pfd[0]);
	close(p->pfd[1]);
}

void	dup_close_evth(t_cmd *p, int fd, int child)
{
	if (child == 1)
	{
		dup2(fd, 0);
		dup2(p->pfd[1], 1);
	}
	else if (child == 2)
	{
		dup2(p->pfd[0], 0);
		dup2(fd, 1);
	}
	close(fd);
	close_pipe(p);
}
