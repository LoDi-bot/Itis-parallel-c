#include "iostream"
#include "omp.h"
#include "chrono"

int main() {
    int a[30];
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < 30; i++) {
        a[i] = rand() % 100;
//        a[i] = 9;
        printf("%d ", a[i]);
    }
    printf("\n______________________________\n");

    int counter = 0;

#pragma omp parallel for default(none) shared(a, counter) num_threads(4)
    for (int i = 0; i < 30; i++) {
        if (a[i] % 9 == 0) {
#pragma omp atomic
            counter += 1;
        }
    }

    printf("counter = %d", counter);

    return EXIT_SUCCESS;
}
