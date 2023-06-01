/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:50:31 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 00:50:44 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
// #include "../gnl/get_next_line.h"

char	*ft_strdup(char *str)
{
	char	*new;
	int		index;

	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	index = 0;
	while (str[index] != 0)
	{
		new[index] = str[index];
		index++;
	}
	new[index] = 0;
	return (new);
}
