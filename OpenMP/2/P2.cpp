#include "iostream"
#include "omp.h"

int main() {
    int val1 = 3;
    int val2 = 2;

#pragma omp parallel default(none) shared(val1) if (val1 > 2) num_threads(val1)
    printf("1st area, val = %d, %d thread of %d threads\n", val1, omp_get_thread_num(), omp_get_num_threads());

#pragma omp parallel default(none) shared(val2) if (val2 > 2) num_threads(val2)
    printf("2nd area, val = %d, %d thread of %d threads\n", val2, omp_get_thread_num(), omp_get_num_threads());

    return EXIT_SUCCESS;
}