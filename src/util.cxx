#include <stdio.h>

#include <time.h>
#include <sys/time.h>

#include "util.h"

double what_time_is_it_now() {
    struct timeval time;
    if (gettimeofday(&time,NULL)) {
        return 0;
    }
    
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

void print_mat_array(float* mat, int size) {
    int i, j;
    
    auto start_pos = mat;

    for ( i = 0; i < size; ++i ) {
        for ( j = 0; j < size; ++j )
            printf("%3.1f\t", *(start_pos + j));

        start_pos += size;

        printf("\n");
    }

    printf("\n");
}
