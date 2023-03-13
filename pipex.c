#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fd[2];
    pid_t pid;

    if (argc != 4) {
        printf("Usage: %s cmd1 cmd2 file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // child process
        close(fd[0]); // close unused read end of the pipe
        dup2(fd[1], STDOUT_FILENO); // redirect stdout to the pipe
        execlp(argv[1], argv[1], NULL); // execute the first command
        perror(argv[1]); // print error message if execlp fails
        exit(EXIT_FAILURE);
    } else {
        // parent process
        int status;
        pid_t pid2;

        pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            // second child process
            close(fd[1]); // close unused write end of the pipe
            dup2(fd[0], STDIN_FILENO); // redirect stdin to the pipe
            execlp(argv[2], argv[2], NULL); // execute the second command
            perror(argv[2]); // print error message if execlp fails
            exit(EXIT_FAILURE);
        } else {
            // parent process
            close(fd[0]);
            close(fd[1]);
            waitpid(pid, &status, 0);
            waitpid(pid2, &status, 0);
        }
    }

    return 0;
}

//  gcc -o pipex pipex.c
// $ ./pipex cmd1 cmd2 file
