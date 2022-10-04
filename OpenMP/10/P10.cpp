#include "iostream"
#include "omp.h"
#include "chrono"

int main() {
    int d[6][8];
    srand(std::chrono::steady_clock::now().time_since_epoch().count());

    for (auto &i: d) {
        for (int &j: i) {
            j = rand() % 100;
            printf("%d ", j);
        }
        printf("\n");
    }

    int min = 1000, max = -1000;

#pragma omp parallel for default(none) shared(d, min, max) num_threads(4)
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {

            if (d[i][j] < min)
#pragma omp critical
            {
                if (d[i][j] < min)
                    min = d[i][j];
            }


            if (d[i][j] > max)
#pragma omp critical
            {
                if (d[i][j] > max)
                    max = d[i][j];
            }

        }
    }

    printf("max = %d, min = %d", max, min);

    return EXIT_SUCCESS;
}
