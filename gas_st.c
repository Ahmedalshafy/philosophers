#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
int gas = 0;

void *filling_st(void*arg)
{
    int i;
    i = -1;
    while (++i < 3)
    {
        pthread_mutex_lock(&mutex);
        gas += 15;
        printf("Filling station: gas = %d\n", gas);
        pthread_mutex_unlock(&mutex);
    }
    return (NULL);
}

void *filling_car(void*arg)
{
    while (1)
    {
        if (gas >= 40)
        {
            pthread_mutex_lock(&mutex);
            gas -= 40;
            printf("Car: gas = %d\n", gas);
            pthread_mutex_unlock(&mutex);
            break;
        }
        else
        {
            printf("Car: not enough gas\n");
            sleep(1);
        }
    }
    // working
    // while (gas < 40)
    // {
    //     sleep(1);
    // }
    // pthread_mutex_lock(&mutex);
    // gas -= 40;
    // printf("Car Filled: gas = %d\n", gas);
    // pthread_mutex_unlock(&mutex);

    // not working
    // if (gas >= 40)
    // {
    //     pthread_mutex_lock(&mutex);
    //     gas -= 40;
    //     printf("Car: gas = %d\n", gas);
    //     pthread_mutex_unlock(&mutex);
    // }
    // else
    //     printf("Car: not enough gas\n");
    return (NULL);
}

int main()
{
    pthread_t t[2];
    int i;

    pthread_mutex_init(&mutex, NULL);
    i = -1;
    while (++i < 2)
    {
        if (i == 0)
        {
            if (pthread_create(&t[i], NULL, &filling_st, NULL) != 0)
                return (1);
        }
        else
        {
            if (pthread_create(&t[i], NULL, &filling_car, NULL) != 0)
                return (1);
        }
    }
    i = -1;
    while (++i < 2)
    {
        if (pthread_join(t[i], NULL) != 0)
            return (2);
    }
    pthread_mutex_destroy(&mutex);
    return (0);
}