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
}

// 递归回溯
bool SolveNQueensRecursive(int* board, int row, int col){
/*
    int row = 0;
    int col = 0;

    while(row >= 0){
        // 尝试在当前行找到一列可以放置皇后
        while(col < BOARD_SIZE){
            board[row] = col;
            if(IsSafe(board, row)){
                break;  // 找到安全位置，停止搜索列
            }
            col++;  // 尝试下一列
        }

        // 如果当前行没有找到安全的位置，回溯
        if(col >= BOARD_SIZE){
            board[row] = -1;  // 清除当前位置
            row--;            // 回溯到上一行
            if(row < 0){
                return false;  // 无解
            }
            col = board[row] + 1;  // 从上一行的下一列继续
            board[row] = -1;        // 清除上一行的记录，准备尝试新位置
        }
        // 检查是否找到完整解
        else if(row == BOARD_SIZE - 1){
            return true;  // 找到解
        }
        // 准备搜索下一行
        else{
            row++;
            col = 0;
        }
    }

    return false;
*/
    
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
    if(SolveNQueensRecursive(board)){
        PrintBoard(board);
    }
    cout << "-----------------------------" << endl;
    cout << "程序结束（已找到一个解）。" << endl;

    system("pause");
    return 0;
}