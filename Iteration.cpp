#include <iostream>
#include <cmath>
#define ERROR 0.000000000001 // 定义误差
#define EPSILON 0.00001

inline double Func(double x){ return x * x - 2 ;}
inline double Dfun(double x){ return 2 * x ; }

inline double FindDfun(double x, double (*func)(double), double epsilon) {
    return (func(x + epsilon) - func(x - epsilon)) / 2*epsilon ;
}

double Leration(double error, double x){
    
    double x_ = x - Func(x) / Dfun(x) ;
    std::cout<< "Func(x)=" << Func(x) << " Dfun(x)=" << Dfun(x)
             << " x=" << x << " x_=" << x_ << " error=" << abs(x_ - x) <<std::endl;
    if(abs(x_ - x) <= error){
        return x_;
    }else{
        return Leration(error, x_);
    }
}

double Leration_(double error, double x){
    double x_ = x - Func(x) / FindDfun(x, Func, EPSILON) ;
    std::cout << "x = " << x << " & " << "x_ = " << x_ << " error = " << abs(x_ - x) <<std::endl;
    if(abs(x_ - x) <= error){
        return x_;
    }else{
        return Leration_(error, x_);
    }
}

int main(){
    std::cout << Leration(ERROR, 3.1415926) << std::endl;
    //std::cout << Leration_(ERROR, 3) << std::endl;
    return 0;
}