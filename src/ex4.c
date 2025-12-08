#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define MAX_SIZE 64
#define NUM_SIZE 16

char* print_status_prompt(int status) {
    char *buff = malloc(MAX_SIZE);
    char num[16];

    if (!buff) return NULL;

    if (WIFEXITED(status)) {
        snprintf(num, sizeof(num), "%d", WEXITSTATUS(status));
        snprintf(buff, MAX_SIZE, " [exit:%s] %% ", num);  // %% → un % 
    } else if (WIFSIGNALED(status)) {
        snprintf(num, sizeof(num), "%d", WTERMSIG(status));
        snprintf(buff, MAX_SIZE, " [sign:%s] %% ", num);  // %% → un %
    } else {
        snprintf(buff, MAX_SIZE, " [unknown] %% ");
    }

    return buff;  
}
