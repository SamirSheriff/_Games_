#ifndef wttt_H
#define wttt_H
#include <iostream>
#include <fstream>
#include <string>
#include "BoardGame_Classes.h"
using namespace std;
template<typename T>
class WTTTboard : public Board<T> {
private:
    ifstream wordsfile;

    bool is_valid_word(const string& word);

public:
    WTTTboard(const string& name);
    ~WTTTboard();

    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

// Implementation of WTTTboard
template<typename T>
WTTTboard<T>::WTTTboard(const string& name) {
    this->n_moves = 0;
    this->board = new T*[3];
    for (int i = 0; i < 3; ++i) {
        this->board[i] = new T[3];
    }
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            this->board[r][c] = '*';
        }
    }
    this->wordsfile = ifstream(name);
    if (!this->wordsfile.is_open()) {
    cerr << "Failed to open file: " << name << endl;
    } else {
    cout << "File opened successfully: " << name << endl;
    }
}

template<typename T>
WTTTboard<T>::~WTTTboard() {
    for (int r = 0; r < 3; r++) {
        delete[] this->board[r];
    }
    delete[] this->board;
    if (wordsfile.is_open()) {
        wordsfile.close();
    }
}
template<typename T>
bool WTTTboard<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < 3 && y >= 0 && y < 3 && this->board[x][y] == '*') {
    this->board[x][y] = symbol;
    this->n_moves++;
    return true;
    }
    return false;
}


template<typename T>
bool WTTTboard<T>::is_valid_word(const string& word) {
    string fileword;
    wordsfile.clear();
    wordsfile.seekg(0, ios::beg);
    while (wordsfile >> fileword) {
         if (fileword == word) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool WTTTboard<T>::is_win() {
    string target;

    for (int i = 0; i < 3; i++) {
    // Check rows
    if (this->board[i][0] != '*' && this->board[i][1] != '*' && this->board[i][2] != '*') {
    target = string(1, this->board[i][0]) + this->board[i][1] + this->board[i][2];
    if (is_valid_word(target)) return true;
    }

    // Check columns
    if (this->board[0][i] != '*' && this->board[1][i] != '*' && this->board[2][i] != '*') {
    target = string(1, this->board[0][i]) + this->board[1][i] + this->board[2][i];
    if (is_valid_word(target)) return true;
    }


    // Check diagonals
    if (this->board[0][0] != '*' && this->board[1][1] != '*' && this->board[2][2] != '*') {
        target = string(1, this->board[0][0]) + this->board[1][1] + this->board[2][2];
        if (is_valid_word(target)) return true;
    }
    if (this->board[0][2] != '*' && this->board[1][1] != '*' && this->board[2][0] != '*') {
        target = string(1, this->board[0][2]) + this->board[1][1] + this->board[2][0];
        if (is_valid_word(target)) return true;
    }
}

    return false;
}



template<typename T>
void WTTTboard<T>::display_board() {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
        cout << this->board[r][c] << " ";
        }
        cout << endl;
    }
}

template<typename T>
bool WTTTboard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool WTTTboard<T>::game_is_over() {
    return is_win() || is_draw();
}

// Word Tic-Tac-Toe Player Class
template<typename T>
class WTTTplayer : public Player<T> {
public:
    char currentSymbol;
    WTTTplayer(string n,T symbol)  : Player<T>(n, symbol){}
    WTTTplayer(T symbol):Player<T>("computer", symbol){}

    void getmove(int& x, int& y) override ;

};
template<typename T>
void WTTTplayer<T>::getmove(int& x, int& y) {
    if(this->name =="computer"){
         srand(static_cast<unsigned>(time(0))); // Seed for randomness
         x = rand() % 3; // Random row (0, 1, or 2)
         y = rand() % 3; // Random column (0, 1, or 2)
         this->symbol = 'A' + (rand() % 26);
         cout<<"computer played successfully ! "<<endl;
    }
    else{
        cout << this->name << ", enter your move (row and column starting from 0): ";
        cin >> x >> y;

        // Prompt the user to enter a symbol for this move
        cout << this->name << ", enter the character for this move: ";
        cin >> currentSymbol;
        this->symbol = toupper(currentSymbol);
    }

}
template<typename T>
class RandomWTTTPlayer : public RandomPlayer<T> {
public:
    RandomWTTTPlayer(T symbol) : RandomPlayer<T>(symbol) {}

    void getmove(int& x, int& y) override ;
};
template<typename T>
void RandomWTTTPlayer<T>::getmove(int& x, int& y) {
        srand(static_cast<unsigned>(time(0)));
        //it has values from 0 to 2
        x = rand() % 3;
        y = rand() % 3;
        //generate random character from A to Z
        this->symbol = 'A' + (rand() % 26);
}

#endif

