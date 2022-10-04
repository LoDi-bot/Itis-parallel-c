#include "iostream"
#include "omp.h"
#include "chrono"

int main() {
    int a[100];
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < 100; i++) {
        a[i] = rand() % 100;
        printf("%d ", a[i]);
    }

    printf("\n______________________________\n");
    int max = -10;

#pragma omp parallel for default(none) shared(a, max) num_threads(4)
    for (int i = 0; i < 100; i++) {
        if (a[i] % 7 == 0 && a[i] > max) {
#pragma omp critical
            {
                if (a[i] > max)
                    max = a[i];
            }
        }
    }

    printf("max = %d\n", max);

    return EXIT_SUCCESS;
}
