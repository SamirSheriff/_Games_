#ifndef _NUMERICAL_TIC_TAC_TOE_H
#define _NUMERICAL_TIC_TAC_TOE_H

#include"BoardGame_Classes.h"

vector<int>Player1Nums = {1, 3, 5, 7, 9};  // Numbers player 1
vector<int>Player2Nums = {2, 4, 6, 8};     // Numbers player 2

class NumericalBoard : public Board<int> {
public:
    NumericalBoard();
    bool update_board (int x , int y , int symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

class NumericalPlayer : public Player<int> {
public:
    static int turn;
    NumericalPlayer(string name, int symbol);
    void getmove(int& x, int& y);
};
int NumericalPlayer::turn = 1;

class Numerical_Random_Player : public RandomPlayer<int>{
public:
    Numerical_Random_Player(int symbol);
    void getmove(int &x, int &y) ;
};

//--------------------------------------- IMPLEMENTATION ----------------------------

// Constructor NumericalBoard
NumericalBoard::NumericalBoard() {
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 50;        // Initial value
        }
    }
    this->n_moves = 0;
}

bool NumericalBoard::update_board(int x, int y, int number) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 50) &&
        ((NumericalPlayer::turn % 2 != 0 && find(Player1Nums.begin(), Player1Nums.end(), number) != Player1Nums.end()) ||
        (NumericalPlayer::turn % 2 == 0 && find(Player2Nums.begin(), Player2Nums.end(), number) != Player2Nums.end())))
    {
        // Update the list of available moves
        if (NumericalPlayer::turn % 2)
            Player1Nums.erase(remove(Player1Nums.begin(), Player1Nums.end(), number), Player1Nums.end());
        else
            Player2Nums.erase(remove(Player2Nums.begin(), Player2Nums.end(), number), Player2Nums.end());

        this->n_moves++;
        this->board[x][y] = number;
        NumericalPlayer::turn++;
        return true;
    }
    return false;
}

// Display the board and the pieces on it
void NumericalBoard::display_board() {
    if (NumericalPlayer::turn % 2)
        cout << string(35, '-') << "\n\tTurn: Player 1\n" << string(35, '-') << "\n\n";
    else
        cout << string(35, '-') << "\n\tTurn: Player 2\n" << string(35, '-') << "\n\n";


    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (board[i][j] == 50) {
                cout << setw(3) << " ";
            } else {
                cout << setw(3) << this->board[i][j];
            }
            if (j < this->columns-1)
                cout << "  |";
        }
        if (i != this->rows - 1)
            cout << "\n-----------------\n";
    }
    cout << endl << endl;
}

bool NumericalBoard::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) ||
            (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) ||
        (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15)) {
        return true;
    }

    return false;
}

bool NumericalBoard::is_draw() {
    return this->n_moves == 9;
}

bool NumericalBoard::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for Numerical_Tic-Tac-Toe_Player
NumericalPlayer::NumericalPlayer(string name, int symbol) : Player(name, symbol) {
}


void NumericalPlayer::getmove(int& x, int& y) {
    cout << "Choose a row (0, 1 or 2): ";
    cin >> x;
    cout << "Choose a column (0, 1 or 2): ";
    cin >> y;

    // Display the list of available numbers for Player1
    if (turn % 2){
        cout << "List: {";
        for (int i = 0; i < Player1Nums.size()-1; ++i) {
            cout << Player1Nums[i] << ", ";
        }
        cout << Player1Nums[Player1Nums.size()-1] << "}\n";
    }

    // Display the list of available numbers for Player2
    else{
        cout << "List: {";
        for (int i = 0; i < Player2Nums.size()-1; ++i) {
            cout << Player2Nums[i] << ", ";
        }
        cout << Player2Nums[Player2Nums.size()-1] << "}\n";
    }

    cout << "Choose a number from the list: ";
    cin >> this->symbol;
}

//--------------------------------------

Numerical_Random_Player::Numerical_Random_Player(int symbol) : RandomPlayer(symbol){
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}


void Numerical_Random_Player::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    int index = rand() % Player2Nums.size();
    this->symbol = Player2Nums[index];
}

#endif //_NUMERICAL_TIC_TAC_TOE_H