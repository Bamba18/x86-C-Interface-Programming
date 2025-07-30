#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Declare external NASM function (Windows ABI)
extern void compute_acceleration(float* matrix, int rows, int* output);

int main() {
    int rows;
    printf("Enter number of rows (cars): ");
    scanf("%d", &rows);

    float* matrix = malloc(sizeof(float) * rows * 3);
    int* output = malloc(sizeof(int) * rows);

    if (!matrix || !output) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the matrix values (Vi Vf T per line):\n");
    for (int i = 0; i < rows; i++) {
        scanf("%f %f %f", &matrix[i * 3], &matrix[i * 3 + 1], &matrix[i * 3 + 2]);
    }

    printf("\nCalling assembly function...\n");
    compute_acceleration(matrix, rows, output);
    printf("Returned from assembly.\n\n");

    printf("Accelerations (rounded to int, m/s^2):\n");
    for (int i = 0; i < rows; i++) {
        printf("%d\n", output[i]);
    }

    free(matrix);
    free(output);
    return 0;
}
