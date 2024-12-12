#include "BoardGame_Classes.h"
#include "Four-in-a-row_MinMaxPlayer.h"
#include "Numerical_MinMaxPlayer.h"

int main(){
    cout << "Welcome to Mental Games :)\n\n";

    string game, enemy, player1Name, player2Name;
    cout << "Games Menu:\n1)Four in a row\n2)Numerical Tic-Tac-Toe\n3)Exit\nChoose a game (1 ,2 or 3): ";
    cin >> game;

    // Exit
    if (game == "3")
        return 0;

    // Check if a user entered a valid choice or not
    while(game != "1" && game != "2"){
        cout <<"Enter the number of game: ";
        cin >> game;
    }

    // Set up player 1
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, player1Name);
    player1Name[0] = toupper(player1Name[0]);

    // Choose player 2
    do {
        cout << "1) Play vs friend\n2) Play vs Random Computer\n3) Play vs Smart Computer (AI)\n";
        cout << "Enter your choice (1, 2 or 3): ";
        cin >> enemy;
    } while (enemy != "1" && enemy != "2" && enemy != "3");


    // Four in a row Game
    if (game == "1"){
        FourInARowBoard<char> *B = new FourInARowBoard<char>();
        Player<char>* players[2];
        players[0] = new FourInARowPlayer<char>(player1Name, 'X');
        // Set up player 2 if he is a friend
        if (enemy == "1"){
            cout << "Enter name player 2: ";
            cin.ignore();
            getline(cin, player2Name);
            player2Name[0] = toupper(player2Name[0]);
            players[1] = new FourInARowPlayer<char>(player2Name, 'O');
        }
        // Set up player 2 if it is a random computer player
        else if (enemy == "2") {
            players[1] = new FourInARow_Random_Player<char>('O');
        }
        // Set up player 2 if it is AI player
        else {
            players[1] = new FourInARow_MinMax_Player<char>('O');
            players[1]->setBoard(B);
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

    // Numerical Tic-Tac-Toe Game
    else if (game == "2"){
        NumericalBoard<int> *B = new NumericalBoard<int>();
        Player<int>* players[2];
        players[0] = new NumericalPlayer<int>(player1Name, 'X');
        // Set up player 2 if he is a friend
        if (enemy == "1"){
            cout << "Enter name player 2: ";
            cin.ignore();
            getline(cin, player2Name);
            player2Name[0] = toupper(player2Name[0]);
            players[1] = new NumericalPlayer<int>(player2Name, 'O');
        }
        // Set up player 2 if it is a random computer player
        else if (enemy == "2") {
            players[1] = new Numerical_Random_Player<int>('O');
        }
        // Set up player 2 if it is AI player
        else {
            players[1] = new Numerical_MinMax_Player<int>('O');
            players[1]->setBoard(B);
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

    return 0;
}