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
    int fd = open("sum", O_RDONLY);
    if (fd == -1)
    {
        return 1;
    }
    int i;
    if (read(fd, arr, sizeof(int) * 5) == -1)
    {
        return 2;
    }
        
    close(fd);
    int sum = 0;
    for (i = 0; i < 5; i++)
    {
        sum += arr[i];
    }

    printf("Result is %d\n", sum);

    int fdSend = open("sum", O_WRONLY);

    if (fdSend == -1)
    {
        return 3;
    }
    printf("Opened the file again...\n");

    if (write(fdSend, &sum, sizeof(int)) == -1)
    {
        return 4;
    }
    printf("Write the sum...\n");
    close(fdSend);
    return 0;
}