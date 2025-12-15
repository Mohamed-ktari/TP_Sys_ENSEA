#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>

#include "../include/ex2.h"
#include "../include/ex3.h"
#include "../include/ex4.h"
#include "../include/ex6.h"





#define PROMPT "enseash% "
#define CONTINUOUS_PROMPT "enseash "
#define ERROR "Command not found\n"
#define FORK_ERROR "Fork failed\n"
#define PROMPT_SIZE 256
#define MAX_ARGS 32



 /* Compute elapsed time in ms */
long time_calculator_in_ms(struct timespec starting_time,struct timespec ending_time){
    return (ending_time.tv_sec - starting_time.tv_sec) * 1000 +(ending_time.tv_nsec - starting_time.tv_nsec) / 1000000;
}

struct timespec starting_time, ending_time;

void display_regular_prompt_with_time_and_state(char *buffer, size_t buf_size)
{
    pid_t pid;
    ssize_t len;
    int status;
    char prompt_buff[PROMPT_SIZE];
    char *state_buffer;

    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

    while (1) {

        
        len = read(STDIN_FILENO, buffer, buf_size);
        buffer[len - 1] = '\0';
        rtrim(buffer);
        display_Bye(buffer, len);

        clock_gettime(CLOCK_MONOTONIC, &starting_time);

        pid = fork();
        if (pid < 0) {
            write(STDERR_FILENO, FORK_ERROR, strlen(FORK_ERROR));
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            char *argv[MAX_ARGS];
            parse_command(buffer, argv);
            handle_redirection(argv);
            execvp(argv[0], argv);
            write(STDERR_FILENO, ERROR, strlen(ERROR));
            exit(EXIT_FAILURE);
        }

        waitpid(pid, &status, 0);
        clock_gettime(CLOCK_MONOTONIC, &ending_time);
        state_buffer=print_status_prompt(status);
        /* Compute elapsed time in ms */
        long time_ms = time_calculator_in_ms(starting_time,ending_time);


        /* Build final prompt */
        snprintf(prompt_buff, sizeof(prompt_buff),"%s [%s|%ldms] %% ",CONTINUOUS_PROMPT,state_buffer, time_ms);
        free(state_buffer);

        write(STDOUT_FILENO, prompt_buff, strlen(prompt_buff));
    }
}



