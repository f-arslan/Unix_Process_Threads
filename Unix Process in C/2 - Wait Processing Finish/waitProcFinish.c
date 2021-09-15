#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int arg, char *argv[])
{
    int id = fork();
    int n;

    if (id == 0)
    {
        n = 1;
    }
    else
    {
        n = 6;
    }
    if (id != 0)
    {
        wait();
    }
    int i;
    for (i = n; i < n + 5; i++)
    {
        printf("%d ", i);
    }
    if (id != 0)
    {
        printf("\n");
    }
    return 0;
}