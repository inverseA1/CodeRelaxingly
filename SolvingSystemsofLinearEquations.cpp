#include <iostream>
#include <stdexcept>
#include "LineralAlgebra.hpp"

class SOLVELINEEQUA{
    private:
        vectr vecX;
        vectr vecB;
        matrix matA;
    public:
        SOLVELINEEQUA(vectr vecb, matrix mata){vecB = vecb; matA = mata;}

        void PrintMatA(){PrintMat(matA);}
        void PrintVecB(){PrintVec(vecB);}
        void PrintVecX(){PrintVec(vecX);}

        bool IsOnlySolvable(){
            return Is_Inversable(matA);
        }

        void Solve_Inverse(){
            if(IsOnlySolvable()){
                vecX = MatrixTimesVector(InverseMat_GJ(matA),vecB);
            }else{
                throw std::runtime_error("Solve_Inverse::error::not inversable.");
            }
        }

};

int main(){
    // 定义一个可逆方阵 A (3x3)
    matrix A = {
        {2, 1, 1},
        {1, 3, 2},
        {1, 1, 2}
    };
    // 定义向量 b
    vectr b = {6, 11, 9};

    std::cout << "Matrix A:" << std::endl;
    PrintMat(A);
    std::cout << "Vector b:" << std::endl;
    PrintVec(b);

    // 求解线性方程组 Ax = b
    SOLVELINEEQUA solver(b, A);
    if (solver.IsOnlySolvable()) {
        solver.Solve_Inverse();
    }

    std::cout << "Vector X:" << std::endl;
    solver.PrintVecX();
    return 0;
}