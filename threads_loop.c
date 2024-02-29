#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t mutex;

void *routine(void *arg)
{
    int i;  

    i = -1;
    while (++i < 1000000)
    {
        pthread_mutex_lock(&mutex);
        counter += 1;
        pthread_mutex_unlock(&mutex);
    }
    // printf("rotin counter = %d\n", counter);
    return NULL;
}

int main()
{
    pthread_t t[100];
    int i;

    if (pthread_mutex_init(&mutex, NULL) != 0)
        return 1;
    i = -1;
    while (++i < 100)
    {
        if (pthread_create(&t[i], NULL, &routine, NULL) != 0)
            return 1;
        printf("thread %d created\n", i);
    }
    i = -1;
    while (++i < 100)
    {
        if (pthread_join(t[i], NULL) != 0)
            return 2;
        printf("thread %d joined\n", i);
    }
    printf("counter = %d\n", counter);
    pthread_mutex_destroy(&mutex);    
}