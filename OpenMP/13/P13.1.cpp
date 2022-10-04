#include "iostream"
#include "omp.h"
#include <chrono>
#include <thread>

int main() {

#pragma omp parallel num_threads(8) default(none)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / (omp_get_thread_num() + 1)));
        printf("Hello World, from thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    return EXIT_SUCCESS;
}
