#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BYE "Bye bye...\n"

void display_Bye(char *buffer, size_t buf_size) {
    if(strncmp(buffer,"exit",buf_size)==0){
        write(STDOUT_FILENO,BYE,strlen(BYE));
        exit(EXIT_SUCCESS);
    }
}