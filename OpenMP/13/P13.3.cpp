#include "iostream"
#include "omp.h"
#include <thread>

int main() {

    int thread = 7;

#pragma omp parallel num_threads(8) default(none) shared(thread)
    {
        for (int i = 0; i < 100000000/ (omp_get_thread_num() * omp_get_thread_num() * omp_get_thread_num() + 1); i++){

        }
        printf("Hello World, from thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    return EXIT_SUCCESS;
}
