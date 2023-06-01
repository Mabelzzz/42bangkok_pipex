/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:52:27 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 00:52:28 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int		ft_find_slash(char *str);
void	count_cmd(t_cmd *p, char *filename);

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

void	count_cmd(t_cmd *p, char *filename)
{
	if (p->argc >= 6 && !ft_strncmp(filename, "here_doc", 9))
	{
		p->heredoc = 1;
		p->cmd_nbr = p->argc - 4;
	}
	else
		p->cmd_nbr = p->argc - 3;
	p->cur = p->argc - (p->cmd_nbr + 1);
}
