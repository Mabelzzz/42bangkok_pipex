#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

typedef struct s_pipe
{
	int		found_path;
	int		pid[2];
	char	*path;

}	t_pipe;
#endif
