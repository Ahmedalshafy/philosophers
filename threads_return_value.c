#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> 

void *roll_dice()
{
    // int value;

    // value = rand() % 6 + 1;
    // printf("value = %d\n", value);
    // return ((void *) &value);
    /* in this case, the value is a local variable,
     so it will be destroyed when the function ends */
    /* to fix this, we can use malloc */

    int value;
    int *result;

    value = rand() % 6 + 1;
    result = malloc(sizeof(int));
    *result = value;
    printf("value = %d\n", value);
    printf("value add = %p\n", &value);
    printf("result add = %p\n", result);
    return ((void *) result);
}

int main()
{
    pthread_t t1;
    int *result;
    srand(time(NULL)); // seed the random number generator

    if (pthread_create(&t1, NULL, &roll_dice, NULL) != 0)
        return 1;
    if (pthread_join(t1, (void **) &result) != 0)
        return 2;
    printf("result = %d\n", *result);
    printf("result add = %p\n", result);
    free(result);
    // the result is a allocted in another function & and its not good
    // to allocate memory in one function and free it in another
}