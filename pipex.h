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

typedef struct s_fd
{
	int		pfd[2];
	int		*pid;
	char	*cmd[2];


}	t_fd;

typedef struct s_cmd
{
	int		found_path;
	int		fd_infile;
	int		fd_outfile;
	int		ac;
	char 	**path;
	t_fd	*pipe;

}	t_cmd;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);

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
// 	t_pipe	*p;

// }	t_cmp;
#endif
