/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:23:59 by pnamwayk          #+#    #+#             */
/*   Updated: 2022/10/30 19:26:47 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl{
	char	*line;
	char	*tmp;
	char	*buf;
	int		byte;
	char	*tmp2;
}	t_gnl;

char	*get_next_line(int fd);
size_t	check_newline(char *buf);
size_t	ft_strlen(char *str);
size_t	check_eof(char *str);
char	*ft_strjoin_nl(char *s1, char *s2, size_t nbyte);
char	*ft_strdup(char *str);
char	*get_temp(char *tmp);
char	*get_line(char *tmp);
char	*tmp_cnt(char *s, size_t nbyte);
t_gnl	read_file(int fd, t_gnl fl);
t_gnl	check_error(t_gnl fl);

#endif
