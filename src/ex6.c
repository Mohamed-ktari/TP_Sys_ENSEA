#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



#define MAX_ARGS 32

void parse_command(char *buffer, char **argv)
{
    int i = 0;

    argv[i] = strtok(buffer, " \t");
    while (argv[i] != NULL && i < MAX_ARGS - 1) {
        i++;
        argv[i] = strtok(NULL, " \t");
    }
}
