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

    for(int i = col; i >= 0; i--)
    {
        if(board[row][i] == 'Q')
            return false;
    }

    for(int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if(board[i][j] == 'Q')
            return false;
    }

    for(int i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if(board[i][j] == 'Q')
            return false;
    }

    return true;
}

void solveNQueens(vector<vector<vector<char>>>& solutions, vector<vector<char>>& board, int col, int n)
{
    if(col >= n)
    {
        solutions.push_back(board);
        return;
    }
    
    cout << "\n\nChecking for column number : " << col <<endl;
    for(int i = 0; i < n; i++)
    {
        if(isSafe(board, i, col, n))
        {
            board[i][col] = 'Q';
            solveNQueens(solutions, board, col+1, n);

            cout << "\nBacktracking to check the other possibility \n\n";
            board[i][col] = '.';

            cout << "Hence the board will be : \n\n";
            printSolution(board, n);
            
        }   
        else
        {
            cout << "\n\nNot possible to place the queen at : [ " << i << " " << col << " ]"<<endl;
            printSolution(board, n);
        }
    }

}


void solveNQ(int n)
{
	vector<vector<char>> board(n, vector<char>(n, '.'));
    vector<vector<vector<char>>> solutions;

	solveNQueens(solutions, board, 0, n);

    if(solutions.size() > 0)
    {
        cout << "Solution exists : \n";
        cout << "Printing the solution :\n";
        int i = 1;
        for(vector<vector<char>> board: solutions)
        {
            cout << "\nSolution number : "<<i << "\n\n";
            printSolution(board, n);
            i++;
        }

        cout << "\n";
    }
    else
    {
        cout << "\nNo solution exists !!\n\n";
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