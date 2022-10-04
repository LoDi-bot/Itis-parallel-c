#include "iostream"
#include "omp.h"
#include "chrono"


int main() {
    int a[16000];
    double b[16000];
    int chunk_size = 100;

    for (int i = 0; i < 16000; i++) {
        a[i] = i;
        printf("%d ", i);
    }
    printf("\n_________________________________________\n");




    auto start_time = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(8) default(none) shared(a, b, chunk_size) schedule(static, chunk_size)
    for (int i = 1; i < 15999; i++)
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    printf("Static scheduler, duration = %lld microseconds\n", duration.count());




    start_time = std::chrono::high_resolution_clock::now();
#pragma omp parallel for  num_threads(8) default(none) shared(a, b, chunk_size) schedule(dynamic, chunk_size)
    for (int i = 1; i < 15999; i++)
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;

    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    printf("Dynamic scheduler, time = %lld microseconds\n", duration.count());




    start_time = std::chrono::high_resolution_clock::now();
#pragma omp parallel for  num_threads(8) default(none) shared(a, b, chunk_size) schedule(guided, chunk_size)
    for (int i = 1; i < 15999; i++)
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;

    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    printf("Guided scheduler, time = %lld microseconds\n", duration.count());




    start_time = std::chrono::high_resolution_clock::now();
#pragma omp parallel for  num_threads(8) default(none) shared(a, b, chunk_size) schedule(auto)
    for (int i = 1; i < 15999; i++)
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;

    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    printf("Auto scheduler, time = %lld microseconds\n", duration.count());

    return EXIT_SUCCESS;
}
