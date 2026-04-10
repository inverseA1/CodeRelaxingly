/*采用递归与回溯法求解八皇后问题。使用一维数组压缩表示棋盘状态，其中数组下标表
示行号、数组元素表示该行皇后所在列号；通过递归函数逐行放置皇后，并利用安全性检测
函数判断是否存在列冲突或对角线冲突；当当前位置不满足约束时，通过回溯机制撤销当前
决策并尝试新的列位置。程序在搜索过程中一旦成功在 8 行中放置所有皇后，即认为找到
一个可行解，立即输出棋盘布局并终止递归搜索，从而实现基于递归回溯策略的八皇后单解
求解与结果可视化。*/
#include <iostream>
#include <Windows.h>
using namespace std;
const int BOARD_SIZE = 8;

bool IsSafe(int* board, int row){
    for(int i = 0 ; i < row ; i++){
        if(board[i] == board[row] || abs(board[i]-board[row])==row-i){
            return false;
        }
    }
    return true;
}

void PrintBoard(int* board){
    for(int i = 0 ; i < BOARD_SIZE ; i++){
        for(int j = 0 ; j < BOARD_SIZE ; j++){
            if(j == board[i]){
                cout << "Q ";
            }else{
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << "-----------------------------" << endl;
}

// 递归回溯
bool SolveNQueensRecursive(int* board, int row){
    //调用到这一行了，如果这行还没放皇后，就要从第一列开始尝试，也就是从-1到0，如果放了，说明这里皇后位置不对，也要+1
    if(board[row] == BOARD_SIZE-1){
        //这一行由于之前行不正确而不能再放了，尝试之前行，凡是尝试之前行，都要重置这一行
        board[row] = -1;
        return SolveNQueensRecursive(board, row-1);
    }else{
        board[row]++;//这一行能放，就放
    }

    //检查皇后放在改行该列是否安全
    if(IsSafe(board, row)){
        //安全
        if(row == BOARD_SIZE-1){
            return true;//最后一行，求解完成，退出
        }else {
            //下一行
            return SolveNQueensRecursive(board, row +1);
        }
    }else {
        //不安全
        if(board[row] == BOARD_SIZE-1){
            //这一行所有列都不安全，上一行**注意重置这一行**
            return SolveNQueensRecursive(board, row-1);
        }else {
            //尝试下一列
            return SolveNQueensRecursive(board, row);
        }
    }
}

int main(){
    int board[BOARD_SIZE];
    // 初始化棋盘
    for(int i = 0; i < BOARD_SIZE; i++){
        board[i] = -1;
    }

    SetConsoleOutputCP(65001);
    cout << "八皇后问题（枚举法，只求一个解）" << endl;
    cout << "=================================" << endl;
    cout << "找到一个解：" << endl;
    if(SolveNQueensRecursive(board,0)){
        PrintBoard(board);
    }
    cout << "程序结束（已找到一个解）。" << endl;

    system("pause");
    return 0;
}