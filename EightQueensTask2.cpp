/**
 * 任务2：递归和回溯法求一个可行解
 * 八皇后问题（递归+回溯，只求一个解）
 * 
 * 算法说明：
 * - 使用递归实现深度优先搜索
 * - 回溯法：尝试放置皇后，不安全则撤销（回溯）
 * - 找到第一个解后立即输出并结束程序
 */

#include <iostream>
#include <iomanip>
using namespace std;

const int N = 8;

int queen[N];  // queen[row] = col，第row行皇后在第col列

// 检查(row, col)位置是否安全
bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        int qCol = queen[i];
        // 列冲突或对角线冲突
        if (qCol == col || abs(qCol - col) == row - i) {
            return false;
        }
    }
    return true;
}

// 递归求解
bool solve(int row) {
    // 遍历当前行的所有列
    for (int col = 0; col < N; col++) {
        queen[row] = col;
        
        if (isSafe(row, col)) {
            // 位置安全
            if (row == N - 1) {
                // 最后一行，找到解
                return true;
            }
            // 递归搜索下一行
            if (solve(row + 1)) {
                return true;  // 找到解，一路返回
            }
            // 下一行没找到解，回溯（继续尝试当前行的下一列）
        }
        // 当前位置不安全，自动尝试下一列（queen[row]会被覆盖）
    }
    // 当前行所有列都不行，返回false触发回溯
    return false;
}

// 打印棋盘
void printBoard() {
    cout << "八皇后问题（递归+回溯，只求一个解）" << endl;
    cout << "========================================" << endl;
    cout << "找到一个解：" << endl;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (queen[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << "-----------------------------------------" << endl;
    cout << "程序结束（已找到一个解）。" << endl;
}

int main() {
    // 初始化
    for (int i = 0; i < N; i++) {
        queen[i] = -1;
    }
    
    if (solve(0)) {
        printBoard();
    }
    
    return 0;
}