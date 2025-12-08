#ifndef EX2_H
#define EX2_H
#include <stddef.h> 

#define PROMPT "enseash% "
#define CONTINUOUS_PROMPT "enseah "
#define ERROR "Command not found\n"
#define FORK_ERROR "Fork failed\n"
#define ENDING_STATE 128
#define PROMPT_SIZE 256


void display_regular_prompt(char *buffer, size_t buf_size);

#endif
