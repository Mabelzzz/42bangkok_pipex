/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 01:00:59 by pnamwayk          #+#    #+#             */
/*   Updated: 2023/06/02 01:16:48 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	char	**cmd;
	int		cmd_nbr;
	int		argc;
	int		heredoc;
	int		cur;
	int		pfd[2];
	pid_t	*pid;
	char	*cur_path;
	char	**path;
	int		fd_file;
	int		tmp_fd;
	int		found_path;
	int		status;
}	t_cmd;

//	ft_dup2.c
void	ft_dup2(t_cmd *p, char **argv, int id);
void	dup_first_child(t_cmd *p, char *infile);
void	dup_last_child(t_cmd *p, char *outfile);

void	ft_putstr_fd(char *str, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t	ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strstr(char *str, char *find);

//	here_doc.c
void	read_heredoc(t_cmd *p, char **argv);
int		check_limiter(char *line, char *limiter, size_t n);

//	pipex_bonus.c
void	init_value(t_cmd *p, int argc);

//	process.c
void	start_process(t_cmd *p, char **argv, char **env);
void	create_process(t_cmd *p, char **argv, char **env);
void	child_process(t_cmd *p, char **argv, char **env, int id);
void	parent_process(t_cmd *p);
void	waiting_process(t_cmd *p);

//	utils_cmd.c
int		ft_find_slash(char *str);
void	count_cmd(t_cmd *p, char *filename);
void	free_cmd(t_cmd *p);

//	utils_error.c
void	err_file(t_cmd *p, char *file);
void	err_cmd(t_cmd *p, char *cmd, int err);
void	err_msg_free(t_cmd *p, char *msg);
void	err_msg(char *msg);
void	ft_exit(int err);

//	utils_path.c
int		find_path(char **env);
int		check_access_path(t_cmd *p, char *cmd);
void	free_path(t_cmd *p);

#endif
