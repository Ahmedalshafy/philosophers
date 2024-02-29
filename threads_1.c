#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *routine(void *arg)
{
    printf("hello from thread\n");
    sleep(1);
    printf("goodbye from thread\n");
    return NULL;
}

int main()
{
    pthread_t t1;
    pthread_t t2;

    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
        return 1;
    if (pthread_create(&t2, NULL, &routine, NULL) != 0)
        return 1;
    if (pthread_join(t1, NULL) != 0)
        return 2;
    if (pthread_join(t2, NULL) != 0)
        return 2;
    sleep(1);
    printf("hello from main\n");
    
}