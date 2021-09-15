#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define PROCESS_NUM 3

int main(int argc, char *argv[])
{
    int pids[PROCESS_NUM];
    int pipes[PROCESS_NUM + 1][2];
    int i;
    for (i = 0; i < PROCESS_NUM + 1; i++)
    {
        if (pipe(pipes[i]) < -1)
        {
            printf("Error creating pipe.\n");
            return 1;
        }
    }

    for (i = 0; i < PROCESS_NUM; i++)
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            printf("Error creating fork.\n");
            return 2;
        }
        if (pids[i] == 0) //! Every time getting new parent from child, not gonna enter there
        {                 //* Child Process
            int j;
            for (j = 0; j < PROCESS_NUM + 1; j++)
            {
                if (i != j)
                {
                    close(pipes[j][0]);
                }
                if (i + 1 != j)
                {
                    close(pipes[j][1]);
                }
            }
            int x;
            if (read(pipes[i][0], &x, sizeof(int)) == -1)
            {
                printf("Error at reading.\n");
                return 3;
            }
            printf("(%d) Got %d\n", i, x);

            x++;
            if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
            {
                printf("Error at writing.\n");
                return 4;
            }
            printf("(%d) Sent %d\n", i, x);

            close(pipes[i][0]);
            close(pipes[i + 1][1]);
            return 0;
        }
    }

    //* Main Process
    int j;
    for (j = 0; j < PROCESS_NUM + 1; j++)
    {
        if (j != PROCESS_NUM)
        {
            close(pipes[j][0]);
        }
        if (j != 0)
        {
            close(pipes[j][1]);
        }
    }
    int y = 5;
    printf("Main process sent: %d\n", y);
    if (write(pipes[0][1], &y, sizeof(int)) == -1)
    {
        printf("Error at writing.\n");
        return 4;
    }

    if (read(pipes[PROCESS_NUM][0], &y, sizeof(int)) == -1)
    {
        printf("Error at reading.\n");
        return 5;
    }
    printf("The final result: %d\n", y);

    close(pipes[0][1]);
    close(pipes[PROCESS_NUM][0]);
    for (i = 0; i < PROCESS_NUM; i++)
    {
        wait(NULL);
    }
    close(pipes[i][0]);
    close(pipes[i + 1][1]);
    return 0;
}