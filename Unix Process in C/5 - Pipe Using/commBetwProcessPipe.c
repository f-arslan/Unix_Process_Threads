#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd[2];
    // fd[0] - read
    // fd[1] - write
    if (pipe(fd) == -1)
    {
        printf("An error occurred with opening the pipe.\n");
        return 1;
    }
    int id = fork();
    if (id == -1)
    {
        printf("An error occurred with fork.\n");
        return 4;
    }
    if (id == 0)
    {                 /* Child Process */
        close(fd[0]); // Close the pipe read part.
        int x;
        printf("Input a number: ");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(int)) == -1)
        {
            printf("An error occurred with writing to the pipe.\n");
            return 2;
        }
        close(fd[1]);
    }
    else
    {  /* Parent Process */
        close(fd[1]); // Close the write part.
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1)
        {
            printf("An error occurred with reading to the pipe.\n");
            return 3;
        }
        y = y * 3;
        printf("Get from child process * 3 : %d\n", y);
        close(fd[0]);
    }
}