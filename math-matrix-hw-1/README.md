Math Matrix Homework - 1
====================

Программа, которая реализует умножение двух матриц.

Исходный код можно посмотреть [здесь](main.cpp).

Запустить программу можно на этом [сервисе](https://replit.com/@viklover/Math-Matrix-Homework#main.cpp)

Входные данные
-------------
Программа ожидает следующий формат общения:

```
Введите размеры и значения матрицы №1:
2 3
-4 2 -6
0 8 20

Введите размеры и значения матрицы №2:
3 3
0 -2 2
1 10 9
8 8 1

Результат перемножения:
-46 -20 4
168 240 92
```

Небольшая документация
----------------------

Класс `Matrix` описывает сущность матрицы.

```cpp
class Matrix {

public:
    Matrix();
    Matrix(const Matrix& obj);
    ~Matrix();

    int** array; // Двумерный массив матрицы
    unsigned short width, height; // Размеры матрицы
    
    void input(const char* name);
    void print();

    Matrix& operator*(Matrix matrix);
};
```

Метод `input` отвечает за ввод данных в матрицу: размер и значения

```cpp
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
```

Для вывода матрицы в консоль существует метод `print`

```cpp
void Matrix::print() {

    for (unsigned short i = 0; i < height; ++i) {
        for (unsigned short j = 0; j < width; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
```

Перегрузка операции умножения, для удобного перемножения между собой экземпляров типа `Matrix`.

```cpp
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
```

Также у класса присутствует:
1. Пустой конструктор `Matrix()`
2. Деструктор `~Matrix()` - освобождает память под выделенный двумерный массив
3. Конструктор копирования `Matrix(const Matrix& obj)`

---------

```cpp
// Проверка возможности перемножения двух матриц
bool compareMatrices(Matrix* matrix1, Matrix* matrix2) {
    return matrix1->width == matrix2->height;
}


int main() {
    Matrix matrix1, matrix2; // Создание двух экземпляров типа Matrix
    matrix1.input("1"); matrix2.input("2"); // Ввод данных для каждой матрицы

    // Проверка на возможность совершить операцию
    if (compareMatrices(&matrix1, &matrix2)) {
        Matrix result = matrix1 * matrix2; // Перемножаем матрицы

        cout << endl << "Результат перемножения: " << endl;
      
        result.print(); // Выводим результат
    }
    else {
        cout << "Операция невозможна из-за недопустимых размеров матрицы" << endl;
    }

    return 0;
}
```
