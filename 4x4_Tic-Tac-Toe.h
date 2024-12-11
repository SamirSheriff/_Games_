#ifndef _4X4_TIC_TAC_TOE_H
#define _4X4_TIC_TAC_TOE_H

#include"BoardGame_Classes.h"
#include "bits/stdc++.h"

string Move;
int idxToken;
vector<pair<int,int>> tokens = {{ 0, 0 }, {0, 2}, {3, 1}, {3, 3}};

template<typename T>
class _4x4_TicTacToe_Board : public Board<T> {
private:
    // Last Move
    T mark;
    int row, col;
    int countRow, countRD, countLD, countCol;
    bool checkWinner(int x, int y, int addRow, int addCol);
public:
    _4x4_TicTacToe_Board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};


template <typename T>
class _4x4_TicTacToe_Player : public Player<T> {
public:
    static int turn;
    _4x4_TicTacToe_Player(string name, T symbol);
    void getmove(int& x, int& y);
};
template <typename T>
int _4x4_TicTacToe_Player<T>::turn = 1;


template<typename T>
class _4x4_TicTacToe_Random_Player : public RandomPlayer<T>{
public:
    _4x4_TicTacToe_Random_Player (T symbol);
    void getmove(int &x, int &y);
};


//--------------------------------------- IMPLEMENTATION ----------------------------


template <typename T>
bool _4x4_TicTacToe_Board<T>::checkWinner(int x, int y, int addRow, int addCol){
    for (int i = 1; i < 3; ++i) {
        int idxRow = x - i * addRow;
        int idxCol = y + i * addCol;
        if (idxRow < 0 || idxRow > 3 || idxCol < 0 || idxCol > 3 || this->board[idxRow][idxCol] != mark)
            return false;

        if ((addRow == 0 && addCol == 1) || (addRow == 0 && addCol == -1))
            this->countRow++;
        else if ((addRow == 1 && addCol == 1) || (addRow == -1 && addCol == -1))
            this->countRD++;  // plus count right diagonal
        else if ((addRow == 1 && addCol == -1) || (addRow == -1 && addCol == 1))
            this->countLD++;  // plus count left diagonal
        else
            this->countCol++;
    }
    return true;
}


// Constructor for _4x4_TicTacToe_Board
template<typename T>
_4x4_TicTacToe_Board<T>::_4x4_TicTacToe_Board() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns && i == 2; ++j) {
            this->board[1][j] = this->board[2][j] = ' ';
        }
    }
    // Initialize the board with tokens
    this->board[0][0] = this->board[0][2] = this->board[3][1] = this->board[3][3] = 'O';
    this->board[0][1] = this->board[0][3] = this->board[3][0] = this->board[3][2] = 'X';
}


void update_position_token(int x, int y){
    tokens.erase(tokens.begin() + idxToken);
    tokens.emplace_back(x, y);
}

template<typename T>
bool _4x4_TicTacToe_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x > 3 || y < 0 || y > 3 || this->board[x][y] != symbol)
        return false;

    // If user choose move up
    if(Move == "1" && x - 1 >= 0 && this->board[x - 1][y] == ' '){
        if (_4x4_TicTacToe_Player<T>::turn % 2 == 0)   // update the list of tokens of random player
            update_position_token(row, col);
        this->board[x][y] = ' ';
        this->board[x - 1][y] = symbol;
        row = x - 1;
        col = y;
        mark = symbol;
        _4x4_TicTacToe_Player<T>::turn++;
        return true;
    }

        // If user choose move right
    else if (Move == "2" && y + 1 < 4 && this->board[x][y + 1] == ' '){
        if (_4x4_TicTacToe_Player<T>::turn % 2 == 0)   // update the list of tokens of random player
            update_position_token(row, col);
        this->board[x][y] = ' ';
        this->board[x][y + 1] = symbol;
        row = x;
        col = y + 1;
        mark = symbol;
        _4x4_TicTacToe_Player<T>::turn++;
        return true;
    }

        // If user choose move down
    else if (Move == "3" && x + 1 < 4 && this->board[x + 1][y] == ' '){
        if (_4x4_TicTacToe_Player<T>::turn % 2 == 0)   // update the list of tokens of random player
            update_position_token(row, col);
        this->board[x][y] = ' ';
        this->board[x + 1][y] = symbol;
        row = x + 1;
        col = y;
        mark = symbol;
        _4x4_TicTacToe_Player<T>::turn++;
        return true;
    }

    // If user choose move left
    else if (Move == "4" && y - 1 >= 0 && this->board[x][y - 1] == ' '){
        if (_4x4_TicTacToe_Player<T>::turn % 2 == 0)  // update the list of tokens of random player
            update_position_token(row, col);
        this->board[x][y] = ' ';
        this->board[x][y - 1] = symbol;
        row = x;
        col = y - 1;
        mark = symbol;
        _4x4_TicTacToe_Player<T>::turn++;
        return true;
    }

    else
        return false;
}


template<typename T>
void _4x4_TicTacToe_Board<T>::display_board() {
    // Display who its turn
    if (_4x4_TicTacToe_Player<T>::turn % 2)
        cout << string(37, '-') << "\n\t       Turn: Player 1\n" << string(37, '-') << "\n";
    else
        cout << string(37, '-') << "\n\t       Turn: Player 2\n" << string(37, '-') << "\n";

    // Display the board
    cout << string(37, '-') << endl;
    for (int r = 0; r < this->rows; r++) {
        cout << "|";
        for (int c = 0; c < this->columns; c++) {
            if (this->board[r][c] != ' ')
                cout << " (" << r + 1 << ',' << c + 1 << ')' << this->board[r][c] << " |";
            else
                cout << setw(4) << this->board[r][c] << "    |";
        }
        cout << endl << string(37, '-') << endl;
    }
}


// Returns true if there is any winner
template <typename T>
bool _4x4_TicTacToe_Board<T>::is_win() {
    this->countRow = this->countRD = this->countLD = this->countCol = 1;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (!(i == 0 && j == 0) && checkWinner(this->row, this->col, i, j))
                return true;
        }
    }
    if (this->countRow >= 3 || this->countRD >= 3 || this->countLD >= 3 || this->countCol >= 3)
        return true;

    return false;
}


template <typename T>
bool _4x4_TicTacToe_Board<T>::is_draw() {
    return false;
}

template <typename T>
bool _4x4_TicTacToe_Board<T>::game_is_over(){
    return is_win();
}


// Constructor for FourInARowPlayer
template <typename T>
_4x4_TicTacToe_Player<T>::_4x4_TicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void _4x4_TicTacToe_Player<T>::getmove(int &x, int &y) {
    cout << this->name << ", choose your token(" << this->symbol << ") and enter its index (1 to 4) separated by spaces: ";
    cin >> x >> y;
    x--; y--;

    cout << "Where do you want to Move ?\n1)Up\n2)Right\n3)Down\n4)Left\nEnter your choice (1, 2, 3 or 4): ";
    cin >> Move;
}


// Constructor for random computer player
template<typename T>
_4x4_TicTacToe_Random_Player<T>::_4x4_TicTacToe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(time(0));  // Seed the random number generator
}

template<typename T>
void _4x4_TicTacToe_Random_Player<T>::getmove(int& x, int& y) {
    idxToken = rand() % tokens.size();             // index random number to choose a token from the vector(tokens)
    x = tokens[idxToken].first;                    // The index of row of chosen token
    y = tokens[idxToken].second;                   // The index of column of chosen token
    Move = to_string(rand() % 4 + 1);          // Random move (up, right, down or left)
}


#endif //_4X4_TIC_TAC_TOE_H