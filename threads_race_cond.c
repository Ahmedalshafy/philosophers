#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter = 0;

void *routine(void *arg)
{
    int i;  

    i = -1;
    while (++i < 1000000)
        counter += 1;
    // what happen here
    // read counter
    // increment counter
    // write counter on memory
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
    printf("counter = %d\n", counter);
    
}