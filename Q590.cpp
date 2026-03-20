/*
编写一个程序，将十进制短整型数n转换成二进制数。
输入提示信息："n="
输出信息格式：cout<<"the binary number is "<<...<<endl;
程序运行示例如下：
n=37
the binary number is 0000000000100101
*/
//#include <iostream> 
#define _CRT_SECURE_NO_WARNING_
#include <stdio.h>
using namespace std; 



int main() {
    int n; 
    printf("n=");
    if (scanf("%d",&n) != 1) return 0;

    char buf[17];
    // 将输入当作无符号短整型处理，输出16位二进制（含前导0）
    unsigned short ux = (unsigned short)n;
    for (int i = 15; i >= 0; --i) {
        buf[15 - i] = ((ux >> i) & 1) ? '1' : '0';
    }
    buf[16] = '\0';

    printf("the binary number is %s\n", buf);
    return 0;
}