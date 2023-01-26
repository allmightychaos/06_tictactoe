#include <iostream>
#include "tictactoe.h"

int main(int argc, char* argv[]) {
    system("clear");
    std::string playAgain;

    if (argc <= 1) {
        std::cout << "<=2: Please enter one or two player names" << std::endl;
        for (int i = 0; i < argc; i++) {
            std::cout << argv[i] << std::endl;
        }
        return 1;
    }
    else if (argc == 2) {
        std::cout << "Do you want to play against the computer? (y/n) ";
        std::cin >> playAgain;
        if (playAgain == "y") {
            std::string player1 = argv[1];
            std::string player2 = "Bob";
            TicTacToe game(player1, player2);
            game.algorithmPlay();
        }
        else if (playAgain == "n") {
            std::cout << "Please enter two player names" << std::endl;
            return 1;
        }
    } 
    else if (argc > 3) {
        std::cout << ">4: Please enter one or two player names" << std::endl;
        return 1;
    }

    std::string player1 = argv[1];
    std::string player2 = argv[2];

    TicTacToe game(player1, player2);
    game.play();

    return 0;
}