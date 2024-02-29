#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
// pthread_mutex_t mutex;

void *routine(void *arg)
{
    int ind;
    int i;
    int sum;

    ind = *(int *)arg;
    i = -1;
    sum = 0;
    while (++i < 5)
        sum += primes[ind + i];
    printf("local sum = %d\n", sum);
    *(int *)arg = sum;
    return (void *)arg;
}

int main()
{
    pthread_t t[10];
    int i;
    int *arg;
    int *res;
    int sum;


    i = -1;
    while (++i < 2)
    {
        arg = malloc(sizeof(int));
        *arg = i * 5;
        if (pthread_create(&t[i], NULL, &routine, arg) != 0)
            return 1;
    }
    i = -1;
    sum = 0;
    while (++i < 2)
    {
        if (pthread_join(t[i], (void **) &res) != 0)
            return 2;
        sum += *(int *)res;
        free(res);
    }
    printf("sum = %d\n", sum);
    
}