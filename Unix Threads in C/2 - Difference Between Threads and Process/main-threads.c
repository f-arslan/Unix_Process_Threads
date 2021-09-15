#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;

void *routine()
{
    x+= 5;
    sleep(2);
    printf("routine 1 Value of x : %d\n", x);
}

void *routine2()
{
    sleep(2);
    printf("routine 2 Value of x : %d\n", x);
}

void *routine3()
{
    sleep(2);
    printf("routine 3 Value of x : %d\n", x);
}
/* Threads share the memory */
int main(int argc, char *argv[])
{
    pthread_t t1, t2, t3;
    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
    {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine2, NULL) != 0)
    {
        return 2;
    }
    if (pthread_create(&t3, NULL, &routine3, NULL) != 0)
    {
        return 3;
    }
    if (pthread_join(t1, NULL) != 0)
    {
        return 4;
    }
    if (pthread_join(t2, NULL) != 0)
    {
        return 5;
    }
    if (pthread_join(t3, NULL) != 0)
    {
        return 6;
    }
    return 0;
}