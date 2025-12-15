#ifndef EX8_H
#define EX8_H



int split_pipe(char *buffer, char **left, char **right);
int execute_pipe(char *left_cmd, char *right_cmd);


#endif