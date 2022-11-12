#include <iostream>

#include "matrix.h"
#include "kramer.h"

using namespace std;

int main() {
    Matrix coefficients, unknown_vars;
    coefficients.input("Введите матрицу коэффициентов");
    unknown_vars.input("Введите матрицу неизвестных переменных");

    KramerSolver kramerSolver(&coefficients, &unknown_vars);

    if (kramerSolver.is_valid()) {
        kramerSolver.printSystem();

        double* result = kramerSolver.solve();

        cout << "Результат:" << endl;

        for (unsigned short i = 0; i < coefficients.height; ++i)
            cout << " - x" << i + 1 << ": " << result[i] << endl;

    } else {
        cout << "Неверный ввод данных" << endl;
    }

    return 0;
}