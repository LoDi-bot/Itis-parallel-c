#include "iostream"
#include "omp.h"

int main() {
    int a = 100;
    int b = 100;

    printf("before 1st area: a = %d, b = %d\n", a, b);

#pragma omp parallel default(none) num_threads(2) private(a) firstprivate(b)
    {
        a = 100;
        int threadNumber = omp_get_thread_num();

        a += threadNumber;
        b += threadNumber;

        printf("In 1st area: thread %d, a = %d, b = %d\n", threadNumber, a, b);
    }

    printf("After 1st area: a = %d, b = %d\n", a, b);

    printf("********************************************\n");

    printf("Before 2nd area: a = %d, b = %d\n", a, b);

#pragma omp parallel default(none) num_threads(4) shared(a) private(b)
    {
        b = 100;
        int threadNumber = omp_get_thread_num();

        a -= threadNumber;
        b -= threadNumber;

        printf("In 2nd area: thread %d, a = %d, b = %d\n", threadNumber, a, b);
    }

    printf("After 2nd area: a = %d, b = %d\n", a, b);



    return EXIT_SUCCESS;
}