#include <unistd.h>
#include <stdlib.h>


int execute(char **argv, char **envp)
{
    execve(argv[0], argv, envp);
}

int main(int argc, char ** argv, char **envp)
{
    int pid;

    pid = fork();
    if (pid != 0)
        execute(argv, envp);
    else
        waitpid(pid, NULL, -1);
    return 0;
}