#include <iostream>
#include "LineralAlgebra.hpp"

int main() {
    using std::cout;
    using std::endl;

    // Test 1: Simple 3x3 matrix
    matrix mat1 = {
        {2, 1, 1},
        {1, 3, 2},
        {3, 1, 1}
    };

    cout << "===== Test 1: 3x3 matrix =====" << endl;
    cout << "Original matrix:" << endl;
    PrintMat(mat1);

    ToUptriMat(mat1);
    cout << "Upper triangular matrix:" << endl;
    PrintMat(mat1);

    // Test 2: 4x4 matrix
    matrix mat2 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    cout << endl << "===== Test 2: 4x4 matrix =====" << endl;
    cout << "Original matrix:" << endl;
    PrintMat(mat2);

    ToUptriMat(mat2);
    cout << "Upper triangular matrix:" << endl;
    PrintMat(mat2);

    // Test 3: Matrix with zero rows (needs pivoting)
    matrix mat3 = {
        {0, 1, 2},
        {3, 0, 4},
        {5, 6, 0}
    };

    cout << endl << "===== Test 3: Matrix with zeros =====" << endl;
    cout << "Original matrix:" << endl;
    PrintMat(mat3);

    ToUptriMat(mat3);
    cout << "Upper triangular matrix:" << endl;
    PrintMat(mat3);

    return 0;
}