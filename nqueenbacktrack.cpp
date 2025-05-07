#include<iostream>
#include<vector>
using namespace std;
vector<vector<char>>grid;

bool isSafeQueen(int row,int col, int n){
    // column
    for(int i=row-1;i>=0;i--){
        if(grid[i][col]=='Q') return false;
    }
    //left digonal
    for(int i=row-1,j=col-1;i>=0&&j>=0;i--,j--){
        if(grid[i][j]=='Q') return false;
    }
    //right digonal
    
    for(int i=row-1,j=col+1;i>=0&&j<n;i--,j++){
        if(grid[i][j]=='Q') return false;
    }
    return true;
}

void f(int row,int n){
    if(row==n){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cout<<grid[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    for(int col=0;col<n;col++){
        if(isSafeQueen(row,col,n)){
            grid[row][col] = 'Q';
            f(row+1,n);
            grid[row][col] = '.';
        }
    }
}
void nqueen(int n){
    f(0,n);
}
int main(){
    int n = 4;
    grid.clear();
    grid.resize(n,vector<char>(n,'.'));
    nqueen(n);

}









class Solution {
    public:
        bool isSafeQueen(vector<vector<char>>& Grid, int row, int col, int n)
        {
            // Check column
            for (int i = row - 1; i >= 0; i--) {
                if (Grid[i][col] == 'Q') return false;
            }
            // Check upper-left diagonal
            for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
                if (Grid[i][j] == 'Q') return false;
            }
            // Check upper-right diagonal
            for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
                if (Grid[i][j] == 'Q') return false;
            }
            return true;
        }
    
        void nqueens(vector<vector<char>>& Grid, int row, int n, vector<vector<string>>& ans)
        {
            if (row == n)
            {
                vector<string> temp;
                for (int i = 0; i < n; i++)
                {
                    string s(Grid[i].begin(), Grid[i].end());
                    temp.push_back(s);
                }
                ans.push_back(temp);
                return;
            }
    
            for (int j = 0; j < n; j++)
            {
                if (isSafeQueen(Grid, row, j, n))
                {
                    Grid[row][j] = 'Q';
                    nqueens(Grid, row + 1, n, ans);
                    Grid[row][j] = '.'; // backtrack
                }
            }
        }
    
        vector<vector<string>> solveNQueens(int n)
        {
            vector<vector<char>> Grid(n, vector<char>(n, '.'));  // Initialize board with '.'
            vector<vector<string>> ans;
            nqueens(Grid, 0, n, ans);  // Start from row 0
            return ans;
        }
    };
    