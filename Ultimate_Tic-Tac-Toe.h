#ifndef _ULTIMATE_TIC_TAC_TOE_H
#define _ULTIMATE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"

bool winnerBox = false, draw_box = false;
int xFirstCell, yFirstCell;   // Indexes of the first cell of box
vector<vector<char>> bigBoard(3, vector<char>(3, ' '));

class UltimateBoard:public Board<char> {
private:
    bool winBox();
    bool drawBox();
public:
    UltimateBoard();
    bool update_board (int x , int y , char symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

class UltimatePlayer : public Player<char> {
public:
    static int turn;
    UltimatePlayer (string name, char symbol);
    void getmove(int& x, int& y);
};
int UltimatePlayer::turn = 1;

class Ultimate_Random_Player : public RandomPlayer<char>{
public:
    Ultimate_Random_Player (char symbol);
    void getmove(int &x, int &y) ;
};


//--------------------------------------- IMPLEMENTATION ----------------------------


bool UltimateBoard::winBox(){
    // Check rows
    for (int i = xFirstCell; i < xFirstCell + 3; i++) {
        if (this->board[i][yFirstCell] == this->board[i][yFirstCell+1] && this->board[i][yFirstCell] == this->board[i][yFirstCell+2]
            && this->board[i][yFirstCell] != ' '){
            bigBoard[xFirstCell/3][yFirstCell/3] = this->board[i][yFirstCell];
            return true;
        }
    }

    // Check columns
    for (int i = yFirstCell; i < yFirstCell +3; ++i) {
        if (this->board[xFirstCell][i] == this->board[xFirstCell+1][i] && this->board[xFirstCell][i] == this->board[xFirstCell+2][i]
            && this->board[xFirstCell][i] != ' ') {
            bigBoard[xFirstCell/3][yFirstCell/3] = this->board[xFirstCell][i];
            return true;
        }
    }

    // Check diagonals
    if ((this->board[xFirstCell][yFirstCell] == this->board[xFirstCell+1][yFirstCell+1] &&
        this->board[xFirstCell][yFirstCell] == this->board[xFirstCell+2][yFirstCell+2] && this->board[xFirstCell][yFirstCell] != ' ') ||
        (this->board[xFirstCell][yFirstCell+2] == this->board[xFirstCell+1][yFirstCell+1] &&
        this->board[xFirstCell+1][yFirstCell+1] == this->board[xFirstCell+2][yFirstCell] && this->board[xFirstCell][yFirstCell+2] != ' '))
    {
        bigBoard[xFirstCell/3][yFirstCell/3] =this->board[xFirstCell+1][yFirstCell+1];
        return true;
    }

    return false;
}

// Check small box is draw or not
bool UltimateBoard::drawBox() {
    if (winnerBox)
        return false;

    for (int i = xFirstCell; i < xFirstCell+3; ++i) {
        for (int j = yFirstCell; j < yFirstCell+3; ++j) {
            if (this->board[i][j] == ' ')
                return false;
        }
    }

    bigBoard[xFirstCell/3][yFirstCell/3] = 'F';
    return true;
}

// Constructor UltimateBoard
UltimateBoard::UltimateBoard() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

bool UltimateBoard::update_board(int x, int y, char mark){
    // Only update if move is valid
    if (x < 0 || x > 8 || y < 0 || y > 8 || this->board[x][y] != ' ')
        return false;

    // Forcing the second player to play on the same square chosen by the first player
    if (!winnerBox && !draw_box && UltimatePlayer::turn % 2 == 0 && (x < xFirstCell || x > xFirstCell+2 || y < yFirstCell || y > yFirstCell+2))
        return false;

    this->board[x][y] = mark;
    xFirstCell = (x % 3 == 0) ? x : x - 1 - (x - 1) % 3;
    yFirstCell = (y % 3 == 0) ? y : y - 1 - (y - 1) % 3;
    UltimatePlayer::turn++;

    winnerBox = winBox();
    if (winnerBox){
        for (int i = xFirstCell; i < xFirstCell+3; ++i) {
            for (int j = yFirstCell; j < yFirstCell+3; ++j) {
                this->board[i][j] = this->board[x][y];
            }
        }
    }

    return true;
}

// Display the board and the pieces on it
void UltimateBoard::display_board() {
    if (UltimatePlayer::turn % 2)
        cout << string(95, '-') << endl << string(40, ' ') << "Turn: Player 1\n" << string(95, '-') << endl;
    else
        cout << string(95, '-') << endl << string(40, ' ') << "Turn: Player 2\n" << string(95, '-') << endl;

    // Print board
    cout << endl << string(95, '=') << endl;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            // Print boundaries
            cout << (j % 3 == 0 ?  "||" : " ");

            // Print the content of box
            if (board[i][j] == ' ')
                cout << setw(3) << "(" << i + 1 << "," << j + 1 << ")  ";
            else
                cout << setw(5) << this->board[i][j] << "    ";
        }
        // Print boundaries
        if ((i + 1) % 3 == 0)
            cout << "||" << endl << string(95, '=') << endl;
        else
            cout << "||" << endl << endl;
    }
}

bool UltimateBoard::is_win() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((bigBoard[i][0] == bigBoard[i][1] && bigBoard[i][1] == bigBoard[i][2] && bigBoard[i][0] != ' ' && bigBoard[i][0] != 'F') ||
            (bigBoard[0][i] == bigBoard[1][i] && bigBoard[1][i] == bigBoard[2][i] && bigBoard[0][i] != ' ' && bigBoard[0][i] != 'F')) {
            return true;
        }
    }

    // Check diagonals
    if ((bigBoard[0][0] == bigBoard[1][1] && bigBoard[1][1] == bigBoard[2][2] && bigBoard[0][0] != ' ' && bigBoard[0][0] != 'F') ||
        (bigBoard[0][2] == bigBoard[1][1] && bigBoard[1][1] == bigBoard[2][0] && bigBoard[0][2] != ' ' && bigBoard[0][2] != 'F')) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
bool UltimateBoard::is_draw() {
    draw_box = drawBox();   // May be modification -> put in is_win()
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (bigBoard[i][j] == ' ')
                return false;
        }
    }
    return true;
}

bool UltimateBoard::game_is_over() {
    return is_win() || is_draw();
}

UltimatePlayer::UltimatePlayer (string name, char symbol) : Player<char>(name, symbol) {}

void UltimatePlayer::getmove(int &x, int &y) {
    cout << "\nPlease enter your move x and y (1 to 3) separated by spaces: ";
    cin >> x >> y;
    x--; y--;
}

Ultimate_Random_Player::Ultimate_Random_Player (char symbol) : RandomPlayer<char>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

void Ultimate_Random_Player::getmove(int &x, int &y) {
    if (winnerBox || draw_box) {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    } else {
        x = rand() % 3 + xFirstCell;
        y = rand() % 3 + yFirstCell;
    }
}

#endif //_ULTIMATE_TIC_TAC_TOE_H