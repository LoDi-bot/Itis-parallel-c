#include "iostream"
#include "omp.h"

int main() {
    int a[] = {34, 54, 73, 69, 15, 353, 3, 56, 95, 63};
    int b[] = {94, 15, 834, 543, 644, 9, 9235, 8563, 926, 763};

    int a_min = INT32_MAX;
    int b_max = INT32_MIN;
    printf("min = %d, max = %d\n", a_min, b_max);


#pragma omp parallel num_threads(2) default(none) shared(a, b, a_min, b_max)
    {
        int thread_num = omp_get_thread_num();

        if (thread_num == 0) {
            for (int number: a) {
                if (number < a_min) {
                    a_min = number;
                }
            }
        }

        if (thread_num == 1) {
            for (int number: b) {
                if (number > b_max) {
                    b_max = number;
                }
            }
        }

        printf("From thread %d after work is done: current a_min = %d, b_max = %d\n", thread_num, a_min, b_max);
    }

    return EXIT_SUCCESS;
}