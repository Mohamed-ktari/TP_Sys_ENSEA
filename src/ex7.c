
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define ACCESS_MODE 0644

void handle_redirection(char **argv)
{
    for (int i = 0; argv[i] != NULL; i++) {

        /* Output redirection */
        if (strcmp(argv[i], ">") == 0) {
            int fd = open(argv[i + 1],
                          O_WRONLY | O_CREAT | O_TRUNC,
                          ACCESS_MODE);
            if (fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);

            argv[i] = NULL;   
        }

        /* Input redirection */
        else if (strcmp(argv[i], "<") == 0) {
            int fd = open(argv[i + 1], O_RDONLY);
            if (fd < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            dup2(fd, STDIN_FILENO);
            close(fd);

            argv[i] = NULL;
        }
    }
}
