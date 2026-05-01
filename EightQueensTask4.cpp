/**
 * Task 4: Character Menu Interface
 * Eight Queens Problem Solver (Character Menu Version)
 *
 * Features:
 * - Character menu class implementation
 * - Console interactive program design
 * - Menu display, input validation
 */

#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

const int N = 8;

// ==================== QueenSolver Class ====================
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

    bool solveOne() {
        init();
        return solveRecursiveOne(0);
    }

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

    void solveRecursiveAll(int row) {
        for (int col = 0; col < n; col++) {
            if (isSafe(row, col)) {
                place(row, col);

                if (row == n - 1) {
                    solutionCount++;
                    displayCount++;

                    cout << "Solution #" << solutionCount << ":" << endl;
                    printBoard();
                    cout << endl;
                } else {
                    solveRecursiveAll(row + 1);
                }

                remove(row, col);
            }
        }
    }
};

// ==================== CharMenu Class ====================
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
        cout << "        0. Exit" << endl;
        cout << "==========================================" << endl;
    }

    int getChoice() {
        int choice;
        cout << "Enter your choice (0-" << optionCount << "): ";

        while (!(cin >> choice) || choice < 0 || choice > optionCount) {
            cout << "Invalid input, please re-enter (0-" << optionCount << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return choice;
    }

    void pause(const string& msg = "Press any key to continue...") {
        cout << msg << endl;
        cin.get();
    }
};

// ==================== Main Program ====================
int main() {
    QueenSolver solver(N);
    CharMenu menu("Eight Queens Solver (Beginner Version)");

    menu.addOption("Find one solution");
    menu.addOption("Find all solutions");
    menu.addOption("Manual solving (not implemented)");

    int choice;
    bool running = true;

    while (running) {
        cout << endl;
        menu.show();
        choice = menu.getChoice();

        switch (choice) {
            case 1: {
                cout << endl << "Finding one solution..." << endl;
                if (solver.solveOne()) {
                    cout << "Solution #1:" << endl;
                    solver.printBoard();
                }
                menu.pause();
                break;
            }
            case 2: {
                cout << endl << "Finding all solutions..." << endl;
                int count = solver.solveAll();
                cout << "==========================================" << endl;
                cout << "Done! Found " << count << " solutions." << endl;
                menu.pause();
                break;
            }
            case 3: {
                cout << endl << "Sorry, manual solving is not implemented." << endl;
                menu.pause();
                break;
            }
            case 0: {
                running = false;
                cout << endl << "Thank you!" << endl;
                break;
            }
        }
    }

    return 0;
}