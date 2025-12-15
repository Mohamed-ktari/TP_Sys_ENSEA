#ifndef EX9_H
#define EX9_H
#include <sys/types.h> 

#define MAX_BACKGROUND_PROCESS 32

void add_bg_process(pid_t pid, const char *cmd, struct timespec start);
void check_background_processes(void);
int is_background(char **argv);
void display_regular_prompt_with_time_and_state_while_handling_background_process(char *buffer, size_t buf_size);



#endif