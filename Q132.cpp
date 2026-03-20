//#include <iostream> 
#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <vector>
using namespace std; 

int Average(vector<int> vec){
    int len = vec.size();
    int sum = 0;
    for(int i = 0 ; i < len ; i++){
        sum += vec[i];
    }
    return sum / len;
}

void PrintVec(vector<int> vec){
    int len = vec.size();
    for(int i = 0 ; i < len ; i++){
        printf("%d ",vec[i]);
    }
}

int main() { 
    vector<int> score = { 0 };
    int tmp = 0;
    int i = 0;
    do{
        printf("Input score:");
        scanf("%d",&tmp);
        if(i == 0){
            score[i] = tmp;
        }else{
            score.push_back(tmp);
        }
        i++;
    }while(score[i-1] >= 0);

    score.pop_back();
    //PrintVec(score);
    int total = score.size();
    printf("Total students are %d\nAverage score is %d\n",total,Average(score));


    return 0;
}/*
用函数编程统计平均成绩。要求在主函数中输入学生成绩，输入负数时,结束输入，调用子函数Average()计算平均成绩，并输出结果。
函数原型：int Average(int score[],int n)
****要求输入提示信息为："Input score:"
****输出格式要求为：
"Total students are %d\n"
"Average score is %d\n"
*/