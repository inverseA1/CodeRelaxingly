/**
 * Task 5: Graphic Interface Based Solution Output
 * Eight Queens Problem Solver (EasyX Graphic Version)
 *
 * Features:
 * - EasyX graphic library for visualization
 * - Recursive backtracking algorithm
 * - Animation showing search and backtracking process
 * - Menu-driven interface
 */

#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
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
    bool foundOneSolution;           // Mode flag: find one or all
    HWND hwnd;                      // EasyX window handle

public:
    EightQueensSolver() {
        resetState();
    }

    // Reset all state
    void resetState() {
        for (int i = 0; i < BOARD_SIZE; i++) {
            board[i] = -1;
        }
        solutionCount = 0;
        foundOneSolution = false;
    }

    // Check if position (row, col) is safe
    bool isSafe(int row, int col) {
        for (int i = 0; i < row; i++) {
            int qCol = board[i];
            // Same column
            if (qCol == col) return false;
            // Main diagonal (row - col == row - col)
            if (row - i == col - qCol) return false;
            // Anti-diagonal (row + col == row + col)
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
    void drawBoard(int currentRow = -1, int currentCol = -1) {
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

        // Highlight current trying position
        if (currentRow >= 0 && currentCol >= 0 && board[currentRow] == -1) {
            setfillcolor(RGB(255, 255, 0));  // Yellow highlight
            int x = WINDOW_MARGIN + currentCol * CELL_SIZE;
            int y = WINDOW_MARGIN + currentRow * CELL_SIZE;
            fillrectangle(x, y, x + CELL_SIZE, y + CELL_SIZE);
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
        sprintf(text, "第 %d 个解", num);

        settextstyle(20, 0, _T("Arial"));
        setbkcolor(RGB(240, 240, 240));
        setcolor(RGB(0, 0, 0));
        outtextxy(WINDOW_MARGIN, 5, text);
    }

    // Solve one solution with animation
    bool solveOneWithAnimation(HWND hwnd) {
        this->hwnd = hwnd;
        foundOneSolution = true;
        resetState();
        return solveRecursiveAnimation(0);
    }

    // Solve all solutions with animation
    int solveAllWithAnimation(HWND hwnd) {
        this->hwnd = hwnd;
        foundOneSolution = false;
        resetState();
        solveRecursiveAllAnimation(0);
        return solutionCount;
    }

private:
    // Recursive solve with animation (find one)
    bool solveRecursiveAnimation(int row) {
        if (row == BOARD_SIZE) {
            // Found a solution
            solutionCount++;
            drawBoard();
            drawSolutionNumber(solutionCount);
            Sleep(2000);  // Show for 2 seconds
            return true;
        }

        for (int col = 0; col < BOARD_SIZE; col++) {
            // Highlight current trying position
            drawBoard(row, col);
            drawSolutionNumber(0);
            Sleep(100);  // Animation delay
            flushmessage();

            if (isSafe(row, col)) {
                place(row, col);
                drawBoard();
                drawSolutionNumber(solutionCount + 1);
                Sleep(100);
                flushmessage();

                if (solveRecursiveAnimation(row + 1)) {
                    return true;
                }

                // Backtrack
                remove(row, col);
                drawBoard();
                drawSolutionNumber(0);
                Sleep(100);
                flushmessage();
            }
        }
        return false;
    }

    // Recursive solve with animation (find all)
    void solveRecursiveAllAnimation(int row) {
        if (row == BOARD_SIZE) {
            solutionCount++;
            drawBoard();
            drawSolutionNumber(solutionCount);
            Sleep(1000);  // Show each solution for 1 second
            return;
        }

        for (int col = 0; col < BOARD_SIZE; col++) {
            // Highlight current trying position
            drawBoard(row, col);
            drawSolutionNumber(solutionCount + 1);
            Sleep(50);  // Shorter delay for searching
            flushmessage();

            if (isSafe(row, col)) {
                place(row, col);
                drawBoard();
                drawSolutionNumber(solutionCount + 1);
                Sleep(50);
                flushmessage();

                solveRecursiveAllAnimation(row + 1);

                // Backtrack
                remove(row, col);
                drawBoard();
                drawSolutionNumber(solutionCount + 1);
                Sleep(50);
                flushmessage();
            }
        }
    }

public:
    // Get solution count
    int getSolutionCount() const {
        return solutionCount;
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
        cout << "       1. Auto find one solution" << endl;
        cout << "       2. Auto find all solutions" << endl;
        cout << "       3. Manual solving (N/A)" << endl;
        cout << "       0. Exit" << endl;
        cout << "======================================" << endl;
    }

    // Get user choice with validation
    int getChoice() {
        int choice;
        cout << "Enter your choice (0-3): ";

        // First check: non-numeric input
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input error! Please enter a number 0-3!" << endl;
            cout << "Press any key to continue..." << endl;
            _getch();
            return -1;
        }

        // Second check: out of range
        if (choice < 0 || choice > 3) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input error! Please choose options between 0-3!" << endl;
            cout << "Press any key to continue..." << endl;
            _getch();
            return -1;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return choice;
    }

    void pause(const string& msg = "Press any key to continue...") {
        cout << msg << endl;
        _getch();
    }
};

// ==================== Main Program ====================
int main() {
    EightQueensSolver solver;
    QueenMenu menu("Eight Queens Solver System");

    bool running = true;
    while (running) {
        menu.showMenu();
        int choice = menu.getChoice();

        if (choice == -1) {
            continue;  // Invalid input, show menu again
        }

        switch (choice) {
            case 1: {
                cout << endl << "Finding one solution..." << endl;
                cout << "Graphic window will open soon!" << endl;

                initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
                HWND hwnd = GetHWnd();
                SetWindowText(hwnd, "Eight Queens Solver");

                bool found = solver.solveOneWithAnimation(hwnd);

                if (found) {
                    cout << "Solution found! Displaying..." << endl;
                }

                cout << "Press any key to close graphic window..." << endl;
                _getch();
                closegraph();

                cout << "Solution #1:" << endl;
                // Print to console as well
                int board[8];
                // We don't have direct access to board, so just show completion
                cout << "(Solution shown in graphic window)" << endl;
                break;
            }

            case 2: {
                cout << endl << "Finding all solutions..." << endl;
                cout << "Graphic window will open! (Switch every 1 second)" << endl;

                initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
                HWND hwnd = GetHWnd();
                SetWindowText(hwnd, "Eight Queens Solver");

                int count = solver.solveAllWithAnimation(hwnd);

                cout << "Press any key to close graphic window..." << endl;
                _getch();
                closegraph();

                cout << "Total solutions found: " << count << endl;
                cout << "(All " << count << " solutions shown in graphic window)" << endl;
                break;
            }

            case 3: {
                cout << endl << "Sorry, manual solving is not implemented." << endl;
                menu.pause();
                break;
            }

            case 0: {
                running = false;
                cout << endl << "Thank you for using Eight Queens Solver!" << endl;
                cout << "Goodbye!" << endl;
                break;
            }
        }
    }

    return 0;
}