/**
 * N-Queens Problem Solver
 * Universal N-Queens solver using vector
 *
 * Features:
 * - Dynamic array container vector usage
 * - Generalizes to N-Queens problem
 * - Supports arbitrary N (recommended 4 <= N <= 12)
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// ==================== NQueenSolver Class ====================
class NQueenSolver {
private:
    int n;
    vector<int> queen;
    vector<bool> colUsed;
    vector<bool> diag1Used;
    vector<bool> diag2Used;
    vector<vector<int>> solutions;
    int solutionCount;

public:
    NQueenSolver(int size = 8) : n(size), solutionCount(0) {
        init();
    }

    void setSize(int size) {
        n = size;
        init();
    }

    void init() {
        queen.assign(n, -1);
        colUsed.assign(n, false);
        diag1Used.assign(2 * n - 1, false);
        diag2Used.assign(2 * n - 1, false);
        solutions.clear();
        solutionCount = 0;
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

    void solveAll() {
        solutions.clear();
        solveRecursive(0);
        solutionCount = solutions.size();
    }

    bool solveOne() {
        init();
        return solveRecursiveOne(0);
    }

    int getSolutionCount() const {
        return solutionCount;
    }

    vector<int>& getSolution(int index) {
        static vector<int> empty;
        if (index >= 0 && index < (int)solutions.size()) {
            return solutions[index];
        }
        return empty;
    }

    vector<int>& getCurrentSolution() {
        return queen;
    }

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

// ==================== Menu Class ====================
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
        cout << "      N-Queens Solver" << endl;
        cout << "======================================" << endl;
        cout << "        1. Find one solution" << endl;
        cout << "        2. Find all solutions" << endl;
        cout << "        0. Exit" << endl;
        cout << "======================================" << endl;
    }

    void showSizeSelect() {
        cout << endl;
        cout << "======================================" << endl;
        cout << "      N-Queens Solver" << endl;
        cout << "======================================" << endl;
        cout << "Enter board size N (recommended 4<=N<=12, N<4 has no valid solution)" << endl;
        cout << "======================================" << endl;
    }

    int getChoice(int maxChoice) {
        int choice;
        cout << "Enter your choice (0-" << maxChoice << "): ";

        while (!(cin >> choice) || choice < 0 || choice > maxChoice) {
            cout << "Invalid input, please re-enter (0-" << maxChoice << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return choice;
    }

    int getBoardSize() {
        int size;
        cout << "Enter board size N: ";

        while (!(cin >> size) || size < 1 || size > 15) {
            cout << "Invalid input, enter a number between 1-15: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return size;
    }

    void pause(const string& msg = "Press any key to continue...") {
        cout << msg << endl;
        cin.get();
    }
};

// ==================== Main Program ====================
int main() {
    NQueenSolver solver(8);
    Menu menu("N-Queens Solver");
    int running = true;

    while (running) {
        menu.showSizeSelect();
        int n = menu.getBoardSize();
        solver.setSize(n);

        bool backToMenu = false;
        while (!backToMenu) {
            menu.showNQueenMenu();
            int choice = menu.getChoice(2);

            switch (choice) {
                case 1: {
                    cout << endl << "Solving for " << n << "-Queens..." << endl;
                    if (solver.solveOne()) {
                        cout << "Solution #1 (" << n << "-Queens):" << endl;
                        solver.printBoard();
                    } else {
                        cout << "No solution!" << endl;
                    }
                    menu.pause();
                    backToMenu = true;
                    break;
                }
                case 2: {
                    cout << endl << "Solving all solutions for " << n << "-Queens..." << endl;
                    solver.solveAll();
                    cout << "Found " << solver.getSolutionCount() << " solutions." << endl;

                    int count = solver.getSolutionCount();
                    int showCount = min(10, count);
                    for (int i = 0; i < showCount; i++) {
                        cout << endl << "Solution #" << (i + 1) << ":" << endl;
                        solver.printBoard(solver.getSolution(i));
                    }

                    if (count > 10) {
                        cout << endl << "... " << (count - 10) << " more solutions not shown" << endl;
                    }

                    menu.pause();
                    backToMenu = true;
                    break;
                }
                case 0: {
                    running = false;
                    backToMenu = true;
                    cout << endl << "Thank you for using!" << endl;
                    break;
                }
            }
        }
    }

    return 0;
}