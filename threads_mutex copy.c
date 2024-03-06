#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
    int id;
    pthread_t t;
    int counter;
    pthread_mutex_t mutex;
} t_data;

int counter = 0;
// pthread_mutex_t mutex;

void *routine(void *arg)
{
    // test two the mutex works
    int i;
    printf("test\n");
    t_data data = *(t_data *)arg;
    printf("id = %d\n", data.id);
    i = -1;
    pthread_mutex_lock(&data.mutex);
    while (++i < 1000000)
    {
        
        counter += 1;
    }
    pthread_mutex_unlock(&data.mutex);
    printf("rotin counter = %d\n", counter);
    return NULL;
}

int main()
{
    t_data t[4];
    int i;
    i = -1;
    while (++i < 4)
    {
        if (pthread_mutex_init(&t[i].mutex, NULL) != 0)
            return 1;
    }
    i = -1;
    while (++i < 4)
    {
        t[i].id = i;
        if (pthread_create(&t[i].t, NULL, &routine, &t[i]) != 0)
            return 1;
    }
    i = -1;
    while (++i < 4)
    {
        if (pthread_join(t[i].t, NULL) != 0)
            return 2;
    }

    
}