#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // CHECK IF SAFE
    bool isSafe(vector<string> &board, int row, int col, int n) {

        // check column (vertical)
        for(int i = 0; i < row; i++) {
            if(board[i][col] == 'Q')
                return false;
        }

        // left diagonal
        for(int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if(board[i][j] == 'Q')
                return false;
        }

        // right diagonal
        for(int i = row, j = col; i >= 0 && j < n; i--, j++) {
            if(board[i][j] == 'Q')
                return false;
        }

        return true;
    }

    // RECURSIVE FUNCTION
    void nQueens(vector<string> &board, int row, int n, vector<vector<string>> &ans) {

        // base case
        if(row == n) {
            ans.push_back(board);
            return;
        }

        // try placing queen in every column
        for(int j = 0; j < n; j++) {

            if(isSafe(board, row, j, n)) {

                board[row][j] = 'Q';   // place
                nQueens(board, row + 1, n, ans);
                board[row][j] = '.';   // backtrack
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {

        vector<vector<string>> ans;

        // empty board
        vector<string> board(n, string(n, '.'));

        nQueens(board, 0, n, ans);

        return ans;
    }
};


int main() {
int n;
cout << "Enter size of chessboard (n): ";
cin >> n;

Solution obj;
vector<vector<string>> result = obj.solveNQueens(n);
int count=0;
if(result.empty()) {
    cout << "No solutions exist.\n";
} else {
    cout << "Solutions:\n";
    for(auto &sol : result) {
        for(auto &row : sol) {
            cout << row << endl;
            
        }
        count++;
        cout << endl;
    }
}
cout<<"count is :"<<count<<endl;
return 0;

}