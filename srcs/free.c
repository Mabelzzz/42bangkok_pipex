/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:46:17 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 00:46:18 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_path(t_cmd *p);
void	free_cmd1(t_cmd *p);
void	free_cmd2(t_cmd *p);

void	free_path(t_cmd *p)
{
	int	i;

	if (!p->path)
		return ;
	i = -1;
	while (p->path[++i])
		free(p->path[i]);
	free(p->path);
}

void	free_cmd1(t_cmd *p)
{
	int	i;

	if (!p->cmd1)
		return ;
	i = -1;
	while (p->cmd1[++i])
		free(p->cmd1[i]);
	free(p->cmd1);
}

void	free_cmd2(t_cmd *p)
{
	int	i;

	if (!p->cmd2)
		return ;
	i = -1;
	while (p->cmd2[++i])
		free(p->cmd2[i]);
	free(p->cmd2);
}
