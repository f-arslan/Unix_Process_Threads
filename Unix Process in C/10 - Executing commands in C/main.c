#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pid = fork();
    if (pid == -1)
    {
        return 1;
    }
    if(pid == 0)
    { // Child process
        execlp("ping", "ping", "-c", "3", "google.com", NULL);
        printf("THIS SHOULD NOT PRINT ON THE TERMINAL!\n");
    }
    else
    {//Parent process
        wait(NULL);
        printf("Success!\n");
        printf("Some post processing here!\n");

    }
    return 0;
}