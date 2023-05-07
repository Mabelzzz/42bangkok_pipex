/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <pnamwayk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 10:51:14 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/04/23 11:23:42 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	check_newline(char *buf)
{
	size_t	len;

	len = 0;
	while (buf[len])
	{
		if (buf[len] == '\n')
			return (len + 1);
		len++;
	}
	len = 0;
	return (len);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(char *str)
{
	char	*new;
	size_t	index;
	size_t	len;

	len = ft_strlen(str);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	index = 0;
	while (str[index] != 0 && index < len)
	{
		new[index] = str[index];
		index++;
	}
	new[index] = 0;
	return (new);
}

char	*tmp_cnt(char *s, size_t nbyte)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = malloc(sizeof(char) * (nbyte + 1));
	if (!tmp)
		return (NULL);
	while (i < nbyte)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = 0;
	free(s);
	return (tmp);
}

char	*ft_strjoin_nl(char *s1, char *s2, size_t nbyte)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || *s1 == 0)
		return (tmp_cnt(s2, nbyte));
	j = ft_strlen(s1);
	if (!s2 || *s2 == 0)
		return (tmp_cnt(s1, j));
	str = malloc(sizeof(char) * (j + nbyte + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < j)
		str[i] = s1[i];
	j = 0;
	while (j < nbyte)
		str[i++] = s2[j++];
	str[i] = 0;
	free(s1);
	free(s2);
	return (str);
}
