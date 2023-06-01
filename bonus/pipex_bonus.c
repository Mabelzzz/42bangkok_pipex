/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:52:07 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 00:52:08 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	init_value(t_cmd *p, int argc);

int	main(int argc, char **argv, char **env)
{
	t_cmd	p;

	if (argc < 5)
		err_msg("Invalid argument");
	init_value(&p, argc);
	start_process(&p, argv, env);
	return (WEXITSTATUS(p.status));
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
