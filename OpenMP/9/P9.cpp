#include "iostream"
#include "omp.h"
#include "chrono"


int main() {
    int n = 100;
    int matrix[n][n];
    int vector[n];
    int parallelAnswer[n];
    int answer[n];
    int sum = 0;

    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < n; i++) {
        vector[i] = rand();
        for (int j = 0; j < n; j++)
            matrix[i][j] = rand();
    }


    auto start_time = std::chrono::high_resolution_clock::now();
#pragma omp parallel for default(none) shared(n, matrix, vector, parallelAnswer) schedule(guided, 100) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            sum += matrix[i][j] * vector[j];
        parallelAnswer[i] = sum;
        sum = 0;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    printf("Paralleled work took %lld microseconds\n", duration.count());


    start_time = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            sum = matrix[i][j] * vector[j];
        answer[i] = sum;
        sum = 0;
    }

    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    printf("Non paralleled work took %lld microseconds \n", duration.count());



//    int a[16000];
//    double b[16000];
//    int chunk_size = 100;
//
//    for (int i = 0; i < 16000; i++) {
//        a[i] = i;
//        printf("%d ", i);
//    }
//    printf("\n_________________________________________\n");
//
//
//
//
//    auto start_time = std::chrono::high_resolution_clock::now();
//#pragma omp parallel for num_threads(8) default(none) shared(a, b, chunk_size) schedule(static, chunk_size)
//    for (int i = 1; i < 15999; i++)
//        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
//
//    auto end_time = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//
//    printf("Static scheduler, duration = %lld microseconds\n", duration.count());
//
//
//
//
//    start_time = std::chrono::high_resolution_clock::now();
//#pragma omp parallel for  num_threads(8) default(none) shared(a, b, chunk_size) schedule(dynamic, chunk_size)
//    for (int i = 1; i < 15999; i++)
//        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
//
//    end_time = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//
//    printf("Dynamic scheduler, time = %lld microseconds\n", duration.count());
//
//
//
//
//    start_time = std::chrono::high_resolution_clock::now();
//#pragma omp parallel for  num_threads(8) default(none) shared(a, b, chunk_size) schedule(guided, chunk_size)
//    for (int i = 1; i < 15999; i++)
//        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
//
//    end_time = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//
//    printf("Guided scheduler, time = %lld microseconds\n", duration.count());
//
//
//
//
//    start_time = std::chrono::high_resolution_clock::now();
//#pragma omp parallel for  num_threads(8) default(none) shared(a, b, chunk_size) schedule(auto)
//    for (int i = 1; i < 15999; i++)
//        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
//
//    end_time = std::chrono::high_resolution_clock::now();
//    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
//
//    printf("Auto scheduler, time = %lld microseconds\n", duration.count());

    return EXIT_SUCCESS;
}
