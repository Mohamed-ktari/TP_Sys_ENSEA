#ifndef EX2_H
#define EX2_H
#include <stddef.h> 

#define PROMPT "enseash% "
#define CONTINUOUS_PROMPT "enseash "
#define ERROR "Command not found\n"
#define FORK_ERROR "Fork failed\n"
#define PROMPT_SIZE 256


void display_regular_prompt(char *buffer, size_t buf_size);
void rtrim(char *s);

#endif
