/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 21:32:48 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/05/31 00:30:06 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"
// #include "../gnl/get_next_line.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	s;

	if (!str)
		return ;
	s = 0;
	while (str[s] != '\0')
	{
		write(fd, &str[s], 1);
		s++;
	}
}
