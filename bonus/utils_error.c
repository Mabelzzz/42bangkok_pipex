/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:52:36 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 00:52:37 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	err_file(t_cmd *p, char *file);
void	err_cmd(t_cmd *p, char *cmd, int err);
void	err_msg_free(t_cmd *p, char *msg);
void	err_msg(char *msg);
void	ft_exit(int err);

void	err_file(t_cmd *p, char *file)
{
	free_path(p);
	write(STDERR_FILENO, "pipex: ", 8);
	write(STDERR_FILENO, file, ft_strlen(file));
	write(STDERR_FILENO, ": ", 3);
	perror("");
	exit(EXIT_FAILURE);
}

void	err_cmd(t_cmd *p, char *cmd, int err)
{
	write(STDERR_FILENO, "pipex: ", 8);
	if (cmd)
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
	if (ft_find_slash(cmd) == 0 && err == 9)
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	else if (err == 2)
		write(STDERR_FILENO, ": command not found\n", 20);
	else if (err == 13)
		write(STDERR_FILENO, ": Permission denied\n", 20);
	free_cmd(p);
	free_path(p);
	ft_exit(err);
}

void	err_msg_free(t_cmd *p, char *msg)
{
	free_path(p);
	perror(msg);
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	err_msg(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_exit(int err)
{
	if (err == 13)
		exit(126);
	else if (err == 2 || err == 9)
		exit(127);
	else
		exit(EXIT_FAILURE);
}
