#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int x;
    printf("Input number: ");
    scanf("%d", &x); 
    printf("Result: %d * 5 = %d\n", x, x * 5); 
    /*After we stopped the (SIGSTOP) program with CTRL + Z (SIGSTP)
        we type "fg" (SIGCONT) and this is gonna back the main function.*/
    return 0;
}