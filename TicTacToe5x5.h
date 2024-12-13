#ifndef TICTACTOE5X5_H
#define TICTACTOE5X5_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TicTacToe5x5 {
private:
    const int size = 5;
    vector<vector<char>> board;
    int movesLeft;
    
    int count_sequences(char symbol);
    bool is_valid_move(int x, int y);

public:
    TicTacToe5x5();
    void display_board();
    bool place_mark(int x, int y, char symbol);
    pair<int, int> determine_winner(); // Returns counts for X and O
    bool is_full();
};

#endif // TICTACTOE5X5_H
