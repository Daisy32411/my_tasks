/*
Код написан с целью решения систем уравнения методом гаусса.
В начале введите количество уравнений, затем введите коэффиценты уравнений по одному
и наконец свободные члены уравнений по одному.
*/

#include <iostream>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <ctime>


bool check_input(const int res);

class Mas {
public:
    void randinputMas(Mas& B, const int n) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
            for (int i = 0; i < n; i++) {
                B.element(i) = std::rand() % 1001;
            }
    }

    void inputMas(Mas& B, const int n) {   
        int res; 
        printf("Введите свободные члены по одному:\n");
            for (int i = 0; i < n; i++) {
                res = scanf("%lf", &B.element(i));
                check_input(res) ? exit(1) : (void)0;
            }
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

    double& element(const int n) {
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
    void randinputMat(Matrix& A, const int n) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) 
                A.M_element(i, j) = std::rand() % 1001;
    }

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

    double& M_element(const int row, const int col) {
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
    int n, res, valid;
    printf("Введите 1, если хотите инициализировать матрицу самостоятельно, и 0 если хотите инициализировать её случайными числами\n");
    res = scanf("%d", &valid);
    check_input(res) ? exit(1) : (void)0;

    printf("Введите количество уравнений: ");
    res = scanf("%d", &n);
    check_input(res) ? exit(1) : (void)0;

    Matrix A(n, n);
    Mas B(n);

    if (valid ==  1) {
        A.inputMat(A, n); 
        B.inputMas(B, n);
    } else if (valid == 0) {
        A.randinputMat(A, n);
        B.randinputMas(B, n);
    } else {
        printf("Error: 'Valid' can be either 0 or 1\n");
        exit(1);
    }

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
