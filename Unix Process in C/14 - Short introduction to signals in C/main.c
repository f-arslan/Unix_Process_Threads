#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0)
    {
        while (1)
        {
            printf("Some text goes here.\n");
            usleep(100000);        
        }
    }
    else
    {   
        sleep(1);
        kill(pid, SIGKILL);
        wait(NULL);
    }
}