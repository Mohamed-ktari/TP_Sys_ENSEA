#include "../include/ex1.h"
#include "../include/ex2.h"

#define Max_SIZE 512

int main() {
    char buffer[Max_SIZE];
    display_welcome_prompt();
    display_regular_prompt(buffer , Max_SIZE);
    return 0;
}
