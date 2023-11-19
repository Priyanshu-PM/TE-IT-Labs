// Write a recursive program to find the solution of placing n queens on the 
// chessboard so that no two queens attack each other using
// Backtracking

#include <bits/stdc++.h>
using namespace std;

void printBoard(vector<vector<char>>& board, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(board[i][j] == 'Q')
                cout <<"Q ";
            else
                cout << ". ";
        }
        cout << "\n";
    }
}

bool isSafe(vector<vector<char>>& board, int row, int col, int n)
{

    //  checking on the left side
    for(int i = col; i >= 0; i--)
    {
        if(board[row][i] == 'Q')
            return false;
    }

    //  checking on the top left
    for(int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if(board[i][j] == 'Q')
            return false;
    }

    //  checking on the bottom left
    for(int i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if(board[i][j] == 'Q')
            return false;
    }

    return true;
}

bool solveNQueens(vector<vector<char>>& board, int col, int n)
{
    if(col >= n)
        return true;


    cout << "\n\nChecking for column number : " << col << endl;
    for(int i = 0; i < n; i++)
    {
        cout << "\nChecking if the queen can be placed in [ "<< i <<" "<< col << " ]\n";

        if(isSafe(board, i, col, n))
        {
            board[i][col] = 'Q';
            cout << "Placed the queen at "<< i << " " << col << " !\n";
            cout << "\nThe board will be : \n\n";

            if(solveNQueens(board, col+1, n))
            {
                return true;
            }

            cout << "\nBacktracking to check the other possibility \n\n";
            board[i][col] = '.';

            cout << "Hence the board will be : \n\n";
            printBoard(board, n);
        }
        else
        {
            cout << "\n\nNot possible to place the queen at : [ " << i << " " << col << " ]"<<endl;
            printBoard(board, n);
        }

    }
    return false;
}

void NQueens(int n)
{
    vector<vector<char>> board(n, vector<char>(n, '.'));
    if(solveNQueens(board, 0, n) == true)
    {
        cout << "\nThe solution is : \n";
        printBoard(board, n);
    }
    else
    {
        cout << "\nThe solution does not exists !!\n";
    }
}

int main()
{
    int n;
    cout << "Enter the number of Queens : ";
    cin >> n;

    NQueens(n);
    return 0;
}