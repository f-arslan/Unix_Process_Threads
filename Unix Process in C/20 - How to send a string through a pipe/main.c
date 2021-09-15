#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        return 1;
    }
    int pid = fork();
    if (pid < 0)
    {
        return 2;
    }
    if (pid == 0)
    {
        /* Child process */
        close(fd[0]);
        char str[200];
        printf("Input string: ");
        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = '\0'; /*we need the delete last character.*/
        int n = strlen(str) + 1;
        if (write(fd[1], &n, sizeof(n)) < 0)
        {
            return 4;
        }

        if (write(fd[1], str, sizeof(char) * n) < 0) /*+1 for null terminator*/
        {
            return 3;
        }
        close(fd[1]);
    }
    else
    {
        /*Parent Process*/
        close(fd[1]);
        char str[200];
        int n;
        if (read(fd[0], &n, sizeof(n)) < 0)
        {
            return 5;
        }
        if (read(fd[0], str, sizeof(char) * n) < 0)
        {
            return 6;
        }
        printf("Given string: %s\n", str);
        close(fd[0]);
        wait(NULL);
    }

    return 0;
}