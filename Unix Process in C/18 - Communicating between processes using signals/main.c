#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
int x;
void handle_sigusr1()
{
    if(x == 0)
    {
    printf("\n(HINT) Remember that multiple is reptetive addition!\n");
    }
}

int main(int argc, char *argv[])
{
    int pid = fork();
    if (pid == -1)
    {
        return 1;
    }
    if (pid == 0)
    { /* Child Process */
        sleep(5);
        kill(getppid(), SIGUSR1);
    }
    else
    { /* Parent Process */
        struct sigaction sa = {0};
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);

        printf("What is the result of 3 x 5: ");
        scanf("%d", &x);
        if (x == 15)
        {
            printf("Right.\n");
        }
        else
        {
            printf("Wrong!\n");
        }
        wait(NULL); /*wait the finish child process*/
    }
    return 0;
}