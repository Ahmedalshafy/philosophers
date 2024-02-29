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
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    pthread_t t4;

    if (pthread_mutex_init(&mutex, NULL) != 0)
        return 1;
    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
        return 1;
    if (pthread_create(&t2, NULL, &routine, NULL) != 0)
        return 1;
    if (pthread_create(&t3, NULL, &routine, NULL) != 0)
        return 1;
    if (pthread_create(&t4, NULL, &routine, NULL) != 0)
        return 1;
    if (pthread_join(t1, NULL) != 0)
        return 2;
    if (pthread_join(t2, NULL) != 0)
        return 2;
    if (pthread_join(t3, NULL) != 0)    
        return 2;
    if (pthread_join(t4, NULL) != 0)    
        return 2;
    printf("counter = %d\n", counter);
    pthread_mutex_destroy(&mutex);    
}