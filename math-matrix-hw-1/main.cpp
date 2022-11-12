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
    void print();

    Matrix& operator*(Matrix matrix);
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
    cout << endl << "Введите размеры и значения матрицы №" << name << ":" << endl;
    cin >> height >> width;

    array = new int* [height];

    for (unsigned short i = 0; i < height; ++i) {
        array[i] = new int[width];
        for (unsigned short j = 0; j < width; ++j) {
            cin >> array[i][j];
        }
    }
}

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

Matrix::Matrix() { }

Matrix::~Matrix() {
    for (unsigned short i = 0; i < height; ++i) {
        delete array[i];
    }
    delete[] array;
}

bool compareMatrices(Matrix* matrix1, Matrix* matrix2) {
    return matrix1->width == matrix2->height;
}


int main() {
    Matrix matrix1, matrix2;
    matrix1.input("1"); matrix2.input("2");

    if (compareMatrices(&matrix1, &matrix2)) {
        Matrix result = matrix1 * matrix2;

        cout << endl << "Результат перемножения: " << endl;
      
        result.print();
    }
    else {
        cout << "Операция невозможна из-за недопустимых размеров матрицы" << endl;
    }

    return 0;
}
