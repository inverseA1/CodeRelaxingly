#include <iostream>
#include <cmath>
#include <vector>

class lineralAlgebra{
    private:
        /*基本的数据
        解向量X 系数矩阵A 向量b 增广矩阵B A行数 A列数*/
        std::vector<double> vecX;
        std::vector<std::vector<double>> matrixA;
        std::vector<double> vecB;
        std::vector<std::vector<double>> matrixB;
        int row;
        int col;

    public:
        //初始化函数
        lineralAlgebra() : vecX(3,0), vecB({5, -2, 9}), matrixA({{2, 1, 1}, {4, -6, 0}, {-2, 7, 2}}){
            row = this->matrixA.size();
            col = this->matrixA[0].size();
            matrixB = matrixA;
            for(int i = 0 ; i < row ; i++){
                matrixB[i].push_back(vecB[i]);
            }
        }
        //---各种打印函数---
        void PrintVec(std::vector<double> vec){
            int len = vec.size();
            for(int i = 0; i < len; i++){
                std::cout<< vec[i] << " ";
            }
            std::cout<< std::endl;
        }
        void PrintVecX(){PrintVec(this->vecX);}
        void PrintVecB(){PrintVec(this->vecB);}

        void PrintMat(std::vector<std::vector<double>> matrix){
            int row = matrix.size();
            for(int i = 0; i < row ; i++){
                    this->PrintVec(matrix[i]);
            }
        }
        void PrintMatA(){PrintMat(this->matrixA);}
        void PrintMatB(){PrintMat(this->matrixB);}
        //---各种打印函数---
        //向量的基本运算
        std::vector<double> PlusVector(std::vector<double> vec1, std::vector<double> vec2){
            int len = vec1.size();
            std::vector<double> resultvec(len,0);
            for(int i = 0 ; i < len ; i++){
                resultvec[i] = vec1[i] + vec2[i];
            }
            return resultvec;
        }

        std::vector<double> TimesVector(std::vector<double> vec, double num){
            int len = vec.size();
            std::vector<double> resultvec(len,0);
            for(int i = 0 ; i < len ; i++){
                resultvec[i] = num * vec[i];
            }
            return resultvec;
        }

        std::vector<double> MinusVector(std::vector<double> vec1, std::vector<double> vec2){
            return PlusVector(vec1, TimesVector(vec2, -1));
        }

        double VectorTimesVector(std::vector<double> vec1, std::vector<double> vec2){
            int len = vec1.size();
            if(len == vec2.size()){
                double VecTimes = 0;
                for(int i = 0 ; i < len ; i++){
                    VecTimes += vec1[i] * vec2[i];
                }
                return VecTimes;
            }else{
                std::cout<<"VectorTimesVector::error::Length Mismatch."<<std::endl;
                return 0;
            }
        }
        //矩阵的基本运算
        std::vector<std::vector<double>> DefMatrix(int row, int col){
            std::vector<std::vector<double>> mat(row, std::vector<double>(col));
            return mat;
        }


        inline int Get_Col(std::vector<std::vector<double>> mat){return mat[0].size();}
        inline int Get_Row(std::vector<std::vector<double>> mat){return mat.size();}
        std::vector<double> Get_ColVector(std::vector<std::vector<double>> mat, int col){
            int _row_ = Get_Row(mat);
            int _col_ = Get_Col(mat);
            if(col < _col_){
                std::vector<double> vec_(_row_);
                for(int i = 0 ; i < _row_ ; i++){
                    vec_[i] = mat[i][col];
                }
                return vec_;
            }else{
                std::cout<<"Get_ColVector::error::Invalid col."<<std::endl;
                return {0};
            }
        }

        std::vector<std::vector<double>> VecToMatrix(std::vector<double> vec){
            std::vector<std::vector<double>> mat_(1,vec);
            return TransposeMatrix(mat_);
        }

        std::vector<double> MatrixToVec(std::vector<std::vector<double>> mat){
            int row = Get_Row(mat);
            if(Get_Col(mat) == 1){
                std::vector<double> vec_(row);
                for(int i = 0 ; i < row ; i++){
                    vec_[i] = mat[i][0];
                }
                return vec_;
            }else{
                std::cout<<"MatrixToVec::error::Invalid convert."<<std::endl;
                return {0};
            }
        }

        std::vector<std::vector<double>> TransposeMatrix(std::vector<std::vector<double>> mat){
            int row = Get_Row(mat);
            int col = Get_Col(mat);
            std::vector<std::vector<double>> mat_ = DefMatrix(col,row);
            for(int i = 0 ; i < col ; i++){
                for(int j = 0 ; j < row ; j++){
                    mat_[i][j] = mat[j][i];
                }
            }
            return mat_;
        }

        std::vector<std::vector<double>> PlusMatrix(std::vector<std::vector<double>> mat1, std::vector<std::vector<double>> mat2){
            int col = Get_Col(mat1);
            int row = Get_Row(mat1);
            if(col == Get_Col(mat2) && row == Get_Row(mat2)){
                std::vector<std::vector<double>> mat3 = DefMatrix(row,col);
                for(int i = 0 ; i < row ; i++){
                    mat3[i] = PlusVector(mat1[i],mat2[i]);
                }
                return mat3;
            }else{
                std::cout<<"PlusMatrix::error::Row and Column Mismatch."<<std::endl;
                std::vector<std::vector<double>> ErrorMatrix = {{0}};
                return ErrorMatrix;
            }
        }

        std::vector<std::vector<double>> TimesMatrix(std::vector<std::vector<double>> mat, double num){
            int row = Get_Row(mat);
            int col = Get_Col(mat);
            std::vector<std::vector<double>> mat_ = DefMatrix(row, col);
            for(int i = 0 ; i < row ; i++){
                mat_[i] = TimesVector(mat[i],num);
            }
            return mat_;
        }

        std::vector<std::vector<double>> MatrixTimesMatrix(std::vector<std::vector<double>> mat1, std::vector<std::vector<double>> mat2){
            int row1 = Get_Row(mat1);
            int col1 = Get_Col(mat1);
            int row2 = Get_Row(mat2);
            int col2 = Get_Col(mat2);
            if(col1 == row2){
                std::vector<std::vector<double>> mat_ = DefMatrix(row1, col2);
                for(int i = 0 ; i < row1 ; i++){
                    for(int j = 0 ; j < col2 ; j++){
                        mat_[i][j] = VectorTimesVector(mat1[i], Get_ColVector(mat2,j));
                    }
                }
                return mat_;
            }else{
                std::cout<<"MatrixTimesMatrix::error::Row and Column Mismatch."<<std::endl;
                std::vector<std::vector<double>> ErrorMatrix = {{0}};
                return ErrorMatrix;
            }
        }

        //矩阵与向量的基本运算
        std::vector<double> MatrixTimesVector(std::vector<std::vector<double>> mat, std::vector<double> vec){
            std::vector<std::vector<double>> vecmat = VecToMatrix(vec);
            return MatrixToVec(MatrixTimesMatrix(mat,vecmat));
        }
        //方程组求解
        void solve(){
            for(int i = 0 ; i < row ; i++){
                for(int j = 0 ; j < row && j != i ; j++){

                }
            }
        }
};

int main(){
    lineralAlgebra MyAlgebra;
    MyAlgebra.PrintMatA();
    MyAlgebra.PrintMatB();
    return 0;
}