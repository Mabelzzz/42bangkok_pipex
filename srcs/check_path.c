/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:46:00 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 00:46:01 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int		find_path(char **env);
int		ft_find_slash(char *str);
int		check_access_path(t_cmd *p, char *cmd, int cmd_no);

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

int	ft_find_slash(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (-1);
	while (str[++i] != '\0')
	{
		if (str[i] == '/')
			return (0);
	}
	return (-1);
}

int	check_access_path(t_cmd *p, char *cmd, int cmd_no)
{
	size_t	i;

	if (!cmd)
		return (err_cmd(p, cmd, 2, cmd_no), -1);
	if (ft_find_slash(cmd) == 0)
	{
		p->cur_path = ft_strdup(cmd);
		if (access(cmd, F_OK & X_OK) == 0)
			return (0);
		free(p->cur_path);
		err_cmd(p, cmd, 9, cmd_no);
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
		err_cmd(p, cmd, 2, cmd_no);
	}
	return (-1);
}
