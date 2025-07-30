#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


extern void compute_acceleration(float* matrix, int rows, int* output);

void run_test(int rows) {
    float* matrix = malloc(sizeof(float) * rows * 3);
    int* output = malloc(sizeof(int) * rows);

    if (!matrix || !output) {
        printf("Memory allocation failed for Y = %d\n", rows);
        return;
    }

    // random test values
    for (int i = 0; i < rows; i++) {
        float Vi = rand() % 150;
        float Vf = Vi + (rand() % 100); // ensure Vf >= Vi
        float T = 1.0f + (rand() % 10); // avoid divide-by-zero

        matrix[i * 3 + 0] = Vi;
        matrix[i * 3 + 1] = Vf;
        matrix[i * 3 + 2] = T;
    }

    // function 30 times
    double total_time = 0.0;
    for (int i = 0; i < 30; i++) {
        clock_t start = clock();
        compute_acceleration(matrix, rows, output);
        clock_t end = clock();

        total_time += (double)(end - start) / CLOCKS_PER_SEC;
    }

    double avg_time = total_time / 30.0;
    printf("Y = %-5d | Average time over 30 runs: %.6f sec\n", rows, avg_time);

    // Checking correctness of first 5 outputs
    printf("Sample output (first 5): ");
    for (int i = 0; i < (rows < 5 ? rows : 5); i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    free(matrix);
    free(output);
}

int main() {
    srand(time(NULL));

    int sizes[] = { 10, 100, 1000, 10000 };
    int count = sizeof(sizes) / sizeof(sizes[0]);

    printf("== Acceleration Performance Test ==\n");
    for (int i = 0; i < count; i++) {
        run_test(sizes[i]);
    }

    return 0;
}
