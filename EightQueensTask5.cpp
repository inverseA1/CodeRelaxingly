/**
 * Task 5: Graphics Interface Implementation
 * Eight Queens Problem - EasyX Graphics Version
 *
 * Features:
 * - EasyX graphics library basics
 * - Board drawing with 8x8 grid
 * - Queen circle drawing with red color
 * - Menu-driven interface (0-3 options)
 * - Solution navigation with arrow keys
 *
 * Compilation (Visual Studio):
 * 1. Download and install EasyX: https://easyx.cn/
 * 2. Create a project in VS and include this file
 * 3. Ensure EasyX include and lib paths are configured in project properties
 */

#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <vector>
#include <string>
#include <Windows.h>
using namespace std;

const int N = 8;
const int CELL_SIZE = 60;                       // Size of each cell
const int BOARD_SIZE = N * CELL_SIZE;            // Total board size
const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 700;

// Color definitions
const int COLOR_BOARD_LIGHT = RGB(240, 240, 240);   // Light cell color
const int COLOR_BOARD_DARK = RGB(180, 180, 180);    // Dark cell color
const int COLOR_QUEEN = RED;                         // Queen color (red)
const int COLOR_BOARD_LINE = RGB(80, 80, 80);       // Board line color
const int COLOR_BG = WHITE;                          // Background color

// ==================== EightQueensSolver Class ====================
class EightQueensSolver {
private:
    int n;
    vector<int> queen;
    vector<vector<int>> solutions;
    bool* colUsed;
    bool* diag1Used;
    bool* diag2Used;
    int solutionCount;
    bool foundOneSolution;

public:
    EightQueensSolver(int size = N) : n(size), solutionCount(0), foundOneSolution(false) {
        queen.resize(n, -1);
        colUsed = new bool[n];
        diag1Used = new bool[2 * n - 1];
        diag2Used = new bool[2 * n - 1];
    }

    ~EightQueensSolver() {
        delete[] colUsed;
        delete[] diag1Used;
        delete[] diag2Used;
    }

    void resetState() {
        fill(queen.begin(), queen.end(), -1);
        fill(colUsed, colUsed + n, false);
        fill(diag1Used, diag1Used + 2 * n - 1, false);
        fill(diag2Used, diag2Used + 2 * n - 1, false);
        solutions.clear();
        solutionCount = 0;
        foundOneSolution = false;
    }

    bool isSafe(int row, int col) {
        return !colUsed[col] &&
               !diag1Used[row - col + n - 1] &&
               !diag2Used[row + col];
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

    // Solve one solution - stops after finding first solution
    bool solveOneSolution() {
        resetState();
        return solveRecursiveOne(0);
    }

    // Solve all solutions
    int solveAllSolutions() {
        resetState();
        solveRecursiveAll(0);
        return solutionCount;
    }

    // Manual solving - not implemented yet
    void solveManual() {
        cout << "手动求解功能暂未实现" << endl;
    }

    int getSolutionCount() const {
        return solutionCount;
    }

    vector<vector<int>>& getSolutions() {
        return solutions;
    }

private:
    bool solveRecursiveOne(int row) {
        for (int col = 0; col < n; col++) {
            if (isSafe(row, col)) {
                place(row, col);

                if (row == n - 1) {
                    solutions.push_back(queen);
                    solutionCount++;
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

    void solveRecursiveAll(int row) {
        for (int col = 0; col < n; col++) {
            if (isSafe(row, col)) {
                place(row, col);

                if (row == n - 1) {
                    solutionCount++;
                    solutions.push_back(queen);
                } else {
                    solveRecursiveAll(row + 1);
                }

                remove(row, col);
            }
        }
    }
};

// ==================== QueenMenu Class ====================
class QueenMenu {
private:
    string title;
    string* options;
    int optionCount;

public:
    QueenMenu(string t = "") : title(t), options(NULL), optionCount(0) {}

    ~QueenMenu() {
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
        cout << "        0. Exit" << endl;
        cout << "==========================================" << endl;
    }

    int getChoice() {
        int choice;
        cout << "Enter your choice (0-" << optionCount << "): ";

        while (!(cin >> choice) || choice < 0 || choice > optionCount) {
            cout << "输入错误！请输入数字 0-" << optionCount << "！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press any key to continue..." << endl;
            _getch();
            return -1;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return choice;
    }

    void pause(const string& msg = "Press any key to continue...") {
        cout << msg << endl;
        cin.get();
    }
};

// ==================== GraphicsBoard Class ====================
class GraphicsBoard {
private:
    int solutionNum;
    int totalSolutions;

public:
    GraphicsBoard() : solutionNum(0), totalSolutions(0) {}

    void initGraph() {
        initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
        setbkcolor(COLOR_BG);
        cleardevice();
    }

    void closeGraph() {
        closegraph();
    }

    void setSolutionInfo(int current, int total) {
        solutionNum = current;
        totalSolutions = total;
    }

    // Draw the board
    void drawBoard() {
        // Draw cells
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                int x = col * CELL_SIZE;
                int y = row * CELL_SIZE;

                // Chess board coloring
                if ((row + col) % 2 == 0) {
                    setfillcolor(COLOR_BOARD_LIGHT);
                } else {
                    setfillcolor(COLOR_BOARD_DARK);
                }

                // Fill cell
                solidrectangle(x, y, x + CELL_SIZE, y + CELL_SIZE);
            }
        }

        // Draw border
        setlinestyle(PS_SOLID, 3);
        setlinecolor(COLOR_BOARD_LINE);
        rectangle(0, 0, BOARD_SIZE, BOARD_SIZE);

        // Draw inner grid lines
        setlinestyle(PS_SOLID, 1);
        for (int i = 1; i < N; i++) {
            // Vertical lines
            line(i * CELL_SIZE, 0, i * CELL_SIZE, BOARD_SIZE);
            // Horizontal lines
            line(0, i * CELL_SIZE, BOARD_SIZE, i * CELL_SIZE);
        }
    }

    // Draw queens (red circles with Q)
    void drawQueens(const vector<int>& queen) {
        for (int row = 0; row < N; row++) {
            int col = queen[row];
            if (col == -1) continue;

            int x = col * CELL_SIZE + CELL_SIZE / 2;
            int y = row * CELL_SIZE + CELL_SIZE / 2;
            int radius = CELL_SIZE / 2 - 10;

            // Draw red solid circle
            setfillcolor(COLOR_QUEEN);
            solidcircle(x, y, radius);

            // Draw border
            setlinecolor(DARKGRAY);
            setlinestyle(PS_SOLID, 2);
            circle(x, y, radius);

            // Draw Q letter at center
            setbkmode(TRANSPARENT);
            setcolor(WHITE);
            settextstyle(20, 0, "Arial");
            outtextxy(x - 8, y - 12, "Q");
        }
    }

    // Display "第 X 个解" at top-left of board
    void drawSolutionLabel() {
        if (totalSolutions == 0) return;

        char label[50];
        sprintf(label, "第 %d 个解", solutionNum);

        setbkmode(TRANSPARENT);
        setcolor(BLACK);
        settextstyle(20, 0, "Microsoft YaHei");
        outtextxy(10, 10, label);
    }

    // Display info panel on the right
    void drawInfo() {
        // Right info panel background
        setfillcolor(RGB(245, 245, 245));
        solidrectangle(BOARD_SIZE + 10, 10, WINDOW_WIDTH - 10, 180);
        setlinecolor(RGB(200, 200, 200));
        rectangle(BOARD_SIZE + 10, 10, WINDOW_WIDTH - 10, 180);

        // Title
        setbkcolor(RGB(245, 245, 245));
        setcolor(BLACK);
        settextstyle(24, 0, "Microsoft YaHei");
        outtextxy(BOARD_SIZE + 30, 30, "八皇后问题求解系统");

        // Current solution info
        char buf[100];
        sprintf(buf, "当前: %d / %d", solutionNum, totalSolutions);
        settextstyle(18, 0, "Microsoft YaHei");
        outtextxy(BOARD_SIZE + 30, 80, buf);

        sprintf(buf, "共 %d 个解", totalSolutions);
        outtextxy(BOARD_SIZE + 30, 110, buf);

        // Hint info
        setcolor(DARKGRAY);
        settextstyle(14, 0, "Microsoft YaHei");
        outtextxy(BOARD_SIZE + 30, 150, "Left/Right: Prev/Next");
    }

    // Display operation tips at bottom
    void drawTips() {
        setfillcolor(RGB(245, 245, 245));
        solidrectangle(BOARD_SIZE + 10, WINDOW_HEIGHT - 80, WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10);
        setlinecolor(RGB(200, 200, 200));
        rectangle(BOARD_SIZE + 10, WINDOW_HEIGHT - 80, WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10);

        setbkcolor(RGB(245, 245, 245));
        setcolor(DARKGRAY);
        settextstyle(14, 0, "Microsoft YaHei");
        outtextxy(BOARD_SIZE + 30, WINDOW_HEIGHT - 65, "操作说明:");
        outtextxy(BOARD_SIZE + 30, WINDOW_HEIGHT - 45, "Left/Right: 切换解");
        outtextxy(BOARD_SIZE + 30, WINDOW_HEIGHT - 25, "ESC: 返回菜单");
    }

    // Draw one solution with animation
    void drawOneSolution(const vector<int>& queen, int current, int total) {
        setSolutionInfo(current, total);

        BeginBatchDraw();
        cleardevice();

        drawBoard();
        drawQueens(queen);
        drawSolutionLabel();
        drawInfo();
        drawTips();

        FlushBatchDraw();
        EndBatchDraw();
    }

    // Draw all solutions with 1 second interval
    void drawAllSolutions(vector<vector<int>>& solutions, int total) {
        int count = 0;
        for (int i = 0; i < total; i++) {
            count = i + 1;
            drawOneSolution(solutions[i], count, total);
            Sleep(1000);  // 1 second delay
        }
    }
};

// ==================== Input Validation Functions ====================
void clearInputBuffer() {
    while (_kbhit()) {
        _getch();
    }
}

int getMenuChoice() {
    int choice;
    while (true) {
        cout << "Enter your choice (0-3): ";

        if (!(cin >> choice)) {
            cout << "输入错误！请输入数字 0-3！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press any key to continue..." << endl;
            _getch();
            clearInputBuffer();
            return -1;
        }

        if (choice < 0 || choice > 3) {
            cout << "输入错误！请选择 0-3 之间的选项！" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press any key to continue..." << endl;
            _getch();
            clearInputBuffer();
            return -1;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return choice;
    }
}

// ==================== Main Program ====================
int main() {
    EightQueensSolver solver(N);
    GraphicsBoard board;
    QueenMenu menu("八皇后问题求解系统");

    menu.addOption("自动求一个解并演示");
    menu.addOption("自动求所有解并演示");
    menu.addOption("手动求解");

    int choice;
    bool running = true;

    while (running) {
        system("cls");  // Clear screen
        menu.show();
        choice = menu.getChoice();

        switch (choice) {
            case 1: {
                // Find one solution and display with graphics
                cout << endl << "正在求解一个解..." << endl;

                bool found = solver.solveOneSolution();

                if (found) {
                    cout << "找到解！正在显示..." << endl;

                    board.initGraph();

                    vector<vector<int>>& solutions = solver.getSolutions();
                    board.drawOneSolution(solutions[0], 1, 1);

                    // Wait for ESC key
                    bool showRunning = true;
                    while (showRunning) {
                        char key = _getch();
                        if (key == 27) {  // ESC
                            showRunning = false;
                        }
                    }

                    board.closeGraph();
                } else {
                    cout << "未找到解！" << endl;
                    cout << "Press any key to continue..." << endl;
                    _getch();
                }
                break;
            }
            case 2: {
                // Find all solutions and display with graphics
                cout << endl << "正在求解所有解..." << endl;

                int count = solver.solveAllSolutions();
                cout << "共找到 " << count << " 个解，正在演示..." << endl;

                if (count > 0) {
                    board.initGraph();

                    vector<vector<int>>& solutions = solver.getSolutions();
                    board.drawAllSolutions(solutions, count);

                    cout << "演示完成！" << endl;
                    cout << "Press any key to return to menu..." << endl;
                    _getch();

                    board.closeGraph();
                }
                break;
            }
            case 3: {
                // Manual solving - not implemented
                cout << endl << "手动求解功能暂未实现" << endl;
                cout << "Press any key to continue..." << endl;
                _getch();
                break;
            }
            case 0: {
                running = false;
                cout << endl << "感谢使用！" << endl;
                break;
            }
            case -1: {
                // Invalid input, continue to next iteration
                break;
            }
        }

        if (running) {
            cout << endl;
        }
    }

    return 0;
}