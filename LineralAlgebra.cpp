#include <iostream>
#include <cmath>
#include <vector>

class lineralAlgebral{
    private:
        std::vector<double> vecX;
        std::vector<std::vector<double>> matrixA;
        std::vector<double> vecB;
        std::vector<std::vector<double>> matrixB;
        int row;
        int col;

    public:
        lineralAlgebral() : vecX(3,0), vecB({5, -2, 9}), matrixA({{2, 1, 1}, {4, -6, 0}, {-2, 7, 2}}){
            row = this->matrixA.size();
            col = this->matrixA[0].size();
            matrixB = matrixA;
            for(int i = 0 ; i < row ; i++){
                matrixB[i].push_back(vecB[i]);
            }
        }

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

        void solve(){
            for(int i = 0 ; i < row ; i++){
                for(int j = 0 ; j < row && j != i ; j++){

                }
            }
        }
};

int main(){
    lineralAlgebral MyAlgebral;
    MyAlgebral.PrintMatA();
    MyAlgebral.PrintMatB();
    return 0;
}