#include "BoardGame_Classes.h"
#include "Numerical_Tic-Tac-Toe.h"
#include "Four-in-a-row.h"
#include "Ultimate_Tic-Tac-Toe.h"
#include "4x4_Tic-Tac-Toe.h"
#include "pyramidicXO.h"
#include "wttt.h"

using namespace std;

int main() {
    cout << "Welcome to Mental Games :)\n\n";

    string game, player2, player1Name, player2Name;
    cout << "Games Menu:\n1) Pyramic Tic-Tac-Toe\n2) Four in a row\n4) Word Tic-Tac-Toe\n5) Numerical Tic-Tac-Toe\n";
    cout << "7) 4x4 Tic-Tac-Toe\n8) Ultimate Tic-Tac-Toe\n9) Exit\nEnter the number of game: ";
    cin >> game;

    // Get the name player2 1
    cout << "Enter Player 1 name: ";
    cin.ignore();
    getline(cin, player1Name);
    player1Name[0] = toupper(player1Name[0]);

    // Choose player2 2
    cout << "1) Play vs friend\n2) Play vs computer\nEnter your choice (1 or 2): ";
    cin >> player2;

    // Check if a user entered a valid choice or not
    while (player2 != "1" && player2 != "2") {
        cout << "Please, enter a valid choice\n";
        cout << "1) Play vs friend\n2) Play vs computer\nEnter your choice (1 or 2): ";
        cin >> player2;
    }

    if (game == "1"){
        myboard<char> *B = new myboard<char>();
        Player<char> *players[2];    // Set up player2 1
        players[0] = new PyramidicPlayer(player1Name, 'X');

        // Set up player2 2
        if (player2 == "1") {
            cout << "Enter Player 2 name: ";
            cin.ignore();
            getline(cin, player2Name);
            player2Name[0] = toupper(player2Name[0]);
            players[1] = new PyramidicPlayer<char>(player2Name, 'O');
        }
        else {
            players[1] = new pyramidicRandomPlayer('O');
        }

        // Create the game manager and run the game
        GameManager<char> pyramidic_game(B, players);
        pyramidic_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

    }

    else if (game == "2"){
        FourInARowBoard<char> *B = new FourInARowBoard<char>();  // Set up the board
        // Set up player2 1
        Player<char> *players[2];
        players[0] = new FourInARowPlayer(player1Name, 'X');

        // Set up player2 2
        if (player2 == "1") {
            cout << "Enter Player 2 name: ";
            cin.ignore();
            getline(cin, player2Name);
            player2Name[0] = toupper(player2Name[0]);
            players[1] = new FourInARowPlayer(player2Name, 'O');
        }
        else {
            players[1] = new FourInARow_Random_Player('O');
        }

        // Create the game manager and run the game
        GameManager<char> FourInARow_game(B, players);
        FourInARow_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
    }

    else if (game == "4"){
        WTTTboard<char> *B = new WTTTboard<char>("dic.txt");  // Set up the board

        // Set up player2 1
        Player<char> *players[2];
        players[0] = new WTTTplayer(player1Name, 'X');

        // Set up player2 2
        if (player2 == "1") {
            cout << "Enter Player 2 name: ";
            cin.ignore();
            getline(cin, player2Name);
            player2Name[0] = toupper(player2Name[0]);
            players[1] = new WTTTplayer(player2Name, 'O');
        }
        else {
            players[1] = new RandomWTTTPlayer('O');
        }

        // Create the game manager and run the game
        GameManager<char> WTTT_game(B, players);
        WTTT_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
    }


    else if (game == "5") {
        NumericalBoard<int> *B = new NumericalBoard<int>();  // Set up the board
        Player<int> *players[2];    // Set up player 1
        players[0] = new NumericalPlayer(player1Name, 50);

        // Set up player 2
        if (player2 == "1") {
            cout << "Enter Player 2 name: ";
            cin.ignore();
            getline(cin, player2Name);
            player2Name[0] = toupper(player2Name[0]);
            players[1] = new NumericalPlayer(player2Name, 50);
        } else {
            players[1] = new Numerical_Random_Player(50);
        }

        // Create the game manager and run the game
        GameManager<int> Numerical_game(B, players);
        Numerical_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
    }

    else if (game == "7"){
        _4x4_TicTacToe_Board<char> *B = new _4x4_TicTacToe_Board<char>();  // Set up the board
        Player<char> *players[2];  // Set up player 1
        players[0] = new _4x4_TicTacToe_Player<char>(player1Name, 'X');

        // Set up player 2
        if (player2 == "1") {
            cout << "Enter Player 2 name: ";   // Get the name of player 2
            cin.ignore();
            getline(cin, player2Name);
            player2Name[0] = toupper(player2Name[0]);
            players[1] = new _4x4_TicTacToe_Player<char>(player2Name, 'O');
        }
        else {
            players[1] = new _4x4_TicTacToe_Random_Player<char>('O');
        }

        // Create the game manager and run the game
        GameManager<char> _4x4_TicTacToe_game(B, players);
        _4x4_TicTacToe_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
    }

    else if (game == "8"){
        UltimateBoard *B = new UltimateBoard();  // Set up the board
        Player<char> *players[2];  // Set up player 1
        players[0] = new UltimatePlayer(player1Name, 'X');

        // Set up player 2
        if (player2 == "1") {
            cout << "Enter Player 2 name: ";
            cin.ignore();
            getline(cin, player2Name);
            player2Name[0] = toupper(player2Name[0]);
            players[1] = new UltimatePlayer(player2Name, 'O');
        }
        else {
            players[1] = new Ultimate_Random_Player('O');
        }

        // Create the game manager and run the game
        GameManager<char> Ultimate_game(B, players);
        Ultimate_game.run();

        // Clean up
        delete B;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }
    }
    return 0;
}



