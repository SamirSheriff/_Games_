#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "misere_tic_tac_toe.h"

using namespace std;

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

Player::Player(string n, char s) : name(n), symbol(s) {}

string Player::get_name() {
    return name;
}

char Player::get_symbol() {
    return symbol;
}

void Player::get_move(int& x, int& y) {
    cout << name << " (" << symbol << "), enter your move (row and column: 0-2): ";
    cin >> x >> y;
}

AIPlayer::AIPlayer(string n, char s) : Player(n, s) {}

void AIPlayer::get_move(int& x, int& y, MisereBoard& board) {
    srand(time(0));
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (!board.make_move(x, y, get_symbol()));
    cout << name << " chooses: " << x << " " << y << endl;
}

MisereGameManager::MisereGameManager(Player* p1, Player* p2) {
    players[0] = p1;
    players[1] = p2;
}

void MisereGameManager::play_game() {
    int x, y;
    int turn = 0;
    while (true) {
        board.display_board();
        Player* current_player = players[turn % 2];

        if (AIPlayer* ai = dynamic_cast<AIPlayer*>(current_player)) {
            ai->get_move(x, y, board);
        } else {
            do {
                current_player->get_move(x, y);
            } while (!board.make_move(x, y, current_player->get_symbol()));
        }

        if (board.is_losing_move(current_player->get_symbol())) {
            board.display_board();
            cout << current_player->get_name() << " loses the game!\n";
            return;
        }

        if (board.is_draw()) {
            board.display_board();
            cout << "The game is a draw!\n";
            return;
        }

        turn++;
    }
}

int main() {
    cout << "Welcome to Misere Tic Tac Toe!\n";
    cout << "Avoid getting three marks in a row!\n\n";

    cout << "Menu:\n";
    cout << "1. Play against another player\n";
    cout << "2. Play against AI\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    Player* player1 = new Player("Player 1", 'X');
    Player* player2;

    if (choice == 1) {
        player2 = new Player("Player 2", 'O');
    } else {
        player2 = new AIPlayer("AI Player", 'O');
    }

    MisereGameManager game(player1, player2);
    game.play_game();

    delete player1;
    delete player2;

    return 0;
}
