/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <pnamwayk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 01:39:44 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/04/23 11:23:57 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *tmp)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	j = check_newline(tmp);
	line = malloc(sizeof(char) * (j + 1));
	if (!line)
		return (NULL);
	while (tmp[i] != 0 && i < j)
	{
		line[i] = tmp[i];
		if (line[i] == '\n')
			break ;
		i++;
	}
	line[i + 1] = 0;
	return (line);
}

char	*get_temp(char *tmp)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*tmp_new;

	i = 0;
	j = check_newline(tmp);
	k = ft_strlen(tmp);
	if (k == j || tmp[j] == 0)
	{
		free(tmp);
		return (NULL);
	}
	tmp_new = malloc(sizeof(char) * (k - j + 1));
	if (!tmp_new)
		return (NULL);
	while (tmp[j] != 0 && j < k)
		tmp_new[i++] = tmp[j++];
	tmp_new[i] = 0;
	free(tmp);
	tmp = NULL;
	return (tmp_new);
}

t_gnl	check_error(t_gnl fl)
{
	free(fl.buf);
	if (fl.byte == 0 && fl.tmp)
	{
		fl.line = ft_strdup(fl.tmp);
		free(fl.tmp);
		fl.tmp = NULL;
	}
	return (fl);
}

t_gnl	read_file(int fd, t_gnl fl)
{
	fl.byte = 1;
	while (fl.byte)
	{
		fl.buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!fl.buf)
			return (fl);
		fl.byte = read(fd, fl.buf, BUFFER_SIZE);
		fl.buf[fl.byte] = 0;
		if (fl.byte <= 0)
		{
			fl = check_error(fl);
			return (fl);
		}
		if (check_newline(fl.buf) != 0)
		{
			fl.tmp2 = ft_strdup(fl.buf);
			fl.line = ft_strjoin_nl(fl.tmp, fl.buf, check_newline(fl.buf));
			fl.tmp = get_temp(fl.tmp2);
			return (fl);
		}
		else
			fl.tmp = ft_strjoin_nl(fl.tmp, fl.buf, (size_t)fl.byte);
	}
	return (fl);
}

char	*get_next_line(int fd)
{
	static t_gnl	fl;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (NULL);
	fl.buf = NULL;
	fl.line = NULL;
	fl.tmp2 = NULL;
	fl.byte = 1;
	if (fl.tmp && check_newline(fl.tmp) != 0)
	{
		fl.line = get_line(fl.tmp);
		fl.tmp = get_temp(fl.tmp);
		return (fl.line);
	}
	else
		fl = read_file(fd, fl);
	return (fl.line);
}
