#include <unistd.h>
#include <string.h>

#define WELCOME "Welcome to ENSEA shell.\nto exit, press 'exit'.\n"
#define PROMPT "enseash% "

void display_welcome_prompt() {
    write(STDOUT_FILENO, WELCOME, strlen(WELCOME));
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}
