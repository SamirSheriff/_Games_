#ifndef _NUMERICAL_TIC_TAC_TOE_H
#define _NUMERICAL_TIC_TAC_TOE_H

#include"BoardGame_Classes.h"

vector<int>Player1Nums = {1, 3, 5, 7, 9};  // Numbers player 1
vector<int>Player2Nums = {2, 4, 6, 8};     // Numbers player 2

template<typename T>
class NumericalBoard : public Board<T> {
public:
    NumericalBoard();
    bool update_board (int x, int y, T symbol);
    void display_board () ;
    bool is_win();
    bool is_draw();
    bool game_is_over();
};


template<typename T>
class NumericalPlayer : public Player<T> {
public:
    static int turn;
    NumericalPlayer(string name, T symbol);
    void getmove(int& x, int& y);
};
template<typename T>
int NumericalPlayer<T>::turn = 1;


template<typename T>
class Numerical_Random_Player : public RandomPlayer<T>{
public:
    Numerical_Random_Player(T symbol);
    void getmove(int &x, int &y) ;
};

//--------------------------------------- IMPLEMENTATION ----------------------------

// Constructor NumericalBoard
template<typename T>
NumericalBoard<T>::NumericalBoard() {
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

template<typename T>
bool NumericalBoard<T>::update_board(int x, int y, T number) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns)) {
        if (number == 50) {
            this->board[x][y] = number;
            this->n_moves--;
            NumericalPlayer<T>::turn--;
            return true;
        }

        else if (this->board[x][y] == 50 && (
                (NumericalPlayer<T>::turn % 2 != 0 && find(Player1Nums.begin(), Player1Nums.end(), number) != Player1Nums.end()) ||
                (NumericalPlayer<T>::turn % 2 == 0 && find(Player2Nums.begin(), Player2Nums.end(), number) != Player2Nums.end())) )
        {
            // Update the list of available moves
            if (NumericalPlayer<T>::turn % 2)
                Player1Nums.erase(remove(Player1Nums.begin(), Player1Nums.end(), number), Player1Nums.end());
            else
                Player2Nums.erase(remove(Player2Nums.begin(), Player2Nums.end(), number), Player2Nums.end());

            this->n_moves++;
            this->board[x][y] = number;
            NumericalPlayer<T>::turn++;
            return true;
        }
    }
    return false;
}

// Display the board and the pieces on it
template<typename T>
void NumericalBoard<T>::display_board() {
    // Print the player turn
    if (NumericalPlayer<T>::turn % 2)
        cout << string(35, '-') << "\n\tTurn: Player 1\n" << string(35, '-') << "\n\n";
    else
        cout << string(35, '-') << "\n\tTurn: Player 2\n" << string(35, '-') << "\n\n";

    // Print the board
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == 50) {
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


template<typename T>
bool NumericalBoard<T>::is_win() {
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

template<typename T>
bool NumericalBoard<T>::is_draw() {
    return this->n_moves == 9;
}

template<typename T>
bool NumericalBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for Numerical_Tic-Tac-Toe_Player
template<typename T>
NumericalPlayer<T>::NumericalPlayer(string name, T symbol) : Player<T>(name, symbol) {
}


template<typename T>
void NumericalPlayer<T>::getmove(int& x, int& y) {
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

template<typename T>
Numerical_Random_Player<T>::Numerical_Random_Player(T symbol) : RandomPlayer<T>(symbol){
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}


template<typename T>
void Numerical_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    int index = rand() % Player2Nums.size();
    this->symbol = Player2Nums[index];
}

#endif //_NUMERICAL_TIC_TAC_TOE_H