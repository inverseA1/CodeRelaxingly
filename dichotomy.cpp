#include <iostream>
#include <iomanip>
#include <cmath>

const double error = 0.000000000001;

inline double func(double x){
    return std::sin(x);
}

inline double dichotomy(double a, double b){
    double m = (b+a)/2;
    if(b - a < error){
        return m;
    }else if((func(a)<0 && func(m)<0)||(func(a)>0 && func(m)>0)){
        return dichotomy(m,b);
    }else{
        return dichotomy(a,m);
    }
}

int main(){
    std::cout<< std::setprecision(12) <<dichotomy(3,4);
    return 0;
}