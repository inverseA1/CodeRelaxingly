/*
采用枚举法（非递归回溯模拟）求解八皇后问题：使用一维数组表示棋盘状态，逐行枚
举皇后在各列的可能位置，并通过安全性检测函数判断是否发生列冲突或对角线冲突；当某
一行无合法位置时，通过回退机制继续枚举上一行的其他列位置。程序在搜索过程中一旦找
到一个满足条件的可行解，立即在控制台输出当前棋盘布局，并终止搜索过程，从而实现对
八皇后问题的单解求解与棋盘可视化输出。
*/
#include <iostream>
#include <cmath>
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
    cout << "八皇后问题（枚举法，只求一个解）" << endl;
    cout << "=================================" << endl;
    cout << "找到一个解：" << endl;
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
    cout << "程序结束（已找到一个解）。" << endl;
}

// 非递归回溯，使用while循环实现
bool SolveNQueensNonRecursive(int* board){
    // 初始化棋盘
    for(int i = 0; i < BOARD_SIZE; i++){
        board[i] = -1;
    }

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
}

int main(){
    int board[BOARD_SIZE];

    if(SolveNQueensNonRecursive(board)){
        PrintBoard(board);
    }

    return 0;
}