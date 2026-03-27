/**
 * 任务6：N皇后问题
 * 通用N皇后求解器 - 使用vector动态数组容器
 * 
 * 功能：
 * - 动态数组容器vector使用
 * - 将问题推广到更通用的N皇后
 * - 支持任意N皇后问题求解（建议4≤N≤12）
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// ==================== N皇后求解器类 ====================
class NQueenSolver {
private:
    int n;                      // 棋盘规模
    vector<int> queen;          // 动态数组存储皇后位置
    vector<bool> colUsed;        // 列是否被占用
    vector<bool> diag1Used;      // 主对角线
    vector<bool> diag2Used;      // 副对角线
    vector<vector<int>> solutions;  // 保存所有解
    int solutionCount;          // 解的个数

public:
    NQueenSolver(int size = 8) : n(size), solutionCount(0) {
        init();
    }
    
    // 设置棋盘大小
    void setSize(int size) {
        n = size;
        init();
    }
    
    // 初始化
    void init() {
        queen.assign(n, -1);
        colUsed.assign(n, false);
        diag1Used.assign(2 * n - 1, false);
        diag2Used.assign(2 * n - 1, false);
        solutions.clear();
        solutionCount = 0;
    }
    
    // 检查是否安全
    bool isSafe(int row, int col) {
        return !colUsed[col] && 
               !diag1Used[row - col + n - 1] && 
               !diag2Used[row + col];
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
    
    // 求解所有解
    void solveAll() {
        solutions.clear();
        solveRecursive(0);
        solutionCount = solutions.size();
    }
    
    // 求一个解
    bool solveOne() {
        init();
        return solveRecursiveOne(0);
    }
    
    // 获取解的数量
    int getSolutionCount() const {
        return solutionCount;
    }
    
    // 获取指定解
    vector<int>& getSolution(int index) {
        static vector<int> empty;
        if (index >= 0 && index < (int)solutions.size()) {
            return solutions[index];
        }
        return empty;
    }
    
    // 获取当前解（最后一个求解的）
    vector<int>& getCurrentSolution() {
        return queen;
    }
    
    // 打印棋盘
    void printBoard(const vector<int>& q = vector<int>()) {
        const vector<int>& board = q.empty() ? queen : q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i] == j) {
                    cout << "Q ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }
    
private:
    // 递归求解（找所有解）
    void solveRecursive(int row) {
        for (int col = 0; col < n; col++) {
            if (isSafe(row, col)) {
                place(row, col);
                
                if (row == n - 1) {
                    solutions.push_back(queen);
                } else {
                    solveRecursive(row + 1);
                }
                
                remove(row, col);
            }
        }
    }
    
    // 递归求解（找一个解）
    bool solveRecursiveOne(int row) {
        for (int col = 0; col < n; col++) {
            if (isSafe(row, col)) {
                place(row, col);
                
                if (row == n - 1) {
                    return true;
                }
                
                if (solveRecursiveOne(row + 1)) {
                    return true;
                }
                
                remove(row, col);
            }
        }
        return false;
    }
};

// ==================== 菜单类 ====================
class Menu {
private:
    string title;
    
public:
    Menu(string t = "") : title(t) {}
    
    void setTitle(string t) {
        title = t;
    }
    
    void showNQueenMenu() {
        cout << endl;
        cout << "======================================" << endl;
        cout << "      N皇后问题求解系统" << endl;
        cout << "======================================" << endl;
        cout << "        1. 自动求一个解并演示" << endl;
        cout << "        2. 自动求所有解并演示" << endl;
        cout << "        0. 退出程序" << endl;
        cout << "======================================" << endl;
    }
    
    void showSizeSelect() {
        cout << endl;
        cout << "======================================" << endl;
        cout << "      N皇后问题求解系统" << endl;
        cout << "======================================" << endl;
        cout << "请输入棋盘大小N (建议4≤N≤12, N<4无有效解)" << endl;
        cout << "======================================" << endl;
    }
    
    int getChoice(int maxChoice) {
        int choice;
        cout << "请输入您的选择 (0-" << maxChoice << "): ";
        
        while (!(cin >> choice) || choice < 0 || choice > maxChoice) {
            cout << "输入无效，请重新输入 (0-" << maxChoice << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return choice;
    }
    
    int getBoardSize() {
        int size;
        cout << "请输入棋盘大小N: ";
        
        while (!(cin >> size) || size < 1 || size > 15) {
            cout << "输入无效，请输入1-15之间的数字: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return size;
    }
    
    void pause(const string& msg = "按任意键继续...") {
        cout << msg << endl;
        cin.get();
    }
};

// ==================== 主程序 ====================
int main() {
    NQueenSolver solver(8);  // 默认8皇后
    Menu menu("N皇后问题求解系统");
    int running = true;
    
    while (running) {
        // 选择棋盘大小
        menu.showSizeSelect();
        int n = menu.getBoardSize();
        solver.setSize(n);
        
        bool backToMenu = false;
        while (!backToMenu) {
            menu.showNQueenMenu();
            int choice = menu.getChoice(2);
            
            switch (choice) {
                case 1: {
                    cout << endl << "正在求解" << n << "皇后的一个解..." << endl;
                    if (solver.solveOne()) {
                        cout << "第 1 个解 (" << n << "皇后):" << endl;
                        solver.printBoard();
                    } else {
                        cout << "无解！" << endl;
                    }
                    menu.pause();
                    backToMenu = true;  // 返回选择大小
                    break;
                }
                case 2: {
                    cout << endl << "正在求解所有" << n << "皇后的解..." << endl;
                    solver.solveAll();
                    cout << "共找到 " << solver.getSolutionCount() << " 个解。" << endl;
                    
                    // 显示前10个解
                    int count = solver.getSolutionCount();
                    int showCount = min(10, count);
                    for (int i = 0; i < showCount; i++) {
                        cout << endl << "第 " << (i + 1) << " 个解:" << endl;
                        solver.printBoard(solver.getSolution(i));
                    }
                    
                    if (count > 10) {
                        cout << endl << "... 还有 " << (count - 10) << " 个解未显示" << endl;
                    }
                    
                    menu.pause();
                    backToMenu = true;  // 返回选择大小
                    break;
                }
                case 0: {
                    running = false;
                    backToMenu = true;
                    cout << endl << "感谢使用！" << endl;
                    break;
                }
            }
        }
    }
    
    return 0;
}