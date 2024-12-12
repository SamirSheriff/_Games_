#ifndef _FOUR_IN_A_ROW_H
#define _FOUR_IN_A_ROW_H

#include"BoardGame_Classes.h"
#include "bits/stdc++.h"

// Last Move
int row, col;
char mark;
bool isComputer = false;
vector<vector<char>>marks(6, vector<char>(7, ' '));

template <typename T>
class FourInARowBoard : public Board<T> {
private:
    static int turn;
    int countRow, countRD, countLD;
    bool checkWinner(int x, int y, int addRow, int addCol);

public:
    FourInARowBoard();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};
template <typename T>
int FourInARowBoard<T>::turn = 0;


template <typename T>
class FourInARowPlayer : public Player<T> {
public:
    FourInARowPlayer(string name, T symbol);
    void getmove(int& x, int& y);
};


template <typename T>
class FourInARow_Random_Player : public RandomPlayer<T>{
public:
    FourInARow_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};


//--------------------------------------- IMPLEMENTATION ----------------------------

template <typename T>
bool FourInARowBoard<T>::checkWinner(int x, int y, int addRow, int addCol){
    for (int i = 1; i < 4; ++i) {
        int idxRow = x - i * addRow, idxCol = y + i * addCol;
        if (idxRow < 0 || idxRow > 5 || idxCol < 0 || idxCol > 6 || this->board[idxRow][idxCol] != mark)
            return false;

        if ((addRow == 0 && addCol == 1) || (addRow == 0 && addCol == -1))
            this->countRow++;
        else if ((addRow == 1 && addCol == 1) || (addRow == -1 && addCol == -1))
            this->countRD++;
        else if ((addRow == 1 && addCol == -1) || (addRow == -1 && addCol == 1))
            this->countLD++;
    }
    return true;
}


// Constructor FourInARowBoard
template <typename T>
FourInARowBoard<T>::FourInARowBoard() {
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


template <typename T>
bool FourInARowBoard<T>::update_board(int x, int y, T symbol) {
    if (y >= 0 && y < this->columns) {
        if (symbol == ' ') {
            for (int i = 0; i < this->rows; ++i) {
                if (this->board[i][y] != symbol) {
                    this->board[i][y] = symbol;
                    this->n_moves--;
                    marks[i][y] = symbol;
                    return true;
                }
            }
        }

        for (int i = this->rows - 1; i >= 0; i--) {
            if (this->board[i][y] == ' ') {
                if (isComputer)
                    cout << "Random Computer Player: played in column " << y + 1 << " \n\n";
                this->board[i][y] = symbol;
                this->n_moves++;
                row = i;
                col = y;
                mark = symbol;
                marks[row][col] = symbol;
                return true;
            }
        }
    }

    return false;
}

// Display the board and the pieces on it
template <typename T>
void FourInARowBoard<T>::display_board() {
    turn++;

    if (turn % 2)
        cout << string(43, '-') << "\n\t       Turn: Player 1\n" << string(43, '-') << "\n\n";
    else
        cout << string(43, '-') << "\n\t       Turn: Player 2\n" << string(43, '-') << "\n\n";

    for (int i = 0; i < this->rows; i++) {
        cout << "|";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(3) << this->board[i][j] << "  |";
        }
        cout << endl << string(43, '-') << endl;
    }

    for (int i = 1; i < 8; ++i) {
        cout << setw(4) << i << "  ";
    }
    cout << endl << endl;
}


// Returns true if there is any winner
template <typename T>
bool FourInARowBoard<T>::is_win() {
    this->countRow = this->countRD = this->countLD = 1;

    if (checkWinner(row, col, -1, 0) || checkWinner(row, col, 0, 1) ||
        checkWinner(row, col, 0, -1) || checkWinner(row, col, 1, 1) ||
        checkWinner(row, col, -1, -1) || checkWinner(row, col, 1, -1) ||
        checkWinner(row, col,-1, 1)){
        return true;
    }

    if (this->countRow >= 4 || this->countRD >= 4 || this->countLD >= 4)
        return true;

    return false;
}


template <typename T>
bool FourInARowBoard<T>::is_draw() {
    return this->n_moves == 42;
}


template <typename T>
bool FourInARowBoard<T>::game_is_over() {
    return is_draw() || is_win();
}

//--------------------------------------

// Constructor for FourInARowPlayer
template <typename T>
FourInARowPlayer<T>::FourInARowPlayer(string name, T symbol) : Player<T>(name, symbol) {}


template <typename T>
void FourInARowPlayer<T>::getmove(int& x, int& y) {
    cout << this->name << ", choose a column (1 to 7): ";
    cin >> y;
    y--;
    x = 0;
    isComputer = false;
}

//--------------------------------------

// Constructor for FourInARow_Random_Player
template <typename T>
FourInARow_Random_Player<T>::FourInARow_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(time(0));  // Seed the random number generator
}


template <typename T>
void FourInARow_Random_Player<T>::getmove(int& x, int& y) {
    y = rand() % this->dimension;   // Random number between 0 and 6
    isComputer = true;
}


#endif //_FOUR_IN_A_ROW_H