#ifndef EX5_H
#define EX5_H
#include <stddef.h> 

extern struct timespec starting_time, ending_time;

long time_calculator_in_ms(struct timespec starting_time,struct timespec ending_time);
void display_regular_prompt_with_time_and_state(char *buffer, size_t buf_size);


#endif
