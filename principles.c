#include <stdio.h>
#include <pthread.h>


int *prime = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *rotine(void *arg)
{
    int i;

    while (i < 10)
    {
        printf("%d\n", prime[i]);
        i++;
    }
}

int main()
{
    pthread_t t1[10];
    int i = -1;
    while (++i < 10)
        pthread_create(&t1[i], NULL, rotine, NULL);
    i = -1;
    while (++i < 10)
        pthread_join(t1[i], NULL);
}