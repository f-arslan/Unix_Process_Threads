#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int id = fork();
    if (id != 0)
    { /*Main process.*/
        fork();
    }
        
    printf("Hello World\n");

    return 0;
}