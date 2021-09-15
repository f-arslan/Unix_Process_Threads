#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (mkfifo("myfifo1", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Could not create fifo\n");
            return 1;
        }
    }
    printf("Opening...\n");

    /* O_WRONLY -> is gonna wait for open with another command like cat myfifo1 */
    int fd = open("myfifo1", O_WRONLY); 
    if (fd == -1)
    {
        return 3;
    }
    printf("Opened...\n");
    int x = 'Z';
    if (write(fd, &x, sizeof(int)) == -1)
    {
        return 2;
    }
    printf("Writing...\n");
    close(fd);
    printf("Closed...\n");

    return 0;
}