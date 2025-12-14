#ifndef EX5_H
#define EX5_H
#include <stddef.h> 


#define PROMPT "enseash% "
#define CONTINUOUS_PROMPT "enseash "
#define ERROR "Command not found\n"
#define FORK_ERROR "Fork failed\n"
#define PROMPT_SIZE 256

void display_regular_prompt_with_time_and_state(char *buffer, size_t buf_size);

#endif
