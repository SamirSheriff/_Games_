#ifndef _MINMAXPLAYER_H
#define _MINMAXPLAYER_H

#include "BoardGame_Classes.h"
#include "Four-in-a-row.h"

template <typename T>
class FourInARow_MinMax_Player : public Player<T> {
public:
    FourInARow_MinMax_Player(T symbol);
    void getmove(int& x, int& y) override;

private:
    int rows, columns, lineLength;
    pair<int, long long> MinMax(int depth, long long alpha, long long beta, bool isMaximizing);
    int cellScore();
    int evaluateLine(vector<T> line);
};


//--------------------------------------- IMPLEMENTATION ----------------------------


// Constructor for the templated class
template <typename T>
FourInARow_MinMax_Player<T>::FourInARow_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
    this->rows = 6;
    this->columns = 7;
    this->lineLength = 4;
}


template <typename T>
void FourInARow_MinMax_Player<T>::getmove(int& x, int& y) {
    y = MinMax(5, numeric_limits<long long>::min(), numeric_limits<long long>::max(), true).first;
}


template<typename T>
int FourInARow_MinMax_Player<T>::evaluateLine(vector<T> line){
    int score = 0;
    T enemySymbol = 'X';    // X is the symbol of player (human)

    if (count(line.begin(), line.end(), this->symbol) == 4)
        score += 100;
    else if (count(line.begin(), line.end(), this->symbol) == 3 && count(line.begin(), line.end(), ' ') == 1)
        score += 5;
    else if (count(line.begin(), line.end(), this->symbol) == 2 && count(line.begin(), line.end(), ' ') == 2)
        score += 2;

    if (count(line.begin(), line.end(), enemySymbol) == 3 && count(line.begin(), line.end(), ' ') == 1)
        score -= 4;

    return score;
}


template <typename T>
int FourInARow_MinMax_Player<T>::cellScore() {
    int score = 0;

    // Score center column
    vector<T> midCol;
    for (int i = rows - 1; i >= 0; --i)
        midCol.push_back(marks[i][3]);
    score += 3 * count(midCol.begin(), midCol.end(), this->symbol);   // May be cut to evaluateLine

    // Score Horizontal
    for (int i = rows - 1; i >= 0; --i) {
        vector<T> row;
        for (int j = 0; j < columns; ++j)
            row.push_back(marks[i][j]);

        for (int j = 0; j < columns - 3; ++j) {
            vector<T> line(row.begin() + j, row.begin() + j + lineLength);
            score += evaluateLine(line);
        }
    }

    // Score Vertical
    for (int i = 0; i < columns; ++i) {
        vector<T> col;
        for (int j = rows - 1; j >= 0; --j)
            col.push_back(marks[j][i]);

        for (int j = 0; j < rows - 3; ++j) {
            vector<T> line(col.begin() + j, col.begin() + j + lineLength);
            score += evaluateLine(line);
        }
    }

    // Score right diagonal
    for (int i = rows - 1; i > rows - 4; --i) {
        for (int j = 0; j < columns - 3; ++j) {
            vector<T> line;
            for (int k = 0; k < lineLength; ++k) {
                line.push_back(marks[i - k][j + k]);
            }
            score += evaluateLine(line);
        }
    }

    // Score left diagonal
    for (int i = rows - 1; i > rows - 4; --i) {
        for (int j = 0; j < columns - 3; ++j) {
            vector<T> line;
            for (int k = 0; k < lineLength; ++k) {
                line.push_back(marks[i - 3 + k][j + k]);
            }
            score += evaluateLine(line);
        }
    }

    return score;
}


template<typename T>
pair<int, long long>FourInARow_MinMax_Player<T>::MinMax(int depth, long long alpha, long long beta, bool isMaximizing){
    if (!isMaximizing && this->boardPtr->is_win())  // If AI won
        return { 0, 10000000000000 };

    else if (this->boardPtr->is_win())  // If human won
        return { 0, -10000000000000 };

    else if (this->boardPtr->is_draw())
        return { 0, 0};

    else if (depth == 0)
        return {0, cellScore()};

    if (isMaximizing){
        long long bestScore = numeric_limits<long long>::min();
        int column;
        for (int col = 0; col < columns; ++col) {
            if (this->boardPtr->update_board(0, col, 'O')){
                long long score = MinMax(depth - 1, alpha, beta, false).second;
                this->boardPtr->update_board(0, col, ' ');
                if (score > bestScore){
                    bestScore = score;
                    column = col;
                }
                alpha = max(alpha, bestScore);
                if (alpha >= beta)
                    break;
            }
        }
        return {column, bestScore} ;
    }

    else {  // Minimizing player
        long long worstScore = numeric_limits<long long>::max();
        int column;
        for (int col = 0; col < columns; ++col) {
            if (this->boardPtr->update_board(0, col, 'X')){
                long long score = MinMax(depth - 1, alpha, beta,true).second;
                this->boardPtr->update_board(0, col, ' ');
                if (score < worstScore){
                    worstScore = score;
                    column = col;
                }
                beta = min(beta, worstScore);
                if (alpha >= beta)
                    break;
            }
        }
        return {column, worstScore} ;
    }
}





#endif //_MINMAXPLAYER_H
