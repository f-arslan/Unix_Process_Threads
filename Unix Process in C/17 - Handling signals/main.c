#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void hangle_sigtstp(int sig)
{ /* This function show the message is gonna prevent to CTRL + Z */
    printf(" Stop not allowed.\n");
}
void hangle_sigcont(int sig)
{ 
    printf(" Input number: ");
    fflush(stdout);
}
int main(int argc, char *argv[])
{
    // Way #1
    // struct sigaction sa;
    // sa.sa_handler = &hangle_sigtstp;
    // sa.sa_flags = SA_RESTART;
    // sigaction(SIGTSTP, &sa, NULL);

    struct sigaction sa;
    sa.sa_handler = &hangle_sigcont;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCONT, &sa, NULL);
    // Way #2
    // signal(SIGTSTP, &hangle_sigtstp);

    int x;
    printf("Input number: ");
    scanf("%d", &x);
    printf("Result %d * 5 : %d\n", x, x * 5);
    return 0;
}