#include <iostream>

using namespace std;

class Matrix {

public:
    Matrix();
    Matrix(const Matrix& obj);
    ~Matrix();

    int** array;
    unsigned short width, height;

    void input(const char* name);
    void input();
    void print();

    int countDeterminant();

    bool isSquare() const;

    Matrix& operator*(Matrix matrix);

private:
    int countDeterminant(int **matrix, int N);
};

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

void Matrix::input(const char* name) {
    cout << endl << "Введите размеры и значения матрицы" << name << ":" << endl;
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

void Matrix::print() {

    for (unsigned short i = 0; i < height; ++i) {
        for (unsigned short j = 0; j < width; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
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

Matrix::Matrix() { }

Matrix::~Matrix() {
    for (unsigned short i = 0; i < height; ++i) {
        delete array[i];
    }
    delete[] array;
}

int main() {
    Matrix matrix;
    matrix.input();

    if (matrix.isSquare()) {
        cout << endl << "Определитель матрицы:" << endl;
        cout << matrix.countDeterminant() << endl;
    }
    else {
        cout << "Матрица не является квадратной" << endl;
    }

    return 0;
}
