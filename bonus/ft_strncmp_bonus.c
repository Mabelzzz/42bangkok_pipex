/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:27:46 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/05/31 00:07:08 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
#include "../gnl/get_next_line.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	int				diff;
	unsigned int	index;

	index = 0;
	diff = 0;
	while (index < n && (s1[index] != 0 || s2[index] != 0))
	{
		if (s1[index] != s2[index])
			return (1);
		index++;
	}
	return (0);
}

int	check_limiter(char *line, char *limiter, size_t n)
{
	unsigned int	index;

	index = 0;
	while (index < n && (line[index] != 0 || limiter[index] != 0))
	{
		if (line[index] != limiter[index])
			return (1);
		index++;
	}
	if (line[index] != '\n')
		return (1);
	return (0);
}
