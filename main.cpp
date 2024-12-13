#include <iostream>

#include "3x3X_O.h"
#include "TicTacToe5x5.h"
using namespace std;

TicTacToe5x5::TicTacToe5x5() : movesLeft(24) {
    board.resize(size, vector<char>(size, ' '));
}

void TicTacToe5x5::display_board() {
    cout << "\n  ";
    for (int i = 0; i < size; i++) cout << i << "   ";
    cout << "\n";

    for (int i = 0; i < size; i++) {
        cout << i << " ";
        for (int j = 0; j < size; j++) {
            cout << board[i][j];
            if (j < size - 1) cout << " | ";
        }
        cout << "\n";
        if (i < size - 1) cout << "  " << string(size * 4 - 3, '-') << "\n";
    }
    cout << endl;
}

bool TicTacToe5x5::is_valid_move(int x, int y) {
    return x >= 0 && x < size && y >= 0 && y < size && board[x][y] == ' ';
}

bool TicTacToe5x5::place_mark(int x, int y, char symbol) {
    if (!is_valid_move(x, y)) return false;
    board[x][y] = symbol;
    movesLeft--;
    return true;
}

int TicTacToe5x5::count_sequences(char symbol) {
    int count = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 2; j++) {
            if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol)
                count++;
            if (board[j][i] == symbol && board[j + 1][i] == symbol && board[j + 2][i] == symbol)
                count++;
        }
    }

    for (int i = 0; i < size - 2; i++) {
        for (int j = 0; j < size - 2; j++) {
            if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol)
                count++;
            if (board[i][j + 2] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j] == symbol)
                count++;
        }
    }

    return count;
}

pair<int, int> TicTacToe5x5::determine_winner() {
    int x_count = count_sequences('X');
    int o_count = count_sequences('O');
    return {x_count, o_count};
}

bool TicTacToe5x5::is_full() {
    return movesLeft <= 0;
}

int main() {
    TicTacToe5x5 game;
    char currentPlayer = 'X';

    while (!game.is_full()) {
        game.display_board();
        int x, y;

        cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        cin >> x >> y;

        if (!game.place_mark(x, y, currentPlayer)) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    game.display_board();
    pair<int, int> result = game.determine_winner();

    cout << "Game Over!\n";
    cout << "Player X: " << result.first << " three-in-a-rows\n";
    cout << "Player O: " << result.second << " three-in-a-rows\n";

    if (result.first > result.second)
        cout << "Player X wins!\n";
    else if (result.second > result.first)
        cout << "Player O wins!\n";
    else
        cout << "It's a draw!\n";

    return 0;
}
