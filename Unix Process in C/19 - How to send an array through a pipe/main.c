#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
/*
    2 process
    1 -> Child process should generate random numbers and send them to the parent
    2 -> Parent is going to sum all the numbers and print the result.
*/

int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        return 2;
    }
    int id = fork();

    if (id == 0)
    { /*Child Process*/
        close(fd[0]);
        srand(time(NULL));
        int arr[10];
        int length = rand() % 10 + 1;
        int i;
        printf("Generated: ");
        for (i = 0; i < length; i++)
        {
            arr[i] = rand() % 11;
            printf("%d ", arr[i]);

        }
        printf("\n");
        /* First send the length. */
        if (write(fd[1], &length, sizeof(int)) < 0)
        {
            return 4;
        }
        printf("Send length: %d\n", length);
        /*After send the array. */
        if (write(fd[1], arr, sizeof(int) * length) < 0)
        {
            return 3;
        }
        printf("Send array\n");
        close(fd[1]);
    }
    else
    { /*Parent process*/
        close(fd[1]);
        int arr[10];
        int length;
        int i, sum = 0;
        if (read(fd[0], &length, sizeof(int)) < 0)
        {
            return 5;
        }
        printf("Received length: %d\n", length);
        if(read(fd[0], arr, sizeof(int) * length) < 0)
        {
            return 6;
        }
        printf("Received array\n");
        for (int i = 0; i < length; i++)
        {
            sum += arr[i];
            printf("%d ", arr[i]);
        }
        printf("\nSum of array: %d\n", sum);
        wait(NULL);
        close(fd[0]);
    }
    return 0;
}