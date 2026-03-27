/**
 * 任务3：基于类的全部解
 * 八皇后问题 - 面向对象实现，求解所有92个解
 * 
 * 算法说明：
 * - 使用类封装 queensolver 类
 * - 递归回溯法求所有解
 * - 解空间遍历
 */

#include <iostream>
#include <iomanip>
using namespace std;

const int N = 8;

class QueenSolver {
private:
    int n;              // 棋盘规模
    int* queen;         // queen[row] = col
    bool* colUsed;     // 列是否被占用
    bool* diag1Used;    // 主对角线 (row - col)
    bool* diag2Used;    // 副对角线 (row + col)
    int solutionCount;  // 解的个数

public:
    QueenSolver(int n = N) : n(n), solutionCount(0) {
        queen = new int[n];
        colUsed = new bool[n];
        diag1Used = new bool[2 * n - 1];
        diag2Used = new bool[2 * n - 1];
    }
    
    ~QueenSolver() {
        delete[] queen;
        delete[] colUsed;
        delete[] diag1Used;
        delete[] diag2Used;
    }
    
    // 初始化
    void init() {
        for (int i = 0; i < n; i++) {
            queen[i] = -1;
            colUsed[i] = false;
        }
        for (int i = 0; i < 2 * n - 1; i++) {
            diag1Used[i] = false;
            diag2Used[i] = false;
        }
        solutionCount = 0;
    }
    
    // 检查(row, col)是否安全
    bool isSafe(int row, int col) {
        return !colUsed[col] && !diag1Used[row - col + n - 1] && !diag2Used[row + col];
    }
    
    // 放置皇后
    void place(int row, int col) {
        queen[row] = col;
        colUsed[col] = true;
        diag1Used[row - col + n - 1] = true;
        diag2Used[row + col] = true;
    }
    
    // 移除皇后（回溯）
    void remove(int row, int col) {
        queen[row] = -1;
        colUsed[col] = false;
        diag1Used[row - col + n - 1] = false;
        diag2Used[row + col] = false;
    }
    
    // 打印棋盘
    void printBoard() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (queen[i] == j) {
                    cout << "Q ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }
    
    // 递归求解所有解
    void solve(int row = 0) {
        for (int col = 0; col < n; col++) {
            if (isSafe(row, col)) {
                place(row, col);
                
                if (row == n - 1) {
                    // 找到一个解
                    solutionCount++;
                    cout << "第 " << solutionCount << " 个解：" << endl;
                    printBoard();
                    cout << endl;
                    // 不返回，继续搜索下一个解
                } else {
                    // 递归搜索下一行
                    solve(row + 1);
                }
                
                // 回溯，尝试当前行的下一列
                remove(row, col);
            }
        }
        // 当前行所有列都不行，自动返回触发回溯
    }
    
    int getSolutionCount() {
        return solutionCount;
    }
    
    // 展示单个解（带装饰）
    void displaySolution(int solutionNum) {
        cout << "========================================" << endl;
        cout << "第 " << solutionNum << " 个解：" << endl;
        cout << "========================================" << endl;
        printBoard();
        cout << endl;
    }
};

int main() {
    QueenSolver solver(N);
    solver.init();
    
    cout << "八皇后问题（递归回溯，求全部解）" << endl;
    cout << "========================================" << endl;
    cout << endl;
    
    solver.solve(0);
    
    cout << "========================================" << endl;
    cout << "总共有 " << solver.getSolutionCount() << " 个解。" << endl;
    cout << "程序结束。" << endl;
    
    return 0;
}