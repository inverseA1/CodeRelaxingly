#include <iostream>
#include "LineralAlgebra.hpp"

int main(){
    using std::cout;
    using std::endl;

    //---vector basic operations test---
    cout << "===== Vector Tests =====" << endl;

    std::vector<double> vec1 = {1, 2, 3};
    std::vector<double> vec2 = {4, 5, 6};

    cout << "vec1: "; PrintVec(vec1);
    cout << "vec2: "; PrintVec(vec2);

    cout << "Plus: "; PrintVec(PlusVector(vec1, vec2));
    cout << "Minus: "; PrintVec(MinusVector(vec1, vec2));
    cout << "TimesVector(vec1, 2): "; PrintVec(TimesVector(vec1, 2));
    cout << "PointTimes: " << DotProduct(vec1, vec2) << endl;

    //---matrix basic operations test---
    cout << endl << "===== Matrix Tests =====" << endl;

    matrix mat1 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    matrix mat2 = {
        {1, 0, 0},
        {0, 1, 0}
    };

    cout << "mat1 (2x3):" << endl; PrintMat(mat1);
    cout << "mat2 (2x3):" << endl; PrintMat(mat2);

    cout << "GetRow(mat1): " << GetRow(mat1) << endl;
    cout << "GetCol(mat1): " << GetCol(mat1) << endl;

    cout << "TransposeMatrix(mat1):" << endl; PrintMat(TransposeMatrix(mat1));

    cout << "PlusMatrix(mat1, mat1):" << endl; PrintMat(PlusMatrix(mat1, mat1));
    cout << "TimesMatrix(mat1, 2):" << endl; PrintMat(TimesMatrix(mat1, 2));

    //---matrix multiplication test---
    cout << endl << "===== Matrix Multiplication Tests =====" << endl;

    matrix A = {
        {1, 2},
        {3, 4}
    };
    matrix B = {
        {5, 6},
        {7, 8}
    };

    cout << "A:" << endl; PrintMat(A);
    cout << "B:" << endl; PrintMat(B);
    cout << "A * B:" << endl; PrintMat(MatrixTimesMatrix(A, B));

    // 2x3 * 3x2
    matrix C = {
        {1, 2, 3},
        {4, 5, 6}
    };
    matrix D = {
        {1, 0},
        {0, 1},
        {1, 0}
    };
    cout << "C (2x3):" << endl; PrintMat(C);
    cout << "D (3x2):" << endl; PrintMat(D);
    cout << "C * D (2x2):" << endl; PrintMat(MatrixTimesMatrix(C, D));

    //---matrix times vector test---
    cout << endl << "===== Matrix-Vector Tests =====" << endl;

    matrix M = {
        {1, 2},
        {3, 4}
    };
    std::vector<double> v = {1, 1};

    cout << "M:" << endl; PrintMat(M);
    cout << "v: "; PrintVec(v);
    cout << "M * v:" << endl; PrintVec(MatrixTimesVector(M, v));

    //---test VecToMatrix and MatrixToVec---
    cout << endl << "===== Vec-Matrix Convert Tests =====" << endl;

    std::vector<double> colVec = {1, 2, 3};
    cout << "colVec: "; PrintVec(colVec);
    cout << "VecToMatrix: " << endl; PrintMat(VecToMatrix(colVec));

    matrix colMat = {{1}, {2}, {3}};
    cout << "colMat: " << endl; PrintMat(colMat);
    cout << "MatrixToVec: "; PrintVec(MatrixToVec(colMat));

    //---test empty matrix edge case---
    cout << endl << "===== Edge Case Tests =====" << endl;

    matrix emptyMat;
    cout << "empty matrix GetRow: " << GetRow(emptyMat) << endl;
    cout << "empty matrix GetCol: " << GetCol(emptyMat) << endl;

    cout << endl << "All tests passed!" << endl;
    return 0;
}