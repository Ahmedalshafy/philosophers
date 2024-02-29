#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
// pthread_mutex_t mutex;

void *routine(void *arg)
{
    printf("prime ind %d = %d\n", *(int *)arg, primes[*(int *)arg]);
    free(arg);
    return NULL;
}

int main()
{
    pthread_t t[10];
    int i;
    int *j;

    i = -1;
    while (++i < 10)
    {
        j = malloc(sizeof(int));
        *j = i;
        if (pthread_create(&t[i], NULL, &routine, j) != 0)
            return 1;
        // free(j); // if we free j here, the thread will not be able to read the value of j
        // in this case (without allcated j here), the address of i is passed to the thread
        // the thread will read the value of i when it starts
        // but the value of i will change before the thread starts
        // so the value of i will be different for each thread
        // to fix this, we can pass the address of a malloced variable
    }
    i = -1;
    while (++i < 10)
    {
        if (pthread_join(t[i], NULL) != 0)
            return 2;
    }
    
}