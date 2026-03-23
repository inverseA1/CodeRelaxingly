#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> board(n, string(n, '.'));  // 初始棋盘
        vector<bool> col(n, false), diag1(2*n-1, false), diag2(2*n-1, false);
        backtrack(0, n, board, col, diag1, diag2, res);
        return res;
    }

private:
    void backtrack(int row, int n, vector<string>& board,
                   vector<bool>& col, vector<bool>& diag1, vector<bool>& diag2,
                   vector<vector<string>>& res) {
        if (row == n) {
            res.push_back(board);
            return;
        }
        for (int c = 0; c < n; ++c) {
            int d1 = row - c + n - 1;  // 主对角线索引（偏移保证非负）
            int d2 = row + c;          // 副对角线索引
            if (col[c] || diag1[d1] || diag2[d2]) continue;
            // 放置皇后
            board[row][c] = 'Q';
            col[c] = diag1[d1] = diag2[d2] = true;
            backtrack(row + 1, n, board, col, diag1, diag2, res);
            // 回溯：撤销皇后
            board[row][c] = '.';
            col[c] = diag1[d1] = diag2[d2] = false;
        }
    }
};

int main(){
    Solution sol;
    vector<vector<string>> res = sol.solveNQueens(12);
    for(int i = 0 ; i < res.size() ; i++){
        for(int j = 0 ; j < res[i].size() ; j++){
            cout<< res[i][j] << endl;
        }
        cout << endl;
    }
    return 0;
}