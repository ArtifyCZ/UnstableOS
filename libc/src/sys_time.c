#include <sys/time.h>
#include <time.h>


int gettimeofday(struct timeval *restrict tp, void *restrict tzp) {
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) < 0)
        return -1;
    tp->tv_sec = ts.tv_sec;
    tp->tv_usec = ts.tv_nsec/1000;
    return 0;
}