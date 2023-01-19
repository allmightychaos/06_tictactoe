#include <iostream>
#include "tictactoe.h"

int main(int argc, char* argv[]) {
    system("clear");
    if (argc < 3) {
        std::cout << "Please enter two player names" << std::endl;
        return 1;
    }

    std::string player1 = argv[1];
    std::string player2 = argv[2];

    TicTacToe game(player1, player2);
    game.play();

    return 0;
}