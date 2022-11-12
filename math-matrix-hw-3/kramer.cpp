
#include "kramer.h"
#include <iostream>

using namespace std;

KramerSolver::KramerSolver(Matrix* coefficients, Matrix* vars) {
    this->coefficients = coefficients;
    this->vars = vars;
}

KramerSolver::~KramerSolver() {
    delete[] result;
}

bool KramerSolver::is_valid() {
    if (coefficients == nullptr || vars == nullptr)
        return false;

    return coefficients->height == vars->height && vars->width == 1;
}

double* KramerSolver::solve() {
    result = new double[coefficients->width];

    int det = coefficients->countDeterminant();

    cout << "№ 1: Вычисляем определитель матрицы коэффициентов: ";
    cout << det << endl << endl;

    cout << "№ 2: Ищем определители остальных матриц: " << endl;
    cout << endl;

    for (unsigned short i = 0; i < coefficients->width; ++i) {
        Matrix matrix = Matrix::changeColumn(coefficients, vars, i);
        int sub_det = matrix.countDeterminant();

        result[i] = (sub_det * 1.0) / det;

        cout << " - " << "Матрица № "  << i + 1 << endl;
        matrix.print(4);

        cout << "   Определитель: " << sub_det << endl;

        cout << endl;
    }

    return result;
}

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
