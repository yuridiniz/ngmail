#include "platform/thread.h"
#include <unistd.h>

#ifndef _WIN32 

unsigned int pcthread_get_num_procs()
{
    return (unsigned int)sysconf(_SC_NPROCESSORS_ONLN);
}

void ms_to_timespec(struct timespec *ts, unsigned int ms)
{
    if (ts == NULL)
        return;
    ts->tv_sec = (ms / 1000) + time(NULL);
    ts->tv_nsec = (ms % 1000) * 1000000;
}

#endif