#ifndef EX9_H
#define EX9_H
#include <sys/types.h> 


void add_bg_process(pid_t pid, const char *cmd, struct timespec start);
void check_background_processes(void);
int is_background(char **argv);



#endif