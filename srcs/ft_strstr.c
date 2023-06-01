/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:47:50 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 01:04:14 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
