//#include <iostream> 
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
using namespace std; 

inline int GetDig1(int n){ return (n % 10); }
inline int GetDig2(int n){ return (n % 100 / 10); }
inline int GetDig3(int n){ return (n % 1000 / 100); }

bool IsSqure(int n){
    if( n == 0 || n == 1 || n == 4 || n == 9 || n == 16 || n == 25 || n == 36 || n == 49 || n == 64 || n == 81)
    return true;
    else
    return false;
}

int main() { 
    int n1, n2, n3;
    printf("The possible perfect squares combinations are:\n");
    for(int i = 10 ; i*i < 1000 ; i++){
        for(int j = 10 ; j*j < 1000 ; j++){
            n1 = GetDig1(i*i) *10 + GetDig1(j*j);
            n2 = GetDig2(i*i) *10 + GetDig2(j*j);
            n3 = GetDig3(i*i) *10 + GetDig3(j*j);
            if(IsSqure(n1) && IsSqure(n2) && IsSqure(n3)){
                printf(" %d and %d\n",i*i,j*j);
            }
        }
    }
    return 0;
}/*
由二个平方三位数获得三个平方二位数。已知两个平方三位数abc和xyz，其中未必是不同的；而ax、by、cz是三个平方二位数。请编程求三位数abc和xyz。
**输出格式要求："The possible perfect squares combinations are:\n" " %d and %d\n"
程序运行示例如下：
The possible perfect squares combinations are:
 400 and 900
 841 and 196
*/