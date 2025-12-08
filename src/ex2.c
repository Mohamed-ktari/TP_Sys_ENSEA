#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define PROMPT "enseash% "
#define ERROR "Command not found\n"
#define FORK_ERROR "Fork failed\n"

void display_regular_prompt(char *buffer, size_t buf_size) {
    __pid_t pid;
    ssize_t len;

    while (1) {

        
        write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
        len = read(STDIN_FILENO, buffer, buf_size);
        buffer[len - 1] = '\0';
        pid = fork();
        if(pid < 0){
            write(STDERR_FILENO,FORK_ERROR,strlen(FORK_ERROR));
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            execlp(buffer, buffer, NULL);
            write(STDERR_FILENO, ERROR, strlen(ERROR));
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
    }
}

