Math Matrix Homework - 2
====================

Программа, которая находит определитель квадратной матрицы.  
Основана на [предыдущем проекте](https://github.com/viklover/math-matrix-hw-1)

Исходный код можно посмотреть [здесь](main.cpp)

Запустить программу можно на этом [сервисе](https://replit.com/@viklover/Math-Matrix-Homework-2#main.cpp)

Входные данные
-------------
Программа ожидает следующий формат общения:

```
Введите размеры и значения матрицы:
4 4
-2 5 -2 3
-5 5 -5 6
3 -4 6 -4
1 3 7 -4

Определитель матрицы:
-144
```

Небольшая документация
----------------------

В классе `Matrix` появились новые методы

```cpp
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
```

---------

Метод `isSquare()` возвращает `true`, если матрица является квадратной

```cpp
bool Matrix::isSquare() const {
    return height == width && height > 1 && width > 1;
}
```

---------

`Matrix::countDeterminant()` является публичным методом и входной точкой для приватного `Matrix::countDeterminant(int **matrix, int N)`, рекурсивно вычисляющий определитель матрицы через алгебраические дополнения.

```cpp
int Matrix::countDeterminant() {
    return countDeterminant(array, height);
}
```

```cpp
int Matrix::countDeterminant(int **matrix, int N) {

    switch(N) {
        case 1: // Матрица 1x1
            return matrix[0][0];
        case 2: // Матрица 2x2
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        default: // Матрица NxN, где N > 2 
            int det = 0; // Переменная для определителя
            int sign = 1; // Знак в формуле алг.дополнения -> (-1)^(i+j)
            int** sub_matrix = new int*[N-1]; // матрица, будущий определитель которой и формирует минор
            for (unsigned short i = 0, k = 0; i < N; ++i, sign = -sign, k = 0) {
                for (unsigned short j = 0; j < N; ++j) {
                    if (i != j)
                        sub_matrix[k++] = matrix[j] + 1;
                }
                // Прибавляем к определителю (-1)^(i+j) * aij * Mij
                det += + sign * matrix[i][0] * countDeterminant(sub_matrix, N-1); 
            }
            delete[] sub_matrix;
            return det;
    }
}
```

---------

```cpp
int main() {
    Matrix matrix; // Создаём экземпляр объекта Matrix
    matrix.input(); // Вводим данные с клавиатуры

    // Проверяем, является ли матрица квадратной
    if (matrix.isSquare()) {
        cout << endl << "Определитель матрицы:" << endl;
        cout << matrix.countDeterminant() << endl;
    }
    else {
        cout << "Матрица не является квадратной" << endl;
    }

    return 0;
}
```
