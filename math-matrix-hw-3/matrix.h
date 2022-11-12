
#ifndef MATH_MATRIX_HW_3_MATRIX_H
#define MATH_MATRIX_HW_3_MATRIX_H

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

#endif
