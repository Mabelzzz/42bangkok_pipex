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

// t_cmd* commands;

// typedef struct s_cmd
// {
// 	char **args;
// }	t_cmd

// commands = ft_prepcmd(argv);

// ft_prepcmd:
// 	infile outfile 2
// 	cmd cmd 
// 	if argv[0] == 'here_doc'
// 		6 min
// 		argv[0,1, -1] reserve, rest is cmds
// 	else
// 		5 min argv[0, -1] reserce, rest is cmds
	
// 	malloc (t_cmd * argc - 4 or 3)
// 	split space argv
// 	assign t_cmd value
// 	access args[0] if args[0][0] == '/'

// execve(args[0], args, envp);

typedef struct s_cmd
{
	char	**cmd;
	int		cmd_nbr;
	int		i;
	int		pfd[2];
	int		pid[2];
	char	*cur_path;
	char 	**path;


	int		found_path;
	int		fd_infile;
	int		fd_outfile;
	int		ac;
	int		**fd_pipe;
	char	**cmd1;
	char	**cmd2;
	// int		pfd[2];
	// int		pid[2];
	int		status;
	// t_fd	*pipe;

}	t_cmd;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
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
