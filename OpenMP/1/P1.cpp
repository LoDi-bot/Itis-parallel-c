#include "iostream"
#include "omp.h"

int main() {

#pragma omp parallel default(none) num_threads(8)
    printf("Hello World, from thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());

    return EXIT_SUCCESS;
}