#include <bits/stdc++.h>
using namespace std;


void printSolution(vector<vector<char>>& board, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
		if(board[i][j] == 'Q')
			cout << "Q ";
		else 
            cout<<". ";
		printf("\n");
	}
}

bool isSafe(vector<vector<char>>& board, int row, int col, int n)
{
	int i, j;

	// Check this row on left side
	for (i = 0; i < col; i++)
		if (board[row][i] == 'Q')
			return false;

	// Check upper diagonal on left side
	for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
		if (board[i][j] == 'Q')
			return false;

	// Check lower diagonal on left side
	for (i = row, j = col; j >= 0 && i < n; i++, j--)
		if (board[i][j] == 'Q')
			return false;

	return true;
}

bool solveNQueens(vector<vector<char>>& board, int col, int n)
{

	if (col >= n)	return true;

    cout << "\n\nChecking for column number : " << col <<endl;

	for (int i = 0; i < n; i++) {

        cout << "\nChecking if the queen can be placed in " << "[ " << i << " " <<col << " ]" << endl; 
		if (isSafe(board, i, col, n)) {
            
			board[i][col] = 'Q';
            cout << "Placed the queen at " << i << " " << col << " !"<< endl;
            cout << "\nThe board will be : \n\n";

            printSolution(board, n);

			if (solveNQueens(board, col + 1, n)) {
				return true;
            }

            cout << "\nBacktracking to check the other possibility \n\n";
			board[i][col] = '.'; // BACKTRACK

            cout << "Hence the board will be : \n\n";
            printSolution(board, n);
		}
        else {
            cout << "\n\nNot possible to place the queen at : [ " << i << " " << col << " ]"<<endl;
            printSolution(board, n);
        }
	}

	return false;
}

void solveNQ(int n)
{
	vector<vector<char>> board(n, vector<char>(n, '.'));

	if (solveNQueens(board, 0, n) == false) {
		cout << "Solution does not exist";
	}
    else {
        cout << "\n\nHence, the final board will be this : \n\n";
	    printSolution(board, n);
        cout << "\n";
    }
}

int main()
{
    int n;
    cout << "Enter the number of columns : ";
    cin >> n;
	solveNQ(n);
	return 0;
}
