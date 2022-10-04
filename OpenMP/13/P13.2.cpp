#include "iostream"
#include "omp.h"
#include <thread>

int main() {

#pragma omp parallel num_threads(8) default(none)
    for (int i = 7; i >= 0; i--) {
#pragma omp barrier
        {
            if (omp_get_thread_num() == i) {
                printf("Hello World, from thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
            }
        }
    }

    return EXIT_SUCCESS;
}
