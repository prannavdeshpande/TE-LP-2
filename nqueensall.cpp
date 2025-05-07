#include <iostream>
#include <vector>
using namespace std;

// Print 2D board
void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row)
            cout << cell << " ";
        cout << endl;
    }
    cout << endl;
}

// -------- BACKTRACKING (Row-wise) --------
bool isSafeBacktrack(const vector<vector<char>>& board, int row, int col, int n) {
    // Check column
    for (int i = 0; i < row; i++)
        if (board[i][col] == 'Q') return false;

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 'Q') return false;

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if (board[i][j] == 'Q') return false;

    return true;
}

void solveBacktracking(vector<vector<char>>& board, int row, int n, int& total) {
    if (row == n) {
        total++;
        printBoard(board);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafeBacktrack(board, row, col, n)) {
            board[row][col] = 'Q';
            solveBacktracking(board, row + 1, n, total);
            board[row][col] = '.'; // backtrack
        }
    }
}

// -------- BRANCH AND BOUND (Row-wise) --------
void solveBranchAndBound(vector<vector<char>>& board, vector<bool>& cols,
                         vector<bool>& diag1, vector<bool>& diag2, int row, int n, int& total) {
    if (row == n) {
        total++;
        printBoard(board);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (!cols[col] && !diag1[row + col] && !diag2[row - col + n - 1]) {
            board[row][col] = 'Q';
            cols[col] = diag1[row + col] = diag2[row - col + n - 1] = true;
            solveBranchAndBound(board, cols, diag1, diag2, row + 1, n, total);
            board[row][col] = '.'; // backtrack
            cols[col] = diag1[row + col] = diag2[row - col + n - 1] = false;
        }
    }
}

// -------- MAIN FUNCTION --------
int main() {
    char continueChoice;
    do {
        int n;
        cout << "\nEnter value of N for N-Queens (positive integer): ";
        cin >> n;

        // Input validation
        if (n <= 0) {
            cout << "N must be a positive integer. Try again.\n";
            continue;
        }

        int method;
        cout << "Choose solving method:\n";
        cout << "1. Backtracking\n";
        cout << "2. Branch and Bound\n";
        cout << "Enter choice (1 or 2): ";
        cin >> method;

        vector<vector<char>> board(n, vector<char>(n, '.'));
        int totalSolutions = 0;

        if (method == 1) {
            cout << "\n--- Solving using Backtracking (Row-wise) ---\n";
            solveBacktracking(board, 0, n, totalSolutions);
            cout << "Total Solutions (Backtracking): " << totalSolutions << "\n";
        }
        else if (method == 2) {
            vector<bool> cols(n, false), diag1(2 * n - 1, false), diag2(2 * n - 1, false);
            cout << "\n--- Solving using Branch and Bound (Row-wise) ---\n";
            solveBranchAndBound(board, cols, diag1, diag2, 0, n, totalSolutions);
            cout << "Total Solutions (Branch and Bound): " << totalSolutions << "\n";
        }
        else {
            cout << "Invalid method choice. Please select 1 or 2.\n";
        }

        cout << "\nDo you want to solve for another N? (y/n): ";
        cin >> continueChoice;
    } while (continueChoice == 'y' || continueChoice == 'Y');

    cout << "Thank you for using the N-Queens solver!\n";
    return 0;
}