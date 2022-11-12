Math Matrix Homework - 3
====================

Программа, которая решает систему уравнений по методу Крамера.

Исходный код лежит в этом репозитории выше (теперь с делением на разные файлы).

Запустить программу позволит этот [сервис](https://replit.com/@viklover/Math-Matrix-Homework-3#main.cpp)

Входные данные
-------------
Программа ожидает следующий формат общения:

```
Введите матрицу коэффициентов:
4 4
2 2 -1 1
4 3 -1 2
8 5 -3 4
3 3 -2 2

Введите матрицу неизвестных переменных:
4 1
4 
6
12
6

Система уравнений: 
2 2 -1 1 = 4
4 3 -1 2 = 6
8 5 -3 4 = 12
3 3 -2 2 = 6

№ 1: Вычисляем определитель матрицы коэффициентов: 2

№ 2: Ищем определители остальных матриц: 

 - Матрицу № 1
    4 2 -1 1 
    6 3 -1 2 
    12 5 -3 4 
    6 3 -2 2 

   Определитель: 2

 - Матрицу № 2
    2 4 -1 1 
    4 6 -1 2 
    8 12 -3 4 
    3 6 -2 2 

   Определитель: 2

 - Матрицу № 3
    2 2 4 1 
    4 3 6 2 
    8 5 12 4 
    3 3 6 2 

   Определитель: -2

 - Матрицу № 4
    2 2 -1 4 
    4 3 -1 6 
    8 5 -3 12 
    3 3 -2 6 

   Определитель: -2

Результат:
 - x1: 1
 - x2: 1
 - x3: -1
 - x4: -1
```

Небольшая документация
----------------------

Сущность `Matrix` теперь имеет статический метод `changeColumn`.

```cpp
class Matrix {

public:
    Matrix();
    Matrix(const Matrix& obj);
    ~Matrix();

    int** array;
    unsigned short width, height;

    static Matrix changeColumn(Matrix* matrix, Matrix* column, unsigned short col_index);

    void input(const char* hint);
    void input();
    void print(unsigned space);
    void print();

    int countDeterminant();

    bool isSquare() const;

    Matrix& operator*(Matrix matrix);

private:
    int countDeterminant(int **matrix, int N);
};
```

Данный метод создаёт новую матрицу взяв за основу другую из аргумента `matrix`. Он меняет определённую колонку по индексу `col_index` на `column` из аргумента функции.

```cpp
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
```

-------

Для решения системы уравнения по методу Крамера я создал класс `KramerSolver`, который принимает в конструктор две матрицы: матрицы коэффициентов и неизвестных переменных. 

```cpp
class KramerSolver {

private:
    Matrix *coefficients, *vars;
    double* result{};

public:
    KramerSolver(Matrix* coefficients, Matrix* vars);
    ~KramerSolver();
    bool is_valid();
    double* solve();
    void printSystem();
};
```

Метод `is_valid()` проверяет корректность формата введённых данных.

```cpp
bool KramerSolver::is_valid() {
    if (coefficients == nullptr || vars == nullptr)
        return false;

    return coefficients->height == vars->height && vars->width == 1;
}
```

Для вывода введённой ранее системы уравнений в консоль, существует метод `printSystem()`.

```cpp
void KramerSolver::printSystem() {

    cout << endl << "Система уравнений: " << endl;

    for (unsigned short i = 0; i < coefficients->height; ++i) {
        for (unsigned short j = 0; j < coefficients->width + 1; ++j) {
            if (j == coefficients->width) {
                cout << "= " << vars->array[i][0] << endl;
            } else {
                cout << coefficients->array[i][j] << " ";
            }
        }
    }

    cout << endl;
}
```

И самый главный метод - `solve()`, решает систему уравнений с выводом промежуточных результатов в консоль.

```cpp
double* KramerSolver::solve() {
    result = new double[coefficients->width];

    int det = coefficients->countDeterminant();

    cout << "№ 1: Вычисляем определитель матрицы коэффициентов: ";
    cout << det << endl << endl;

    cout << "№ 2: Ищем определители остальных матриц: " << endl;
    cout << endl;

    for (unsigned short i = 0; i < coefficients->width; ++i) {
        Matrix matrix = Matrix::changeColumn(coefficients, vars, i); // Меняем колонку по индексу i
        int sub_det = matrix.countDeterminant(); // Вычисляем определитель

        result[i] = (sub_det * 1.0) / det; // ищем x по формуле: det i / det A

        cout << " - " << "Матрица № "  << i + 1 << endl;
        matrix.print(4);

        cout << "   Определитель: " << sub_det << endl;

        cout << endl;
    }

    return result;
}
```

---------

```cpp
int main() {
    Matrix coefficients, unknown_vars;
    coefficients.input("Введите матрицу коэффициентов");
    unknown_vars.input("Введите матрицу неизвестных переменных");

    KramerSolver kramerSolver(&coefficients, &unknown_vars);  

    if (kramerSolver.is_valid()) { // Проверяем корректность введённых данных
        kramerSolver.printSystem(); // Выводим систему в консоль

        double* result = kramerSolver.solve(); // Решаем и кладём в массив result

        cout << "Результат:" << endl;

        for (unsigned short i = 0; i < coefficients.height; ++i)
            cout << " - x" << i + 1 << ": " << result[i] << endl;

    } else {
        cout << "Неверный ввод данных" << endl;
    }

    return 0;
}
```
