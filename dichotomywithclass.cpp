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

class DICHOTOMY{
    private:
        double a;
        double b;
    public:
        void Geta(double a_){a = a_;}
        void Getb(double b_){b = b_;}
        double func(double x){
            return std::sin(x);
        }
        double dichotomy(){
            double m = (b+a)/2;
            if(b - a < error){
                return m;
            }else if((func(a)<0 && func(m)<0)||(func(a)>0 && func(m)>0)){
                a = m;
                return dichotomy();
            }else{
                b = m;
                return dichotomy();
            }
        }
};

int main(){
    DICHOTOMY MyDichotomy;
    MyDichotomy.Geta(3);
    MyDichotomy.Getb(4);
    std::cout<< std::setprecision(12) <<MyDichotomy.dichotomy();
    return 0;
}