#pragma once

#include <time.h>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>

inline uint64_t getNanos() {
    timespec start;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    return start.tv_sec*1'000'000'000 + start.tv_nsec;
}