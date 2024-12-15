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

class Player {
private:
    string name;
    char symbol;

public:
    Player(string n, char s);
    string get_name();
    char get_symbol();
    void get_move(int& x, int& y);
};

class MisereGameManager {
private:
    MisereBoard board;
    Player* players[2];

public:
    MisereGameManager(Player* p1, Player* p2);
    void play_game();
};

#endif
