/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:52:48 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 00:52:49 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int		find_path(char **env);
int		check_access_path(t_cmd *p, char *cmd);

int	find_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
	{
		if (ft_strstr(env[i], "PATH=") == 0)
			return (i);
	}
	return (-1);
}

int	check_access_path(t_cmd *p, char *cmd)
{
	size_t	i;

	if (!cmd)
		return (err_cmd(p, cmd, 2), -1);
	if (ft_find_slash(cmd) == 0)
	{
		p->cur_path = ft_strdup(cmd);
		if (access(cmd, F_OK & X_OK) == 0)
			return (0);
		free(p->cur_path);
		err_cmd(p, cmd, 9);
	}
	else
	{
		i = -1;
		while (p->path[++i])
		{
			p->cur_path = ft_strjoin(p->path[i], cmd);
			if (access(p->cur_path, F_OK & X_OK) == 0)
				return (0);
			free(p->cur_path);
		}
		err_cmd(p, cmd, 2);
	}
	return (-1);
}
