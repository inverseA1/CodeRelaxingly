#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#define ERROR 0.000000000001 // 定义误差
#define EPSILON 0.00001

inline double Func(double x){ return x * x - 2 ;}
inline double Dfun(double x){ return 2 * x ; }

inline double FindDfun(double x, double (*func)(double), double epsilon) {
    return (func(x + epsilon) - func(x - epsilon)) / 2*epsilon ;
}

double Polynomial(std::vector<double> coefficient, double x){
    double result = 0;
    int n = coefficient.size();
    for(int i = 0 ; i < n ; i++){
        result += coefficient[i] * std::pow(x, i);
    }
    return result;
}

double Dpolynomial(std::vector<double> coefficient, double x){
    double result = 0;
    int n = coefficient.size();
    for(int i = 1 ; i < n ; i++){
        result += coefficient[i] * i * std::pow(x, i-1);
    }
    return result;
}

double Leration(double error, double x){
    double x_ = x - Func(x) / Dfun(x) ;
    //std::cout<< "Func(x)=" << Func(x) << " Dfun(x)=" << Dfun(x)
             //<< " x=" << x << " x_=" << x_ << " error=" << std::abs(x_ - x) <<std::endl;
    if(std::abs(x_ - x) <= error){
        return x_;
    }else{
        return Leration(error, x_);
    }
}

double Leration_(double error, double x){
    double x_ = x - Func(x) / FindDfun(x, Func, EPSILON) ;
    std::cout << "x = " << x << " & " << "x_ = " << x_ << " error = " << std::abs(x_ - x) <<std::endl;
    if(std::abs(x_ - x) <= error){
        return x_;
    }else{
        return Leration_(error, x_);
    }
}

double LerationPoly(double error, double x,std::vector<double> coefficient){
    double x_ = x - Polynomial(coefficient, x) / Dpolynomial(coefficient, x) ;
        //std::cout<< "Polynomial(x)=" << Polynomial(coefficient,x) << " Dpolynomial(x)=" << Dpolynomial(coefficient,x)
             //<< " x=" << x << " x_=" << x_ << " error=" << std::abs(x_ - x) <<std::endl;
    if(std::abs(x_ - x) <= error){
        return x_;
    }else{
        return LerationPoly(error, x_,coefficient);
    }
}

int main(){
    std::vector<double> coeff = {-10, 0, 1};
    std::cout << std::setprecision(12);
    //std::cout << Leration(ERROR, 1) << std::endl;
    //std::cout << Leration_(ERROR, 1) << std::endl;
    std::cout << LerationPoly(ERROR, 3, coeff) << std::endl;
    return 0;
}