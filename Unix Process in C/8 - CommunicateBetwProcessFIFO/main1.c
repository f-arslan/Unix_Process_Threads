#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int arr[5];
    srand(time(NULL));
    int i;
    for (i = 0; i < 5; i++)
    {
        arr[i] = rand() % 10;
        printf("Generated %d\n", arr[i]);
    }

    int fd = open("sum", O_WRONLY);
    if (fd == -1)
    {
        return 1;
    } 

    if (write(fd, arr, sizeof(int) * 5) == -1)
    {
        return 2;
    }        
    close(fd);


    int fdRead = open("sum", O_RDONLY);
    int sum1;
    if (fdRead == -1)
    {
        return 3;
    }
    printf("Open the file for read\n");
    if (read(fdRead, &sum1, sizeof(int)) == -1)
    {
        return 4;
    }
    printf("Readed the file.\n");
    printf("Sum : %d\n", sum1);
    close(fdRead);
    return 0;
}