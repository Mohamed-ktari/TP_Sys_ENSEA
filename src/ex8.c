#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "../include/ex6.h"
#include "../include/ex7.h"

int split_pipe(char *buffer, char **left, char **right)
{
    char *pipe_pos = strchr(buffer, '|');
    if (!pipe_pos)
        return 0;

    *pipe_pos = '\0';
    *left  = buffer;
    *right = pipe_pos + 1;
    //triming the spaces
    while (**right == ' ' || **right == '\t')
        (*right)++;

    return 1;
}

int execute_pipe(char *left_cmd, char *right_cmd)
{
    int fd[2];
    pid_t pid1, pid2;
    int status1, status2;

    char *argv1[MAX_ARGS];
    char *argv2[MAX_ARGS];

    if (pipe(fd) == -1) {
        perror("pipe");
        return -1;
    }

    /* First child: left command */
    pid1 = fork();
    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        parse_command(left_cmd, argv1);
        handle_redirection(argv1);
        execvp(argv1[0], argv1);

        perror("execvp failed");
        exit(EXIT_FAILURE);
    }

    /* Second child: right command */
    pid2 = fork();
    if (pid2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);

        parse_command(right_cmd, argv2);
        handle_redirection(argv2);
        execvp(argv2[0], argv2);

        perror("execvp failed");
        exit(EXIT_FAILURE);
    }

    /* Parent */
    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);

    /* Return status of LAST command */
    return status2;
}
