#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREADS 4
int mails = 0;
pthread_mutex_t mutex;
void *routine()
{ //*! Get race expected 2m but get 1.4m */
    //*! Race condition fix the problem, but getting slower. */
    for (int i = 0; i < 10000000; i++)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
        //* read mails
        //* increment
        //* write mails
    }
}

int main(int argc, char *argv[])
{
    pthread_t th[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);
    int i;
    for (i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
        {
            return 1;
        }
        printf("Thread %d has started.\n", i);
    } //*! Use two for loop because get avoid from one threads. */
    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            return 2;
        }
        printf("Thread %d has finished execution.\n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
    return 0;
}