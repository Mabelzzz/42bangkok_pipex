/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:48:59 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 00:49:00 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_cmd	p;

	if (argc != 5)
		err_msg("Invalid argument");
	p.found_path = find_path(env);
	if (p.found_path != -1)
		p.path = ft_split(&env[p.found_path][5], ':');
	start_process(&p, argv, env);
	close_pipe(&p);
	waitpid(p.pid[0], &p.status, WUNTRACED);
	waitpid(p.pid[1], &p.status, WUNTRACED);
	free_path(&p);
	return (WEXITSTATUS(p.status));
}
