/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:51:49 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 01:03:18 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
// #include "../gnl/get_next_line.h"

int	ft_strstr(char *str, char *find)
{
	int	i;
	int	j;
	int	cp;

	i = 0;
	cp = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == find[0])
		{
			j = 0;
			while (find[j])
			{
				if (str[i] == find[j])
					cp++;
				j++;
				i++;
			}
			if (cp == j)
				return (0);
		}
		i++;
	}
	return (-1);
}
