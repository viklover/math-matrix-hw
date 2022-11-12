
#include "matrix.h"
#include <iostream>

using namespace std;

Matrix::Matrix() { }

Matrix::Matrix(const Matrix& obj) {
    width = obj.width;
    height = obj.height;

    array = new int*[height];

    for (unsigned short i = 0; i < height; ++i) {
        array[i] = new int[width];
        for (unsigned short j = 0; j < width; ++j) {
            array[i][j] = obj.array[i][j];
        }
    }
}

Matrix Matrix::changeColumn(Matrix* matrix, Matrix* column, unsigned short col_index) {

    auto *new_matrix = new Matrix();

    new_matrix->width = matrix->width;
    new_matrix->height = matrix->height;

    new_matrix->array = new int*[matrix->height];

    for (unsigned short i = 0; i < matrix->height; ++i) {
        new_matrix->array[i] = new int[matrix->width];
        for (unsigned short j = 0; j < matrix->width; ++j) {
            if (j == col_index)
                new_matrix->array[i][j] = column->array[i][0];
            else
                new_matrix->array[i][j] = matrix->array[i][j];
        }
    }

    return *new_matrix;
}

void Matrix::input(const char* hint) {
    cout << endl << hint << ":" << endl;
    cin >> height >> width;

    array = new int* [height];

    for (unsigned short i = 0; i < height; ++i) {
        array[i] = new int[width];
        for (unsigned short j = 0; j < width; ++j) {
            cin >> array[i][j];
        }
    }
}

void Matrix::input() { input(""); }

void Matrix::print(unsigned space) {

    for (unsigned short i = 0; i < height; ++i) {
        for (unsigned k = 0; k < space; ++k)
            cout << " ";
        for (unsigned short j = 0; j < width; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

}

void Matrix::print() {
    print(0);
}

int Matrix::countDeterminant(int **matrix, int N) {

    switch(N) {
        case 1:
            return matrix[0][0];
        case 2:
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        default:
            int det = 0;
            int sign = 1;
            int** sub_matrix = new int*[N-1];
            for (unsigned short i = 0, k = 0; i < N; ++i, sign = -sign, k = 0) {
                for (unsigned short j = 0; j < N; ++j) {
                    if (i != j)
                        sub_matrix[k++] = matrix[j] + 1;
                }
                det += + sign * matrix[i][0] * countDeterminant(sub_matrix, N-1);
            }
            delete[] sub_matrix;
            return det;
    }
}

int Matrix::countDeterminant() {
    return countDeterminant(array, height);
}

bool Matrix::isSquare() const {
    return height == width && height > 1 && width > 1;
}

Matrix& Matrix::operator*(Matrix matrix) {

    Matrix* newMatrix = new Matrix();
    newMatrix->width = matrix.width;
    newMatrix->height = this->height;

    int** new_array = new int* [newMatrix->height];

    for (unsigned short i = 0; i < newMatrix->height; ++i) {
        new_array[i] = new int[width];
        for (unsigned short j = 0; j < newMatrix->width; ++j) {
            new_array[i][j] = 0;

            for (unsigned short m = 0; m < matrix.height; ++m) {
                new_array[i][j] += array[i][m] * matrix.array[m][j];
            }
        }
    }

    newMatrix->array = new_array;

    return *newMatrix;
}

Matrix::~Matrix() {
    for (unsigned short i = 0; i < height; ++i) {
        delete array[i];
    }
    delete[] array;
}

