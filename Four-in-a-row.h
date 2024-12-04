#ifndef _FOUR_IN_A_ROW_H
#define _FOUR_IN_A_ROW_H

#include"BoardGame_Classes.h"

// Last move
int row, col;
char mark;

class FourInARowBoard : public Board<char> {
private:
    int countRow, countRD, countLD;
    bool checkWinner(int x, int y, int addRow, int addCol);

public:
    FourInARowBoard();
    bool update_board (int x , int y , char symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

class FourInARowPlayer : public Player<char> {
public:
    static int turn;
    FourInARowPlayer(string name, char symbol);
    void getmove(int& x, int& y);
};
int FourInARowPlayer::turn = 1;


class FourInARow_Random_Player : public RandomPlayer<char>{
public:
    FourInARow_Random_Player (char symbol);
    void getmove(int &x, int &y) ;
};


//--------------------------------------- IMPLEMENTATION ----------------------------


bool FourInARowBoard::checkWinner(int x, int y, int addRow, int addCol){
    for (int i = 1; i < 4; ++i) {
        int idxRow = x - i * addRow, idxCol = y + i * addCol;
        if (idxRow < 0 || idxRow > 5 || idxCol < 0 || idxCol > 6 || this->board[idxRow][idxCol] != mark)
            return false;

        if ((addRow == 0 && addCol == 1) || (addRow == 0 && addCol == -1))
            countRow++;
        else if ((addRow == 1 && addCol == 1) || (addRow == -1 && addCol == -1))
            countRD++;
        else if ((addRow == 1 && addCol == -1) || (addRow == -1 && addCol == 1))
            countLD++;
    }
    return true;
}

// Constructor FourInARowBoard
FourInARowBoard::FourInARowBoard() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

bool FourInARowBoard::update_board(int x, int y, char symbol) {
    if (y < 1 || y > 7)
        return false;

    for (int i = 5; i >= 0; i--) {
        if (this->board[i][y-1] == ' '){
            this->board[i][y-1] = symbol;
            row = i;
            col = y - 1;
            mark = symbol;
            FourInARowPlayer::turn++;
            return true;
        }
    }
    return false;
}

// Display the board and the pieces on it
void FourInARowBoard::display_board() {
    if (FourInARowPlayer::turn % 2)
        cout << string(43, '-') << "\n\t       Turn: Player 1\n" << string(43, '-') << "\n";
    else
        cout << string(43, '-') << "\n\t       Turn: Player 2\n" << string(43, '-') << "\n";

    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(3) << this->board[i][j] << "  |";
        }
        cout << endl << string(43, '-');
    }

    cout << endl;
    for (int i = 1; i < 8; ++i) {
        cout << setw(4) << i << "  ";
    }
    cout << endl << endl;
}

bool FourInARowBoard::is_win() {
    countRow = this->countRD = countLD = 1;

    if (checkWinner(row, col, -1, 0) || checkWinner(row, col, 0, 1) ||
        checkWinner(row, col, 0, -1) || checkWinner(row, col, 1, 1) ||
        checkWinner(row, col, -1, -1) || checkWinner(row, col, 1, -1) ||
        checkWinner(row, col,-1, 1)){
        return true;
    }

    if (countRow >= 4 || countRD >= 4 || countLD >= 4)
        return true;

    return false;
}

bool FourInARowBoard::is_draw() {
    for (int c = 0; c < 7; ++c) {
        if (this->board[0][c] == ' ')
            return false;
    }
return true;
}

bool FourInARowBoard::game_is_over() {
    return is_draw() || is_win();
}

// Constructor for FourInARowPlayer
FourInARowPlayer::FourInARowPlayer(string name, char symbol) : Player(name, symbol) {}

void FourInARowPlayer::getmove(int& x, int& y) {
    cout << "\nChoose a column (1 to 7): ";
    cin >> y;
}

FourInARow_Random_Player::FourInARow_Random_Player(char symbol) : RandomPlayer(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

void FourInARow_Random_Player::getmove(int& x, int& y) {
    y = rand() % this->dimension;   // Random number between 0 and 6
}


#endif //_FOUR_IN_A_ROW_H