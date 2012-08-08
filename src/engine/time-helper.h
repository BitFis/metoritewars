/* 
 * File:   tie.h
 * Author: zurcherl
 *
 * Created on 19. Juli 2012, 13:31
 */

#ifndef TIME_HELPER_H
#define	TIME_HELPER_H

#ifdef __cplusplus

extern "C" {
#endif
    
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

// mac ?
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

// windows?
#ifdef _WIN32
// we need windows.h to implement clock_gettime on windows
#include <windows.h>

// this may not be defined on windows
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 15 /* most random value evarr! */
#endif

// the timespec structure is not available on windows
struct timespec {
    time_t tv_sec;
    unsigned long tv_nsec;
};

#endif /* _WIN32 */

double timeval_diff(struct timespec* tv1, struct timespec* tv2);
void current_utc_time(struct timespec *ts);

#ifdef __cplusplus
}
#endif
#endif	/* TIME-HELPER_H */

