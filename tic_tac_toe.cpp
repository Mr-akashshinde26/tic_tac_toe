#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char EMPTY = ' ';
const int SIZE = 3;

void printBoard(const vector<vector<char>>& board) {
    system("cls");  // Clear screen, use "clear" on Unix-based systems
    cout << "   1   2   3\n";
    cout << "  +---+---+---+\n";
    for (int i = 0; i < SIZE; ++i) {
        cout << i + 1 << " | ";
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << " | ";
        }
        cout << " |\n";
        if (i < SIZE - 1) cout << "  +---+---+---+\n";
    }
    cout << "  +---+---+---+\n";
    cout << '\n';
}

bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows
    for (int i = 0; i < SIZE; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }
    // Check columns
    for (int j = 0; j < SIZE; ++j) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return true;
    }
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

bool checkDraw(const vector<vector<char>>& board) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == EMPTY)
                return false;
        }
    }
    return true;
}

bool isValidMove(int row, int col, const vector<vector<char>>& board) {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == EMPTY;
}

void playTicTacToe() {
    vector<vector<char>> board(SIZE, vector<char>(SIZE, EMPTY));
    char currentPlayer = 'X';
    bool gameEnded = false;

    while (!gameEnded) {
        printBoard(board);
        int row, col;
        cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        
        while (!(cin >> row >> col) || row < 1 || row > SIZE || col < 1 || col > SIZE) {
            cout << "Invalid input. Please enter numbers between 1 and " << SIZE << " for both row and column: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        row--; col--;

        if (isValidMove(row, col, board)) {
            board[row][col] = currentPlayer;
            if (checkWin(board, currentPlayer)) {
                printBoard(board);
                cout << "Player " << currentPlayer << " wins!\n";
                gameEnded = true;
            } else if (checkDraw(board)) {
                printBoard(board);
                cout << "The game is a draw!\n";
                gameEnded = true;
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        } else {
            cout << "Invalid move, the cell is already occupied. Try again.\n";
        }
    }
}

int main() {
    char playAgain;
    do {
        playTicTacToe();
        cout << "Do you want to play again? (Y/N): ";
        
        while (!(cin >> playAgain) || (playAgain != 'Y' && playAgain != 'N' && playAgain != 'y' && playAgain != 'n')) {
            cout << "Invalid input. Please enter 'Y' for yes or 'N' for no: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
    } while (playAgain == 'Y' || playAgain == 'y');

    return 0;
}