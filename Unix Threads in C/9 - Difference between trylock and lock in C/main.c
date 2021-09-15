#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
pthread_mutex_t mutex;

void *routine(void *arg)
{
    if (pthread_mutex_trylock(&mutex) == 0)
    {
        printf("Got lock\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    }
    else
    {
        printf("Didn't get lock\n");
    }
}

int main(int argc, char *argv[])
{
    pthread_t th[4];
    for (int i = 0; i < 4; i++)
    {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
        {
            printf("Error at creation of thread\n");
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            printf("Error at join of thread\n");
        }
    }

    return 0;
}