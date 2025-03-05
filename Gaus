/*
Код написан с целью решения систем уравнения методом гаусса.
В начале введите количество уравнений, затем введите коэффиценты уравнений по одному
и наконец свободные члены уравнений по одному.
*/

#include <iostream>
#include <cstdlib>
#include <utility>

void gauss(double **arrA, double *arrB, const int n);
bool check_input(const int res);
void memory_clear(double **arr, int n);
void memory_clear(double *arr);

int main(void) {
    int n, res;
    double pse;
    printf("Введите количество уравнений: ");
    res = scanf("%d", &n);
    check_input(res) ? exit(1) : (void)0;

    double** arrA = new double*[n];
    double* arrB = new double[n];

    for (int i = 0; i < n; i++) 
        arrA[i] = new double[n];

    printf("Введите элементы матрицы А по одному:\n");
    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++) {
            res = scanf("%lf", &arrA[j][i]);
            check_input(res) ? exit(1) : (void)0;
        }
    
    printf("Введите свободные члены по одному:\n");
    for (int i = 0; i < n; i++) 
        scanf("%lf", &arrB[i]); 

    gauss(arrA, arrB, n);

    memory_clear(arrA, n);
    memory_clear(arrB);

    return 0;
}













































bool check_input(const int res) {
    if (res != 1) {
        printf("Error: Wrong input\n");
        return true;
    }
    return false;
}




void gauss(double **arrA, double *arrB, const int n) {
    for (int i = 0; i < n; i++) {
        double elmax = abs(arrA[i][i]);
        int to = i;

        for (int j = i + 1; j < n; j++) {
            if (abs(arrA[j][i]) > elmax) {
                elmax = abs(arrA[j][i]);
                to = j;
            }
        }

        for (int j = i; j < n; j++ ) 
            std::swap(arrA[to][j], arrA[i][j]);
        std::swap(arrB[to], arrB[i]);

        for (int j = i + 1; j < n; j++) {
            double foo = -arrA[j][i] / arrA[i][i];
            for (int k = i; k < n; k++)
                arrA[j][k] += foo * arrA[i][k];
            arrB[j] += foo * arrB[i];
        }
    }

    double *ans = new double[n];

    for (int i = n - 1; i >= 0; i--) {
        ans[i] = arrB[i];
        for (int j = i + 1; j < n; j++)
            ans[i] -= arrA[i][j] * ans[j];
        ans[i] /= arrA[i][i];
    }

    printf("Система уравнений имеет решения:\n");
    for (int i = 0; i < n; i++)
        printf("x%d = %lf\n", i + 1, ans[i]);

    delete[] ans; 
}

void memory_clear(double **arr, int n) {
    for (int i = 0; i < n; i++)
        delete[] arr[i];
    delete[] arr;
}

void memory_clear(double *arr) {
    delete[] arr;
}
