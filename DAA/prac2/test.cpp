#include <bits/stdc++.h>
using namespace std;

void solve(int col, vector<string>& board, vector<vector<string>>& ans, vector<int>& leftRow, vector<int>& lowerDiagonal, vector<int>& upperDiagonal, int n) {

    if(col == n) {  // if solution exists, then store the solution
        ans.push_back(board);
        return;
    }

    for(int row = 0; row < n; row++) {

        if(leftRow[row] == 0 && lowerDiagonal[row+col] == 0 && upperDiagonal[n-1 + col-row] == 0) 
        {
            board[row][col] = 'Q';
            leftRow[row] = 1;
            lowerDiagonal[row+col] = 1;
            upperDiagonal[n-1+col - row] = 1;
            solve(col+1, board, ans, leftRow, lowerDiagonal, upperDiagonal, n);

            // backtracking to check other options
            board[row][col] = '.';
            leftRow[row] = 0;
            lowerDiagonal[row+col] = 0;
            upperDiagonal[n-1+col-row] = 0;
        }
    }
}

vector<vector<string>> solveNQueens(int n) {

    vector<vector<string>> ans;

    vector<string> board(n);
    string s(n, '.');
    for(int i = 0; i < n; i++) {
        board[i] = s;
    }
    vector<int> leftRow(n, 0), lowerDiagonal(2*n-1, 0), upperDiagonal(2*n-1, 0);

    solve(0, board, ans, leftRow, lowerDiagonal, upperDiagonal, n);
    return ans;
}

void printBoard(vector<vector<string>>& ans) {

    int count = 1;
    for(vector<string> board: ans) {
        
        cout << "Solution number : "<< count << endl;
        for(string row: board) {

            for(int i = 0; i < row.size(); i++) {
                if(row[i] == '.')
                    cout << ". ";

                else
                    cout << "Q ";
            
            }
            cout << endl;
        }
        count++;
        cout << endl;
    }

}

int main() {

    int n;
    cout << "Enter the number of columns for chessboard\n";
    cout << "(min 4 | max 8) : ";
    cin >> n;

    vector<vector<string>> ans = solveNQueens(n);

    if(ans.size() == 0)
        cout << "Solution does not exist !!" << endl;
    else 
        printBoard(ans);

    return 0;
}