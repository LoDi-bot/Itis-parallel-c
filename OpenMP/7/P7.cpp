#include "iostream"
#include "omp.h"
#include "chrono"

int main() {
    int a[12], b[12], c[12];
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    for (int i: a) {
        i = rand() % 100;
        printf("%d ", i);
    }
    printf("\n______________________________\n");

#pragma omp parallel for num_threads(3) default(none) shared(a,b) schedule(static, 3)
    for (int i = 0; i < 12; i++) {
        a[i] = i;
        b[i] = i * 2;
        printf("Static area, %d thread of %d threads; a[%d] = %d, b[%d] = %d\n", omp_get_thread_num(), omp_get_num_threads(), i, a[i], i, b[i]);
    }

    printf("\n______________________________________________\n\n");

#pragma omp parallel for num_threads(4) default(none) shared(a, b, c) schedule(dynamic, 4)
    for (int i = 0; i < 12; i++) {
        c[i] = a[i] + b[i];
        printf("Dynamic area, %d thread of %d threads; c[%d] = %d + %d = %d\n", omp_get_thread_num(), omp_get_num_threads(), i, a[i], b[i], c[i]);
    }

    return EXIT_SUCCESS;
}
