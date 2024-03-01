#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval currentTime;

    // Get the current time
    gettimeofday(&currentTime, NULL);

    // Print the time in seconds and microseconds
    printf("Seconds: %ld\n", currentTime.tv_sec);
    printf("Microseconds: %ld\n", currentTime.tv_usec);

    return 0;
}
