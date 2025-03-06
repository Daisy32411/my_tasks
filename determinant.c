/*
Программа вычисляет определитель матрицы.
В начале вводится порядок матрицы, затем ее элементы по одному.
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double t = 2.0;

void replacing_lines(double **matrix, int i, int size);

int main(void) {
    int size, res;

    // SIZE
    res = scanf("%d", &size);
    if (res != 1) {
        printf("Error: Wrong input\n");
        exit(1);
    }

    // LINES
    double **matrix = malloc(size * sizeof(double *));
    if (matrix == 0) {
        printf("Error: Memory allocation failed 'matrix'\n");
        exit(1);   
    }
    
    // COLUMNS
    for (int i = 0; i < size; i++) {
        matrix[i] = malloc(size * sizeof(double));
    }

    // filling in the matrix
    double element;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            scanf("%lf", &element);
            matrix[i][j] = element;
        }

    for (int i = 0; i < size; i++) {
        if (matrix[i][i] == 0) {
            replacing_lines(matrix, i, size);
        }
    }

    double sum = 1;
    // reduction to a triangular shape
    for(int i = 0; i < (size - 1); i++) {
        for (int j = 0; j < (size - 1 - i); j++) {
            if (matrix[i][i] == 0) 
                replacing_lines(matrix, i, size);
                
            if (matrix[j + 1 + i][i] != 0) {
                double first = matrix[i][i];
                double second = matrix[j + 1 + i][i];
                for (int n = 0; n < size; n++) 
                    matrix[j + 1 + i][n] = (matrix[j + 1 + i][n] - (matrix[i][n] * second / first));
            }
        }
    }

    for (int i = 0; i < size; i++) 
        sum *= matrix[i][i];
    for (int i = t; t != 0; t--)
        sum *= -1.0;
    printf("%d\n",(int) (ceil(sum)));

    // free matrix
    for (int i = 0; i < size; i++) 
        free(matrix[i]);
    free(matrix);

    return 0;
}

void replacing_lines(double **matrix, int i, int size) {
    int k = i + 1;
    while (k < size && matrix[k][i] == 0)
        k++;

    if (k < size) { 
        double *tmp = matrix[i];
        matrix[i] = matrix[k];
        matrix[k] = tmp;
        t = t + 1.0;
    } 
}

/*    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%lf ", matrix[i][j]);
        printf("\n");
    }
*/
