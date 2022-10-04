#include "iostream"
#include "omp.h"
#include "chrono"

int main() {
    int d[6][8];
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    for (auto &i: d) {
        for (int &j: i) {
            j = rand() % 10;
            printf("%d ", j);
        }
        printf("\n");
    }

#pragma omp parallel sections default(none) shared(d) num_threads(3)
    {
#pragma omp section
        {
            int sum = 0;

            for (auto &i: d) {
                for (int &j: i) {
                    sum += j;
                }
            }
            printf("1st section, thread - %d, average number = %d \n", omp_get_thread_num(), sum / 48);
        }
#pragma omp section
        {
            int min = 100;
            int max = -100;

            for (auto &i: d) {
                for (int &j: i) {
                    if (j < min)
                        min = j;
                    if (j > max)
                        max = j;
                }
            }
            printf("2nd section, thread - %d, min = %d, max = %d  \n", omp_get_thread_num(), min, max);
        }
#pragma omp section
        {
            int counter = 0;

            for (auto &i: d) {
                for (int &j: i) {
                    if (j % 3 == 0)
                        counter++;
                }
            }
            printf("3th section, thread - %d, counter = %d  \n", omp_get_thread_num(), counter);
        }
    }

    return EXIT_SUCCESS;
}
