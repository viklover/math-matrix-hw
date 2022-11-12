
#include "matrix.h"

#ifndef MATH_MATRIX_HW_3_KRAMER_H
#define MATH_MATRIX_HW_3_KRAMER_H

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

#endif
