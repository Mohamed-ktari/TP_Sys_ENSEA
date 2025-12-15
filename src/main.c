#include "../include/ex1.h"
#include "../include/ex2.h"
#include "../include/ex3.h"
#include "../include/ex5.h"

#define Max_SIZE 512

int main() {
    char buffer[Max_SIZE];
    display_welcome_prompt();
    //display_regular_prompt(buffer , Max_SIZE); //ex2 , ex3 , ex4
    display_regular_prompt_with_time_and_state(buffer,Max_SIZE); //ex5 , ex6, ex7, ex8
    return 0;
}
