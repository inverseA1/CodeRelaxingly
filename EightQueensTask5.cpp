/**
 * Task 5: 图形界面八皇后问题求解器
 * Eight Queens Problem Solver (EasyX Graphic Version)
 *
 * Features:
 * - EasyX graphic library for visualization
 * - Recursive backtracking algorithm
 * - Direct display of solutions (no search animation)
 * - Menu-driven interface
 */

#include <iostream>
#include <vector>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <limits>
using namespace std;

// ==================== Constants ====================
const int CELL_SIZE = 60;
const int WINDOW_MARGIN = 20;
const int BOARD_SIZE = 8;
const int WINDOW_WIDTH = CELL_SIZE * BOARD_SIZE + WINDOW_MARGIN * 2;
const int WINDOW_HEIGHT = CELL_SIZE * BOARD_SIZE + WINDOW_MARGIN * 2;
const int QUEEN_RADIUS = CELL_SIZE / 3;

// ==================== EightQueensSolver Class ====================
class EightQueensSolver {
private:
    int board[BOARD_SIZE];           // Row -> Column, -1 means empty
    int solutionCount;               // Solution counter
    vector<vector<int>> allSolutions; // Store all solutions
    HWND hwnd;                      // EasyX window handle

public:
    EightQueensSolver() : solutionCount(0), hwnd(NULL) {
        resetState();
    }

    // Reset all state
    void resetState() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            board[i] = -1;
        }
        solutionCount = 0;
        allSolutions.clear();
    }

    // Check if position (row, col) is safe
    bool isSafe(int row, int col) {
        for (int i = 0; i < row; i++) {
            int qCol = board[i];
            // Same column
            if (qCol == col) return false;
            // Main diagonal
            if (row - i == col - qCol) return false;
            // Anti-diagonal
            if (row + col == i + qCol) return false;
        }
        return true;
    }

    // Place queen at (row, col)
    void place(int row, int col) {
        board[row] = col;
    }

    // Remove queen from (row, col)
    void remove(int row, int col) {
        board[row] = -1;
    }

    // Draw the chessboard
    void drawBoard() {
        // Draw background
        setbkcolor(RGB(240, 240, 240));
        cleardevice();

        // Draw cells
        for (int row = 0; row < BOARD_SIZE; row++) {
            for (int col = 0; col < BOARD_SIZE; col++) {
                int x = WINDOW_MARGIN + col * CELL_SIZE;
                int y = WINDOW_MARGIN + row * CELL_SIZE;

                // Checkerboard pattern
                if ((row + col) % 2 == 0) {
                    setfillcolor(RGB(255, 255, 255));  // White
                } else {
                    setfillcolor(RGB(128, 128, 128));  // Gray
                }
                fillrectangle(x, y, x + CELL_SIZE, y + CELL_SIZE);
            }
        }

        // Draw queens
        for (int row = 0; row < BOARD_SIZE; row++) {
            if (board[row] >= 0) {
                int col = board[row];
                int centerX = WINDOW_MARGIN + col * CELL_SIZE + CELL_SIZE / 2;
                int centerY = WINDOW_MARGIN + row * CELL_SIZE + CELL_SIZE / 2;

                // Queen is a red circle
                setfillcolor(RGB(255, 0, 0));
                setcolor(RGB(255, 0, 0));
                fillcircle(centerX, centerY, QUEEN_RADIUS);
            }
        }

        // Draw grid lines
        setcolor(RGB(64, 64, 64));
        for (int i = 0; i <= BOARD_SIZE; i++) {
            // Vertical lines
            line(WINDOW_MARGIN + i * CELL_SIZE, WINDOW_MARGIN,
                 WINDOW_MARGIN + i * CELL_SIZE, WINDOW_MARGIN + BOARD_SIZE * CELL_SIZE);
            // Horizontal lines
            line(WINDOW_MARGIN, WINDOW_MARGIN + i * CELL_SIZE,
                 WINDOW_MARGIN + BOARD_SIZE * CELL_SIZE, WINDOW_MARGIN + i * CELL_SIZE);
        }
    }

    // Draw solution number
    void drawSolutionNumber(int num) {
        char text[64];
        sprintf(text, "%d", num);
        char prefix[32] = "Solution #";

        settextstyle(20, 0, _T("Arial"));
        setbkcolor(RGB(240, 240, 240));
        setcolor(RGB(0, 0, 0));

        outtextxy(WINDOW_MARGIN, 5, prefix);
        outtextxy(WINDOW_MARGIN + 100, 5, text);
    }

    // Solve one solution and display
    bool solveOneAndShow() {
        resetState();
        bool found = solveRecursiveOne(0);
        if (found) {
            drawBoard();
            drawSolutionNumber(1);
        }
        return found;
    }

    // Solve all solutions and display (1 second per solution)
    int solveAllAndShow() {
        resetState();
        collectAllSolutions(0);

        // Display each solution for 1 second
        for (size_t i = 0; i < allSolutions.size(); i++) {
            // Copy solution to board
            for (int row = 0; row < BOARD_SIZE; row++) {
                board[row] = allSolutions[i][row];
            }
            drawBoard();
            drawSolutionNumber(i + 1);
            if (i < allSolutions.size() - 1) {
                Sleep(1000);
                flushmessage();
            }
        }
        return allSolutions.size();
    }

    // Get current board state
    int* getBoard() {
        return board;
    }

    // Get solution count
    int getSolutionCount() const {
        return solutionCount;
    }

private:
    // Recursive solve (find one)
    bool solveRecursiveOne(int row) {
        if (row == BOARD_SIZE) {
            solutionCount++;
            return true;
        }

        for (int col = 0; col < BOARD_SIZE; col++) {
            if (isSafe(row, col)) {
                place(row, col);

                if (solveRecursiveOne(row + 1)) {
                    return true;
                }

                remove(row, col);
            }
        }
        return false;
    }

    // Recursive solve (collect all solutions)
    void collectAllSolutions(int row) {
        if (row == BOARD_SIZE) {
            vector<int> sol;
            for (int i = 0; i < BOARD_SIZE; i++) {
                sol.push_back(board[i]);
            }
            allSolutions.push_back(sol);
            solutionCount++;
            return;
        }

        for (int col = 0; col < BOARD_SIZE; col++) {
            if (isSafe(row, col)) {
                place(row, col);
                collectAllSolutions(row + 1);
                remove(row, col);
            }
        }
    }
};

// ==================== QueenMenu Class ====================
class QueenMenu {
private:
    string title;

public:
    QueenMenu(string t = "") : title(t) {}

    void setTitle(string t) {
        title = t;
    }

    // Show main menu
    void showMenu() {
        cout << endl;
        cout << "======================================" << endl;
        cout << "       " << title << endl;
        cout << "======================================" << endl;
        cout << "       1. 自动查找一个解" << endl;
        cout << "       2. 自动查找所有解" << endl;
        cout << "       3. 手动求解（暂未实现）" << endl;
        cout << "       0. 退出" << endl;
        cout << "======================================" << endl;
    }

    // Get user choice with validation
    int getChoice() {
        int choice;
        cout << "请输入您的选择 (0-3): ";

        // First check: non-numeric input
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            cout << "输入错误！请输入 0-3 的数字！" << endl;
            cout << "按任意键继续..." << endl;
            _getch();
            return -1;
        }

        // Second check: out of range
        if (choice < 0 || choice > 3) {
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            cout << "输入错误！请选择 0-3 之间的选项！" << endl;
            cout << "按任意键继续..." << endl;
            _getch();
            return -1;
        }

        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return choice;
    }

    void pause(const string& msg = "按任意键继续...") {
        cout << msg << endl;
        _getch();
    }
};

// ==================== Main Program ====================
int main() {
    EightQueensSolver solver;
    QueenMenu menu("八皇后求解器系统");

    bool running = true;
    while (running) {
        menu.showMenu();
        int choice = menu.getChoice();

        if (choice == -1) {
            continue;  // Invalid input, show menu again
        }

        switch (choice) {
            case 1: {
                cout << endl << "正在查找一个解..." << endl;
                cout << "图形窗口即将打开！" << endl;

                initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
                SetWindowText(GetHWnd(), "八皇后求解器");

                bool found = solver.solveOneAndShow();

                if (found) {
                    cout << "找到解！正在显示..." << endl;
                }

                cout << "按任意键关闭图形窗口..." << endl;
                _getch();
                closegraph();

                cout << "第1个解:" << endl;
                cout << "(解已在图形窗口中显示)" << endl;
                break;
            }

            case 2: {
                cout << endl << "正在查找所有解..." << endl;
                cout << "图形窗口已打开！（每1秒切换一次）" << endl;

                initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
                SetWindowText(GetHWnd(), "八皇后求解器");

                int count = solver.solveAllAndShow();

                cout << "按任意键关闭图形窗口..." << endl;
                _getch();
                closegraph();

                cout << "共找到解的数量: " << count << endl;
                cout << "(" << count << " 个解已在图形窗口中显示)" << endl;
                break;
            }

            case 3: {
                cout << endl << "抱歉，手动求解功能暂未实现。" << endl;
                menu.pause();
                break;
            }

            case 0: {
                running = false;
                cout << endl << "感谢使用八皇后求解器！" << endl;
                cout << "再见！" << endl;
                break;
            }
        }
    }

    return 0;
}