#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int id = fork();
    if (id == 0)
    {
        sleep(1);
    }
    printf("Current id : %d | Parent id: %d \n", getpid(), getppid());
    int res = wait(NULL);
    if (res == -1)
    {
        printf("No clildren to wait for\n");
    }
    else
    {
        printf("%d finished executing\n", res);
    }

    return 0;
}