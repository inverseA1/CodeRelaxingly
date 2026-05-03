#ifndef LINERALALGEBRA_HPP
#define LINERALALGEBRA_HPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <algorithm>

using vectr = std::vector<double>;
using matrix = std::vector<vectr>;

//---declarations---
inline void PrintVec(const vectr& vec);
inline void PrintMat(const matrix& mat);

inline vectr PlusVector(const vectr& vec1, const vectr& vec2);
inline vectr TimesVector(const vectr& vec, double num);
inline vectr MinusVector(const vectr& vec1, const vectr& vec2);
inline double DotProduct(const vectr& vec1, const vectr& vec2);

inline matrix DefMatrix(int row, int col);
inline int GetCol(const matrix& mat);
inline int GetRow(const matrix& mat);
inline vectr GetColVector(const matrix& mat, int col);
inline matrix TransposeMatrix(const matrix& mat);
inline matrix VecToMatrix(const vectr& vec);
inline vectr MatrixToVec(const matrix& mat);
inline matrix PlusMatrix(const matrix& mat1, const matrix& mat2);
inline matrix TimesMatrix(const matrix& mat, double num);
inline matrix MatrixTimesMatrix(const matrix& mat1, const matrix& mat2);
inline vectr MatrixTimesVector(const matrix& mat, const vectr& vec);

//print functions---------------------------------------------------------------------------------------
//print vector
//vector is implemented as vectr, default is column vector
inline void PrintVec(const vectr& vec){
    int len = vec.size();
    for(int i = 0; i < len; i++){
        std::cout<< vec[i] << " ";
    }
    std::cout<< std::endl;
}

//print matrix
//matrix is implemented as std::vector<vectr>, mat[i] is the i-th row
inline void PrintMat(const matrix& mat){
    int row = mat.size();
    int col = GetCol(mat);
    for(int i = 0; i < row ; i++){
        for(int j = 0; j < col; j++){
            std::cout << std::fixed << std::setprecision(3) 
                      << std::setw(8) << mat[i][j];
        }
        std::cout << std::endl;
    }
}

//vector operations---------------------------------------------------------------------------------------
//vector addition
inline vectr PlusVector(const vectr& vec1, const vectr& vec2){
    int len = vec1.size();
    vectr vec_(len,0);
    for(int i = 0 ; i < len ; i++){
        vec_[i] = vec1[i] + vec2[i];
    }
    return vec_;
}

//vector scalar multiplication
inline vectr TimesVector(const vectr& vec, double num){
    int len = vec.size();
    vectr resultvec(len,0);
    for(int i = 0 ; i < len ; i++){
        resultvec[i] = num * vec[i];
    }
    return resultvec;
}

//vector subtraction
inline vectr MinusVector(const vectr& vec1, const vectr& vec2){
    return PlusVector(vec1, TimesVector(vec2, -1));
}

//vector dot product
inline double DotProduct(const vectr& vec1, const vectr& vec2){
    int len = vec1.size();
    if(len == vec2.size()){
        double VecTimes = 0;
        for(int i = 0 ; i < len ; i++){
            VecTimes += vec1[i] * vec2[i];
        }
        return VecTimes;
    }else{
        throw std::runtime_error("DotProduct::error::Length Mismatch.");
    }
}

//Get Length of Vector
inline double LenVec(vectr vec){
    return sqrt(DotProduct(vec, vec));
}

//Get the subscript of the maximum value in the vector
inline int vecmax_sub(vectr vec){
    int script = 0;
    int n = vec.size();
    for(int i = 0 ; i < n ; i++){
        if(vec[i] > vec[script]){
            script = i;
        }
    }
    return script;
}

//matrix operations-----------------------------------------------------------------------------------------
//create matrix with given rows and columns
inline matrix DefMatrix(int row, int col){
    matrix mat(row, vectr(col));
    return mat;
}

//get matrix row count and column count
//to get vector length, just use vec.size()
inline int GetCol(const matrix& mat){
    if(mat.empty() || mat[0].empty()) return 0;
    return mat[0].size();
}

inline int GetRow(const matrix& mat){
    return mat.size();
}

//get the column vector at given column index
//to get row vector, just use mat[i]
inline vectr GetColVector(const matrix& mat, int col){
    int _row_ = GetRow(mat);
    int _col_ = GetCol(mat);
    if(col < 0 || col >= _col_){
        throw std::runtime_error("GetColVector::error::Invalid col.");
    }
    vectr vec_(_row_);
    for(int i = 0 ; i < _row_ ; i++){
        vec_[i] = mat[i][col];
    }
    return vec_;
}

//matrix transpose
inline matrix TransposeMatrix(const matrix& mat){
    int row = GetRow(mat);
    int col = GetCol(mat);
    matrix mat_ = DefMatrix(col,row);
    for(int i = 0 ; i < col ; i++){
        for(int j = 0 ; j < row ; j++){
            mat_[i][j] = mat[j][i];
        }
    }
    return mat_;
}

//convert a column vector to an n-by-1 matrix for certain operations
inline matrix VecToMatrix(const vectr& vec){
    matrix mat_(1,vec);
    return TransposeMatrix(mat_);
}

//conversely, convert an n-by-1 matrix to a vector
inline vectr MatrixToVec(const matrix& mat){
    int row = GetRow(mat);
    if(GetCol(mat) == 1){
        vectr vec_(row);
        for(int i = 0 ; i < row ; i++){
            vec_[i] = mat[i][0];
        }
        return vec_;
    }else{
        throw std::runtime_error("MatrixToVec::error::Invalid convert.");
    }
}

//matrix addition
inline matrix PlusMatrix(const matrix& mat1, const matrix& mat2){
    int col = GetCol(mat1);
    int row = GetRow(mat1);
    if(col == GetCol(mat2) && row == GetRow(mat2)){
        matrix mat3 = DefMatrix(row,col);
        for(int i = 0 ; i < row ; i++){
            mat3[i] = PlusVector(mat1[i],mat2[i]);
        }
        return mat3;
    }else{
        throw std::runtime_error("PlusMatrix::error::Row and Column Mismatch.");
    }
}

//matrix scalar multiplication
inline matrix TimesMatrix(const matrix& mat, double num){
    int row = GetRow(mat);
    int col = GetCol(mat);
    matrix mat_ = DefMatrix(row, col);
    for(int i = 0 ; i < row ; i++){
        mat_[i] = TimesVector(mat[i],num);
    }
    return mat_;
}

//matrix multiplication
inline matrix MatrixTimesMatrix(const matrix& mat1, const matrix& mat2){
    int row1 = GetRow(mat1);
    int col1 = GetCol(mat1);
    int row2 = GetRow(mat2);
    int col2 = GetCol(mat2);
    if(col1 == row2){
        matrix mat_ = DefMatrix(row1, col2);
        for(int i = 0 ; i < row1 ; i++){
            for(int j = 0 ; j < col2 ; j++){
                mat_[i][j] = DotProduct(mat1[i], GetColVector(mat2,j));
            }
        }
        return mat_;
    }else{
        throw std::runtime_error("MatrixTimesMatrix::error::Row and Column Mismatch.");
    }
}

//matrix times vector
inline vectr MatrixTimesVector(const matrix& mat, const vectr& vec){
    matrix vecmat = VecToMatrix(vec);
    return MatrixToVec(MatrixTimesMatrix(mat,vecmat));
}

//Elementary Row Operations
//Row Swapping, row$ = 0, 1, 2, ...
inline void RowSwap(matrix& mat,int row1, int row2){
    int row = GetRow(mat);
    if(row1 < row && row2 < row){
        std::swap(mat[row1],mat[row2]);
    }else{
        throw std::runtime_error("RowSwap::error::Invalid line count");
    }
}
//The original matrix remains unchanged
inline matrix RowSwapNew(const matrix mat,int row1, int row2){
        matrix mat_ = mat;
        RowSwap(mat_,row1,row2);
        return mat_;
}

//Duplicate a row
inline void Duplicatrow(matrix& mat, int row, double num){
    if(row < GetRow(mat)){
        mat[row] = TimesVector(mat[row], num);
    }else{
        throw std::runtime_error("Duplicatrow::error::Invalid row count");
    }
}
//The original matrix remains unchanged
inline matrix DuplicatrowNew(const matrix mat, int row, double num){
        matrix mat_ = mat;
        Duplicatrow(mat_, row, num);
        return mat_;
}

//Adding a multiple of one row to another row, row1 = row1 + row2 * num
inline void AddMultiRow(matrix& mat, int row1, int row2, double num){
    int row = GetRow(mat);
    if(row1 < row && row2 < row){
        mat[row1] = PlusVector(mat[row1], TimesVector(mat[row2], num));
    }else{
        throw std::runtime_error("AddMultiRow::error::Invalid row count");
    }
}
//The original matrix remains unchanged
inline matrix AddMultiRowNew(const matrix mat, int row1, int row2, double num){
        matrix mat_ = mat;
        AddMultiRow(mat_,row1,row2,num);
        return mat_;
}

//Matrix factorization
//Convert to upper triangular matrix
inline void ToUptriMat(matrix& mat){
    int row = GetRow(mat);
    std::cout << "row = " << row <<std::endl;
    for(int i = 0 ; i < row-1 ; i++){
        //find main element
        vectr vec = GetColVector(mat, i);
        vec.erase(vec.begin(), vec.begin() + i);
        PrintVec(vec);
        //Undefined behavior occurs if there are more rows than columns

        //TODO
        int subscript = vecmax_sub(vec);
        std::cout << "main element is vec[" << subscript << "]" <<std::endl;
        if(vec[subscript] == 0){
            std::cout<< "main element too small!" << std::endl;
            continue;
        }
        RowSwap(mat, i, subscript+i);
        std::cout<< "after rowswap:" << std::endl;
        PrintMat(mat);
        for(int j = i+1 ; j < row ; j++){
            double coefficient = mat[j][i]/mat[i][i];
            AddMultiRow(mat, j , i , -coefficient);
            std::cout<<"mat[" << j << "] - " << coefficient << " * mat[" << i << "]" << std::endl;
            PrintMat(mat);
        }
    }
}
//The original matrix remains unchanged


//TODO
//Find the determinant
inline double Determinat(const matrix mat){
    if(GetRow(mat) == GetCol(mat)){

    }else{
        throw std::runtime_error("Determinat::error::Input must be a square matrix.");
    }
}


//TODO
//Find the inverse of the matrix
inline matrix Inversemat(const matrix mat){

}

#endif