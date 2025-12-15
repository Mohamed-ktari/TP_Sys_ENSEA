#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "../include/ex3.h"
#include "../include/ex4.h"

#define PROMPT "enseash% "
#define CONTINUOUS_PROMPT "enseash "
#define ERROR "Command not found\n"
#define FORK_ERROR "Fork failed\n"
#define PROMPT_SIZE 256

// trim the extra spaces in the end of the string
void rtrim(char *s)
{
    int i = strlen(s) - 1;

    while (i >= 0 && (s[i] == ' ' || s[i] == '\t')) {
        s[i] = '\0';
        i--;
    }
}


void display_regular_prompt(char *buffer, size_t buf_size) {
    __pid_t pid;
    ssize_t len;
    char prompt_buff[PROMPT_SIZE];
    int status;
    char *state_buffer; // add this for ex4

    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
    while (1) {
        
        len = read(STDIN_FILENO, buffer, buf_size);
        buffer[len - 1] = '\0';
        rtrim(buffer);
        display_Bye(buffer,len);  // add this for exercice 3
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
            wait(&status);
            state_buffer=print_status_prompt(status); //add this for ex4

        }
        snprintf(prompt_buff, sizeof(prompt_buff), "%s [%s] %% ",CONTINUOUS_PROMPT, state_buffer); //add this for ex4 to concatenate the prompt
        write(STDOUT_FILENO, prompt_buff, strlen(prompt_buff));
        free(state_buffer);
    }
}

