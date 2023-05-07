/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <pnamwayk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:27:46 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/04/24 01:07:11 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
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
