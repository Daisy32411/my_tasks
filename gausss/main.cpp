/*
Код написан с целью решения систем уравнения методом гаусса.
В начале введите количество уравнений, затем введите коэффиценты уравнений по одному
и наконец свободные члены уравнений по одному.
*/

#include <iostream>
#include <cstdlib>
#include <utility>
#include <cmath>

bool check_input(const int res);

class Mas {
public:
    void inputMas(Mas& B, int n) {    
        printf("Введите свободные члены по одному:\n");
            for (int i = 0; i < n; i++) 
                scanf("%lf", &B.element(i));
    }

    Mas(int size) {
        _size = size;

        top = new double[_size];
        if (top == nullptr) {
            perror("Error: Memory allocation falied\n");
            exit(1);
        }
    }

    ~Mas() {
        delete[] top;
    }

    double& element(int n) {
        if (n >= 0 && n < _size)
            return top[n];
        else {
            perror("Error: There is no such array element\n");
            exit(1);
        } 
    }

    void PrintMas() {
        printf("Система уравнений имеет решения:\n");
        for (int i = 0; i < _size; i++) 
            printf("x%d = %lf\n", i + 1, top[i]);
    }
    
private:
    int _size;
    double *top;
};  


class Matrix {
public:
    void inputMat(Matrix& A, const int n) {
        int res;
        printf("Введите элементы матрицы А по одному:\n");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                res = scanf("%lf", &A.M_element(i, j));
                check_input(res) ? exit(1) : (void)0;
            }
    }

    Matrix(int row, int col) {
        _row = row;
        _col = col;

        top = new double*[_row];
        if (top == nullptr) {
            perror("Error: Memory allocation falied\n");
            exit(1);
        }

        for (int i = 0; i < _row; i++) {
            top[i] = new double[_col];
        }
    }

    ~Matrix() {
        for (int i = 0; i < _row; i++)
            delete[] top[i];
        delete[] top;
    }

    double& M_element(int row, int col) {
        if ((row >= 0 && row < _row) && (col >= 0 && col < _col))
            return top[row][col];
        else {
            perror("Error: There is no such matrix element\n");
            exit(1);
        }
    }

private:
    int _row;
    int _col;
    double **top;   
};


void gauss(Matrix &A, Mas &B, const int n);

int main(void) {
    int n, res;
    printf("Введите количество уравнений: ");
    res = scanf("%d", &n);
    check_input(res) ? exit(1) : (void)0;

    Matrix A(n, n);
    Mas B(n);

    A.inputMat(A, n); 

    B.inputMas(B, n);

    gauss(A, B, n);

    return 0;
}







































bool check_input(const int res) {
    if (res != 1) {
        perror("Error: Wrong input\n");
        return true;
    }
    return false;
}


void gauss(Matrix &A, Mas &B, const int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (A.M_element(i, i) == 0) {
                perror("Error: Division by zero\n");
                exit(1);
            }
            double foo = -A.M_element(j, i) / A.M_element(i, i);
            for (int k = i; k < n; k++)
                A.M_element(j, k) += foo * A.M_element(i, k);
            B.element(j) += foo * B.element(i);
        }
    }

    Mas ans(n);

    int det = 1;

    for (int i = 0; i < n; i++)
        det *= A.M_element(i, i);
    
    if (A.M_element(n - 1, n - 1) == 0 && B.element(n - 1) != 0) 
        printf("0 != %lf, so there are no solutions\n", B.element(n - 1));

    else if (det == 0) 
        printf("The determinant is zero, so there are infinitely many solutions\n");

    else {
        for (int i = n - 1; i >= 0; i--) {
            ans.element(i) = B.element(i);
            for (int j = i + 1; j < n; j++)
                ans.element(i) -= A.M_element(i, j) * ans.element(j);
            if (A.M_element(i, i) == 0) {
                    perror("Error: Division by zero\n");
                    exit(1);
            }
            ans.element(i) /= A.M_element(i, i);
        }
        ans.PrintMas();
    }
}
