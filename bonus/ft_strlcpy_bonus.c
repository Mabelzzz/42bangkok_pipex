/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <pnamwayk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:55:33 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/04/24 01:00:39 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;

	index = 0;
	if (dstsize > 0)
	{
		while (dstsize-- > 1 && src[index] != 0)
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = 0;
	}
	return (ft_strlen(src));
}
