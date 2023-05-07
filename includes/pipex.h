#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h> //open
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

// typedef struct s_fd
// {
// 	// int		*pfd[2];
// 	// int		*pid;
// 	char	*cmd[2];


// }	t_fd;

typedef struct s_cmd
{
	int		found_path;
	// int		fd_infile;
	// int		fd_outfile;
	int		ac;
	char 	**path;
	int		**fd_pipe;
	// int		*pid;
	// int		**pfd;
	char	***cmd;
	char	**cmd1;
	char	**cmd2;
	int		pfd[2];
	int		pid[2];
	char	*cur_path;
	int		status;
	// t_fd	*pipe;

}	t_cmd;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
void	err_msg(t_cmd *p, char *msg);
int		ft_strstr(char *str, char *find);
int		ft_find_slash(char *str);
void	child_process1(t_cmd *p, char **env, char** argv);
void	child_process2(t_cmd *p, char **env, char** argv);
void ft_free_path(t_cmd *p);
// typedef struct s_cmd
// {
// 	int		found_path;
// 	int		*pid;
// 	t_pipe	*p;

// }	t_cmd;
// typedef struct s_cmd
// {
// 	int		found_path;
// 	char	*path;
// 	// t_pipe	*p;

// }	t_cmp;
#endif
