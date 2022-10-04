#include "iostream"
#include "omp.h"
#include "chrono"

int main() {
    int a[100];
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    for (int i: a) {
        i = rand() % 100;
        printf("%d ", i);
    }
    printf("\n______________________________\n");

    int sum1 = 0, sum2 = 0, test_sum = 0;

#pragma omp parallel for default(none) shared(a, sum1)
    for (int i = 0; i < 100; i++) {
        sum1 += i;
    }
    printf("sum1 parallel for without reduction = %d\n", sum1 / 100);

#pragma omp parallel for default(none) shared(a) reduction(+:sum2)
    for (int i = 0; i < 100; i++) {
        sum2 += i;
    }
    printf("sum2 parallel for with reduction = %d\n", sum2 / 100);

    for (int i = 0; i < 100; i++) {
        test_sum += i;
    }
    printf("test_sum without parallel for = %d\n", test_sum / 100);
    return EXIT_SUCCESS;
}
