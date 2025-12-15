#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/resource.h>
#include <fcntl.h>


#include "../include/ex2.h"
#include "../include/ex3.h"
#include "../include/ex4.h"
#include "../include/ex5.h"
#include "../include/ex6.h"
#include "../include/ex7.h"
#include "../include/ex8.h"

#define MAX_BG 32

typedef struct {
    int job_id;
    pid_t pid;
    char command[256];
    struct timespec start_time;
    int active;
} bg_process_t;

bg_process_t bg_list[MAX_BG];
int bg_count = 0;
int next_job_id = 1;


void add_bg_process(pid_t pid, const char *cmd, struct timespec start)
{
    for (int i = 0; i < MAX_BG; i++) {
        if (!bg_list[i].active) {
            bg_list[i].job_id = next_job_id++;
            bg_list[i].pid = pid;
            strncpy(bg_list[i].command, cmd, sizeof(bg_list[i].command) - 1);
            bg_list[i].start_time = start;
            bg_list[i].active = 1;

            printf("[%d] %d\n", bg_list[i].job_id, pid);
            return;
        }
    }
}

void check_background_processes(void)
{
    int status;
    struct rusage usage;
    struct timespec end;

    for (int i = 0; i < MAX_BG; i++) {
        if (!bg_list[i].active)
            continue;

        pid_t ret = wait4(bg_list[i].pid, &status, WNOHANG, &usage);
        if (ret > 0) {
            clock_gettime(CLOCK_MONOTONIC, &end);

            long ms = time_calculator_in_ms(bg_list[i].start_time, end);

            printf("[%d]+ Ended: %s [%ldms]\n",
                   bg_list[i].job_id,
                   bg_list[i].command,
                   ms);

            bg_list[i].active = 0;
        }
    }
}

int is_background(char **argv)
{
    
    int i = 0;
    
    while (argv[i]) i++;

    if (i > 0 && strcmp(argv[i - 1], "&") == 0) {
        argv[i - 1] = NULL;
        return 1;
    }
    return 0;
}




void display_regular_prompt_with_time_and_state_while_handling_background_process(char *buffer, size_t buf_size)
{
    pid_t pid;
    ssize_t len;
    int status;
    char prompt_buff[PROMPT_SIZE];
    char *state_buffer;
    char *left, *right;
    char *argv[MAX_ARGS];

    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

    while (1) {

    check_background_processes();

    len = read(STDIN_FILENO, buffer, buf_size);
    buffer[len - 1] = '\0';
    rtrim(buffer);
    display_Bye(buffer, len);
    parse_command(buffer,argv);
    int is_bg = is_background(argv);

    if (split_pipe(buffer, &left, &right)) {
        // execute pipe
        clock_gettime(CLOCK_MONOTONIC, &starting_time);
        status = execute_pipe(left, right);
        clock_gettime(CLOCK_MONOTONIC, &ending_time);
        }
            
        else{   // single-command execution

        clock_gettime(CLOCK_MONOTONIC, &starting_time);
        pid = fork();
        if (pid < 0) {
            write(STDERR_FILENO, FORK_ERROR, strlen(FORK_ERROR));
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            char *argv[MAX_ARGS];
            handle_redirection(argv);
            execvp(argv[0], argv);
            write(STDERR_FILENO, ERROR, strlen(ERROR));
            exit(EXIT_FAILURE);
        }
        if (is_bg) {
            add_bg_process(pid, buffer, starting_time);
            state_buffer = strdup("1&");
        }
        else{
        waitpid(pid, &status, 0);
        clock_gettime(CLOCK_MONOTONIC, &ending_time);
        }
    }
        
        //compute time in ms
        long time_ms = 0;

        if (!is_bg) {
            time_ms = time_calculator_in_ms(starting_time, ending_time);
        }
        state_buffer=print_status_prompt(status);

        /* Build final prompt */
        snprintf(prompt_buff, sizeof(prompt_buff),"%s [%s|%ldms] %% ",CONTINUOUS_PROMPT,state_buffer, time_ms);
        free(state_buffer);
        write(STDOUT_FILENO, prompt_buff, strlen(prompt_buff));
    }
}
