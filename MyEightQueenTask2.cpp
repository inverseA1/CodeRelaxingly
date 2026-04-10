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
bool SolveNQueensRecursive(int* board, int row) {
    // 边界安全：回溯到第0行之前表示无解
    if (row < 0) {
        return false;
    }

    // 如果当前行还没开始尝试，board[row] == -1；尝试下一列即 board[row]++
    // 如果当前行已经尝试过某些列，board[row] 指向当前列，继续尝试下一列
    board[row]++;

    // 如果当前行所有列都试完了（注意是 >= BOARD_SIZE，因为 board[row] 可能被加到 BOARD_SIZE）
    if (board[row] >= BOARD_SIZE) {
        board[row] = -1;          // 重置当前行，为下一次回溯到该行做准备
        return SolveNQueensRecursive(board, row - 1); // 回溯上一行
    }

    // 检查当前列是否安全
    if (IsSafe(board, row)) {
        if (row == BOARD_SIZE - 1) {
            return true; // 找到解
        }
        // 当前行安全，进入下一行（下一行的 board[row+1] 需为 -1，调用前已初始化）
        return SolveNQueensRecursive(board, row + 1);
    } else {
        // 当前列不安全，尝试当前行的下一列（递归调用自己，board[row] 在上次调用时已被+1）
        return SolveNQueensRecursive(board, row);
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