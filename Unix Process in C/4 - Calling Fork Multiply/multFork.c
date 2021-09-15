#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int id1 = fork();
    int id2 = fork();

    if (id1 == 0)
    {
        if (id2 == 0)
        {
            printf("We are process y\n");
            printf("Current Id : %d | Parent Id : %d\n", getpid(), getppid());
        }
        else
        {
            printf("We are process x\n");
            printf("Current Id : %d | Parent Id : %d\n", getpid(), getppid());
        }
    }
    else
    {
        if (id2 == 0)
        {
            printf("We are process z\n");
            printf("Current Id : %d | Parent Id : %d\n", getpid(), getppid());
        }
        else
        {
            printf("We are the parent process\n");
            printf("Current Id : %d | Parent Id : %d\n", getpid(), getppid());
        }
    }
    while (wait(NULL) != -1 || errno != ECHILD)
    {
        // printf("Waited for a child to finish\n");
    }

    return 0;
}