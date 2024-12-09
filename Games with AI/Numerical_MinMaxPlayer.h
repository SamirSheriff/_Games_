#ifndef _NUMERICAL_MINMAXPLAYER_H
#define _NUMERICAL_MINMAXPLAYER_H

#include "BoardGame_Classes.h"
#include "Numerical_Tic-Tac-Toe.h"



template <typename T>
class Numerical_MinMax_Player : public Player<T> {
public:
    Numerical_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(int alpha, int beta, bool isMaximizing);
    int forcedMove(int r, int c);
    vector<int> getBestMove();
};


//--------------------------------------- IMPLEMENTATION ----------------------------

// Constructor for the templated class
template <typename T>
Numerical_MinMax_Player<T>::Numerical_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Method to get the best move for the player
template <typename T>
void Numerical_MinMax_Player<T>::getmove(int& x, int& y) {
    vector<int> bestMove = getBestMove();
    x = bestMove[0];
    y = bestMove[1];
    this->symbol = bestMove[2];
}


// Minimax algorithm to evaluate the board
template <typename T>
int Numerical_MinMax_Player<T>::calculateMinMax(int alpha, int beta, bool isMaximizing) {
    if (this->boardPtr->is_win())
        return isMaximizing ? -INF : INF;
    else if (this->boardPtr->is_draw())
        return 0;

    if (isMaximizing) {
        int bestValue = -INF;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < Player2Nums.size(); ++k) {
                    int moveNum = Player2Nums[k];
                    if (this->boardPtr->update_board(i, j, moveNum)) {
                        int value = calculateMinMax(alpha, beta, false);
                        this->boardPtr->update_board(i, j, 50); // Undo move
                        Player2Nums.insert(Player2Nums.begin() + k, moveNum);   // Undo list
                        bestValue = max(bestValue, value);
                        alpha = max(alpha, value);
                        if (beta <= alpha)
                            return bestValue;
                    }
                }
            }
        }
        return bestValue;
    }
    else{
        int minValue = INF;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < Player1Nums.size(); ++k) {
                    int moveNum = Player1Nums[k];
                    if (this->boardPtr->update_board(i, j, moveNum)) {
                        int value = calculateMinMax(alpha, beta, true);
                        this->boardPtr->update_board(i, j, 50); // Undo move
                        Player1Nums.insert(Player1Nums.begin() + k, moveNum); // Undo list
                        minValue = min(minValue, value);
                        beta = min(beta, value);
                        if (beta <= alpha)
                            return minValue;
                    }
                }
            }
        }
        return minValue;
    }
}

template<typename T>
int Numerical_MinMax_Player<T>::forcedMove(int r, int c){
    int bestValue = -INF;
    int bestNumber;

    for (int i = 0; i < Player2Nums.size(); ++i) {
        int moveNum = Player2Nums[i];
        this->boardPtr->update_board(r, c, moveNum);
        int moveValue = calculateMinMax(-INF, INF, false);
        this->boardPtr->update_board(r, c, 50);   // Undo move
        Player2Nums.insert(Player2Nums.begin() + i, moveNum);   // Undo list

        if (moveValue > bestValue){
            bestValue = moveValue;
            bestNumber = moveNum;
        }
    }

    return bestNumber;
}

// Find the best move using the minimax algorithm
template <typename T>
vector<int> Numerical_MinMax_Player<T>::getBestMove() {
    int bestValue = -INF;
    vector<int> bestMove = {-1, -1, 0};

    // First, check if we can win in the next move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < Player2Nums.size(); ++k) {
                int moveNum = Player2Nums[k];
                if (this->boardPtr->update_board(i, j, moveNum)) {
                    if (this->boardPtr->is_win()) {
                        // Undo move
                        this->boardPtr->update_board(i, j, 50);
                        Player2Nums.insert(Player2Nums.begin() + k, moveNum);
                        return {i, j, moveNum}; // Winning move found
                    }
                    // Undo move
                    this->boardPtr->update_board(i, j, 50);
                    Player2Nums.insert(Player2Nums.begin() + k, moveNum);
                }
            }
        }
    }

    // Second, check if the opponent can win in their next move and block them
    NumericalPlayer<int>::turn++;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < Player1Nums.size(); ++k) {
                int moveNum = Player1Nums[k];
                if (this->boardPtr->update_board(i, j, moveNum)) {
                    if (this->boardPtr->is_win()) {
                        this->boardPtr->update_board(i, j, 50); // Undo move
                        Player1Nums.insert(Player1Nums.begin() + k, moveNum); // Undo list
                        NumericalPlayer<int>::turn--;
                        int bestNumber = forcedMove(i, j);
                        return {i, j, bestNumber}; // Block opponent's winning move
                    }
                    this->boardPtr->update_board(i, j, 50); // Undo move
                    Player1Nums.insert(Player1Nums.begin() + k, moveNum); // Undo list
                }
            }
        }
    }
    NumericalPlayer<int>::turn--;

    // If no immediate win or block, use MinMax to find the best move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < Player2Nums.size(); ++k) {
                int moveNum = Player2Nums[k];
                if (this->boardPtr->update_board(i, j, moveNum)) {
                    int moveValue = calculateMinMax(-INF, INF, false);
                    this->boardPtr->update_board(i, j, 50);    // Undo move
                    Player2Nums.insert(Player2Nums.begin() + k, moveNum);   // Undo list

                    if (moveValue > bestValue) {
                        bestMove = {i, j, moveNum};
                        bestValue = moveValue;
                    }
                }
            }
        }
    }

    return bestMove;
}


#endif //_NUMERICAL_MINMAXPLAYER_H