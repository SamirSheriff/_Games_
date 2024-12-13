
#ifndef pyramidic_XO
#define pyramidic_XO
#include "BoardGame_Classes.h"
using namespace std;

template <typename T>
class myboard : public Board<T> {

public:
    myboard();
    ~myboard();

    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

template <typename T>
myboard<T>::myboard() {
    this->n_moves=0;
    this->rows = 3;  // Pyramid height
    this->columns = 5;  // Max width at the base


    this->board = new T*[this->rows];
    for (int r = 0; r < this->rows; r++) {
         this->board[r] = new T[2 * (r + 1) - 1];  // Pyramid structure
         for (int c = 0; c < 2 * (r + 1) - 1; c++) {
            this->board[r][c] = '*';  // Initialize with empty marker
        }
    }
}

template <typename T>
myboard<T>::~myboard() {
for (int r = 0; r < this->rows; r++) {
    delete[] this->board[r];
    }
    delete[] this->board;
}

template <typename T>
bool myboard<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y <= 2 * (x + 1) - 1 && this->board[x][y] == '*') {
    this->board[x][y] = symbol;
    this->n_moves++;
    return true;
    }
    return false;
}

template <typename T>
void myboard<T>::display_board() {
    for (int r = 0; r < this->rows; r++) {
        for (int space = 0; space < this->rows - r - 1; space++) {
         cout << " ";
        }
        for (int c = 0; c < 2 * (r + 1) - 1; c++) {
         cout << this->board[r][c];
        }
    cout << endl;
    }
}

template <typename T>
bool myboard<T>::is_win() {
// Check for horizontal, vertical, and diagonal wins
    for (int r = 0; r < this->rows; r++) {
    for (int c = 0; c < 2 * (r + 1) - 1; c++) {
    if (this->board[r][c] == '*') continue;
    T symbol = this->board[r][c];

    // Horizontal
    if (c + 2 < 2 * (r + 1) && this->board[r][c + 1] == symbol && this->board[r][c + 2] == symbol) {
    return true;
    }

    // Vertical
    if (r + 2 < this->rows && c < 2 * (r + 1) && this->board[r + 1][c] == symbol && this->board[r + 2][c] == symbol) {
    return true;
    }

    // Diagonal
    if (r + 2 < this->rows && c + 2 < 2 * (r + 2) +1 && this->board[r + 1][c + 1] == symbol && this->board[r + 2][c + 2] == symbol) {
    return true;
    }
    }
    }
    return false;
}

template <typename T>
bool myboard<T>::is_draw() {
    return this->game_is_over() && !this->is_win();
}

template <typename T>
bool myboard<T>::game_is_over() {
    return this->n_moves == (this->rows * this->rows);
}
template<typename T>
class PyramidicPlayer : public Player<T>{
public:
    PyramidicPlayer(string name, T symbol):Player<T>(name, symbol){}
    PyramidicPlayer(T symbol):Player<T>("computer", symbol){

    }
    void getmove(int& x, int& y)override{
    if(this->name=="computer"){
        srand(static_cast<unsigned>(time(0))); // Seed for randomness
        x = rand() % 3; // Randomly pick a row (0, 1, or 2)
        y = rand() % (2 * x + 1);
        cout<<"computer played successfully ! "<<endl;

    }
    else{
        cout << this->name << ", enter your move (row and column starting from 0)" ;
        cin >> x >> y;
    }
    }

};
template <typename T>
class pyramidicRandomPlayer : public RandomPlayer<T> {
    public:
    pyramidicRandomPlayer(T symbol):RandomPlayer<T>(symbol){};
    void getmove(int &x, int &y)override;
};
template<typename T>
void pyramidicRandomPlayer<T>::getmove(int &x, int &y) {
    srand(static_cast<unsigned>(time(0))); // Seed for randomness
    x = rand() % 3; // Randomly pick a row (0, 1, or 2)
    y = rand() % (2 * x + 1);
}
#endif