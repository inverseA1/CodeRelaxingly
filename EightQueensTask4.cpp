/**
 * 任务4：字符菜单界面
 * 八皇后问题求解系统（字符菜单版）
 * 
 * 功能：
 * - 字符菜单类实现
 * - 控制台交互式程序设计
 * - 菜单展示、输入校验
 */

#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

const int N = 8;

// ==================== 棋盘求解器类 ====================
class QueenSolver {
private:
    int n;
    int* queen;
    bool* colUsed;
    bool* diag1Used;
    bool* diag2Used;
    int solutionCount;
    int displayCount;
    const int MAX_DISPLAY = 92;

public:
    QueenSolver(int n = N) : n(n), solutionCount(0), displayCount(0) {
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
        displayCount = 0;
    }
    
    bool isSafe(int row, int col) {
        return !colUsed[col] && !diag1Used[row - col + n - 1] && !diag2Used[row + col];
    }
    
    void place(int row, int col) {
        queen[row] = col;
        colUsed[col] = true;
        diag1Used[row - col + n - 1] = true;
        diag2Used[row + col] = true;
    }
    
    void remove(int row, int col) {
        queen[row] = -1;
        colUsed[col] = false;
        diag1Used[row - col + n - 1] = false;
        diag2Used[row + col] = false;
    }
    
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
    
    // 求一个解并演示
    bool solveOne() {
        init();
        return solveRecursiveOne(0);
    }
    
    // 求所有解
    int solveAll() {
        init();
        solveRecursiveAll(0);
        return solutionCount;
    }
    
private:
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
    
    // 递归求所有解
    void solveRecursiveAll(int row) {
        for (int col = 0; col < n; col++) {
            if (isSafe(row, col)) {
                place(row, col);
                
                if (row == n - 1) {
                    // 找到一个解
                    solutionCount++;
                    displayCount++;
                    
                    // 显示所有解
                    cout << "第 " << solutionCount << " 个解：" << endl;
                    printBoard();
                    cout << endl;
                } else {
                    solveRecursiveAll(row + 1);
                }
                
                remove(row, col);
            }
        }
        // 自动返回，上一行继续尝试其他列
    }
};

// ==================== 字符菜单类 ====================
class CharMenu {
private:
    string title;
    string* options;
    int optionCount;
    
public:
    CharMenu(string t = "") : title(t), options(NULL), optionCount(0) {}
    
    ~CharMenu() {
        if (options) delete[] options;
    }
    
    void setTitle(string t) {
        title = t;
    }
    
    void addOption(string opt) {
        string* newOptions = new string[optionCount + 1];
        for (int i = 0; i < optionCount; i++) {
            newOptions[i] = options[i];
        }
        newOptions[optionCount++] = opt;
        if (options) delete[] options;
        options = newOptions;
    }
    
    void show() {
        cout << "==========================================" << endl;
        cout << "        " << title << endl;
        cout << "==========================================" << endl;
        for (int i = 0; i < optionCount; i++) {
            cout << "        " << (i + 1) << ". " << options[i] << endl;
        }
        cout << "        0. 退出程序" << endl;
        cout << "==========================================" << endl;
    }
    
    int getChoice() {
        int choice;
        cout << "请输入您的选择 (0-" << optionCount << "): ";
        
        while (!(cin >> choice) || choice < 0 || choice > optionCount) {
            cout << "输入无效，请重新输入 (0-" << optionCount << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return choice;
    }
    
    void pause(const string& msg = "按任意键继续...") {
        cout << msg << endl;
        cin.get();
    }
};

// ==================== 主程序 ====================
int main() {
    QueenSolver solver(N);
    CharMenu menu("八皇后问题求解系统（初学者版）");
    
    menu.addOption("自动求一个解并演示");
    menu.addOption("自动求所有解并演示");
    menu.addOption("手动求解（暂未实现）");
    
    int choice;
    bool running = true;
    
    while (running) {
        cout << endl;
        menu.show();
        choice = menu.getChoice();
        
        switch (choice) {
            case 1: {
                cout << endl << "正在求解一个解..." << endl;
                if (solver.solveOne()) {
                    cout << "第 1 个解：" << endl;
                    solver.printBoard();
                }
                menu.pause();
                break;
            }
            case 2: {
                cout << endl << "正在求解所有解..." << endl;
                int count = solver.solveAll();
                cout << "==========================================" << endl;
                cout << "演示完成！共找到 " << count << " 个解。" << endl;
                menu.pause();
                break;
            }
            case 3: {
                cout << endl << "抱歉，手动求解功能暂未实现。" << endl;
                menu.pause();
                break;
            }
            case 0: {
                running = false;
                cout << endl << "感谢使用！" << endl;
                break;
            }
        }
    }
    
    return 0;
}