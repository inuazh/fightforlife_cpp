#include <iostream>
#include <vector>
using namespace std;

const int M = 8;
const int N = 8;

const char PLAYER1 = 'X';
const char PLAYER2 = 'O';
const char EMPTY = '.';

void displayBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isSurrounded(const vector<vector<char>>& board, int x, int y, char opponent) {
    int count = 0;
    if (x > 0 && board[x - 1][y] == opponent) count++;
    if (x < M - 1 && board[x + 1][y] == opponent) count++;
    if (y > 0 && board[x][y - 1] == opponent) count++;
    if (y < N - 1 && board[x][y + 1] == opponent) count++;
    return count >= 3;
}

bool canPlaceNewPiece(const vector<vector<char>>& board, int x, int y, char player) {
    int count = 0;
    if (x > 0 && board[x - 1][y] == player) count++;
    if (x < M - 1 && board[x + 1][y] == player) count++;
    if (y > 0 && board[x][y - 1] == player) count++;
    if (y < N - 1 && board[x][y + 1] == player) count++;
    return count >= 3;
}

void makeMove(vector<vector<char>>& board, int x1, int y1, int x2, int y2, char player) {
    if (board[x1][y1] == player && board[x2][y2] == EMPTY) {
        board[x1][y1] = EMPTY;
        board[x2][y2] = player;
    }
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == PLAYER1 && isSurrounded(board, i, j, PLAYER2)) {
                board[i][j] = EMPTY;
            } else if (board[i][j] == PLAYER2 && isSurrounded(board, i, j, PLAYER1)) {
                board[i][j] = EMPTY;
            }
            if (board[i][j] == EMPTY && canPlaceNewPiece(board, i, j, PLAYER1)) {
                board[i][j] = PLAYER1;
            } else if (board[i][j] == EMPTY && canPlaceNewPiece(board, i, j, PLAYER2)) {
                board[i][j] = PLAYER2;
            }
        }
    }
}

bool hasPieces(const vector<vector<char>>& board, char player) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == player) return true;
        }
    }
    return false;
}

int main() {
    vector<vector<char>> board(M, vector<char>(N, EMPTY));

    board[0][0] = PLAYER1;
    board[0][1] = PLAYER1;
    board[M - 1][N - 1] = PLAYER2;
    board[M - 1][N - 2] = PLAYER2;

    displayBoard(board);

    char currentPlayer = PLAYER1;
    while (hasPieces(board, PLAYER1) && hasPieces(board, PLAYER2)) {
        int x1, y1, x2, y2;
        cout << "Ход игрока " << currentPlayer << ": введите координаты (x1 y1) -> (x2 y2): ";
        cin >> x1 >> y1 >> x2 >> y2;

        makeMove(board, x1, y1, x2, y2, currentPlayer);
        displayBoard(board);

        currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    }

    if (hasPieces(board, PLAYER1)) {
        cout << "Игрок X победил!" << endl;
    } else {
        cout << "Игрок O победил!" << endl;
    }

    return 0;
}
