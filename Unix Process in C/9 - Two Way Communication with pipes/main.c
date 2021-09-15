#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char *argv[])
{
    // Guarantead the communication.
    // 5 => 5 * 4 = 20 => 20
    int p1[2]; // Child to parent write
    int p2[2]; // Parent to child write

    if (pipe(p1) == -1)
    {
        return 1;
    }
    if (pipe(p2) == -1)
    {
        return 1;
    }
    printf("Pipes were created.\n");

    int pid = fork();
    if (pid == -1)
    {
        return 2;
    }
    printf("Fork was successful.\n");
    if (pid == 0)
    { // Child Process
        close(p1[0]);
        close(p2[1]);

        int x;
        if (read(p2[0], &x, sizeof(x)) == -1)
        {
            return 3;
        }
        printf("Read from child process completed. Number : %d\n", x);
        x *= 4;
        if (write(p1[1], &x, sizeof(x)) == -1)
        {
            return 4;
        }
        printf("Write from child process completed. Number : %d\n", x);
        close(p1[1]);
        close(p2[0]);
    }
    else
    { // Parent Process
        close(p1[1]);
        close(p2[0]);
        srand(time(NULL));
        int y = rand() % 10;
        if (write(p2[1], &y, sizeof(y)) == -1)
        {
            return 5;
        }
        /*This is why we use 2 pipe instead of 1.*/
        // printf("Write from parent process completed. Number : %d\n", y);
        if (read(p1[0], &y, sizeof(y)) == -1)
        {
            return 6;
        }
        printf("Read from parent process completed. Number : %d\n", y);
        close(p1[0]);
        close(p2[1]);
        wait(NULL);
    }

    return 0;
}