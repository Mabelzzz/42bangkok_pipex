/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 01:12:35 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 01:17:32 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	int		found_path;
	char	**path;
	char	**cmd1;
	char	**cmd2;
	int		pfd[2];
	int		pid[2];
	char	*cur_path;
	int		status;
}	t_cmd;

//	check_path.c
int		find_path(char **env);
int		ft_find_slash(char *str);
int		check_access_path(t_cmd *p, char *cmd, int cmd_no);

//	error.c
void	err_file(t_cmd *p, char *file);
void	err_cmd(t_cmd *p, char *cmd, int err, int cmd_no);
void	err_msg_free(t_cmd *p, char *msg);
void	err_msg(char *msg);
void	ft_exit(int err);

//	free.c
void	free_path(t_cmd *p);
void	free_cmd1(t_cmd *p);
void	free_cmd2(t_cmd *p);

char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_strstr(char *str, char *find);

//	start_process.c
void	start_process(t_cmd *p, char **argv, char **env);
void	child_process1(t_cmd *p, char **env, char **argv);
void	child_process2(t_cmd *p, char **env, char **argv);

//	utils.c
void	init_value(t_cmd *p);
void	dup_close_evth(t_cmd *p, int fd, int child);
void	close_pipe(t_cmd *p);

#endif
