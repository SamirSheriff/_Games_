#ifndef MISERE_TIC_TAC_TOE_H
#define MISERE_TIC_TAC_TOE_H

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class MisereBoard {
private:
    vector<vector<char>> board;
    int moves;

public:
    MisereBoard();
    void display_board();
    bool make_move(int x, int y, char symbol);
    bool is_losing_move(char symbol);
    bool is_draw();
};

class player {
private:
    string name;
    char symbol;

public:
    player(string n, char s);
    string get_name();
    char get_symbol();
    void get_move(int& x, int& y);
};

class MisereGameManager {
private:
    MisereBoard board;
    player* players[2];

public:
    MisereGameManager(player* p1, player* p2);
    void play_game();
};

MisereBoard::MisereBoard() {
    board = vector<vector<char>>(3, vector<char>(3, ' '));
    moves = 0;
}

void MisereBoard::display_board() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

bool MisereBoard::make_move(int x, int y, char symbol) {
    if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[x][y] == ' ') {
        board[x][y] = symbol;
        moves++;
        return true;
    }
    return false;
}

bool MisereBoard::is_losing_move(char symbol) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) ||  // Rows
            (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)) {  // Columns
            return true;
        }
    }
    if ((board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) ||      // Main diagonal
        (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)) {      // Anti-diagonal
        return true;
    }
    return false;
}

bool MisereBoard::is_draw() {
    return moves == 9;
}

player::player(string n, char s) : name(n), symbol(s) {}

string player::get_name() {
    return name;
}

char player::get_symbol() {
    return symbol;
}

void player::get_move(int& x, int& y) {
    cout << name << " (" << symbol << "), enter your move (row and column: 0-2): ";
    cin >> x >> y;
}

MisereGameManager::MisereGameManager(player* p1, player* p2) {
    players[0] = p1;
    players[1] = p2;
}

void MisereGameManager::play_game() {
    int x, y;
    int turn = 0;
    while (true) {
        board.display_board();
        player* current_player = players[turn % 2];


        do {
            current_player->get_move(x, y);
        } while (!board.make_move(x, y, current_player->get_symbol()));

        if (board.is_losing_move(current_player->get_symbol())) {
            board.display_board();
            cout << current_player->get_name() << " loses the game!\n";
            return;
        }

        if (board.is_draw()) {
            board.display_board();
            cout << "Draw!\n";
            return;
        }

        turn++;
    }
}

#endif
