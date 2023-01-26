#include "tictactoe.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <iomanip>

TicTacToe::TicTacToe(std::string player1, std::string player2) : player1_(player1), player2_(player2) {
    // Initialize the board
    for(int i = 1; i <= 9; i++) {
        board_.push_back(std::to_string(i));
    }

    // Seed the random number generator
    srand(time(NULL));

    // Randomly choose a starting player
    int startingPlayer = rand() % 2;
    if (startingPlayer == 0) {
        currentPlayer_ = player1_;  
        std::cout << "Player " << player1_ << " (X) goes first!" << std::endl;
    } else {
        currentPlayer_ = player2_;
        std::cout << "Player " << player2_ << " (O) goes first!" << std::endl;
    }
}

void TicTacToe::play() {
    // game loop
    printBoard();

    while (true) {
        // Get the player's move
        int move;
        std::cout << "Player " << currentPlayer_ << ", enter a move (1-9): ";
        std::cin >> move;

        // Validate the move
        if (!makeMove(move)) {
            std::cout << "Invalid move, please try again." << std::endl;
            continue;
        }

        printBoard();
        
        if (checkWin()) {
            std::cout << "Player " << currentPlayer_ << " wins!" << std::endl;
            break;
        } else if (checkTie()) {
            std::cout << "Tie game!" << std::endl;
            break;
        }

        switchPlayers();
    }

    char playAgain;
    while(true) {
        std::cout << "Do you want to play again? (y/n) ";
        std::cin >> playAgain;
        if(playAgain == 'y' || playAgain == 'n') break;
    }
    if (playAgain == 'y') {
        TicTacToe newGame(player1_, player2_);
        newGame.play();
    }
}

void TicTacToe::algorithmPlay() {
    // game loop
    printBoard();

    while (true) {
        // Get the player's move (and check if its the computer's turn)
        if (currentPlayer_ == "Bob") {
            int algorithmMove_ = algorithm();

            while (board_[algorithmMove_ - 1] == "X" || board_[algorithmMove_ - 1] == "O") {
                algorithmMove_ = algorithm();
            }

            // Validate the move
            if (!makeMove(algorithmMove_)) {
                continue;
            }

        } else {
            int move;
            std::cout << "Player " << currentPlayer_ << ", enter a move (1-9): ";
            std::cin >> move;

            // Validate the move
            if (!makeMove(move)) {
                std::cout << "Invalid move, please try again." << std::endl;
                continue;
            }
        }

        printBoard();
        
        if (checkWin()) {
            std::cout << "Player " << currentPlayer_ << " wins!" << std::endl;
            break;
        } else if (checkTie()) {
            std::cout << "Tie game!" << std::endl;
            break;
        }

        switchPlayers();
    }

    char playAgain;
    while(true) {
        std::cout << "Do you want to play again? (y/n) ";
        std::cin >> playAgain;
        if(playAgain == 'y' || playAgain == 'n') break;
    }
    if (playAgain == 'y') {
        TicTacToe newGame(player1_, player2_);
        newGame.algorithmPlay();
    } else {
        exit(0);
    }
}

void TicTacToe::switchPlayers() {
    if (currentPlayer_ == player1_) {
        currentPlayer_ = player2_;
    } else {
        currentPlayer_ = player1_;
    }
}

std::string TicTacToe::getColor(int board_index) {
    if (board_[board_index] == "X") {
        return "\033[1;31mX\033[0m";
    }
    else if (board_[board_index] == "O") {
        return "\033[1;34mO\033[0m";
    }
    else {
        return board_[board_index];
    }
}

void TicTacToe::printBoard() {

    // Declare new variables to store
    std::string player1_new = player1_;
    std::string player2_new = player2_;

    // Get the size of the player names
    int player1_size = player1_.size();
    int player2_size = player2_.size();

    // Check if name is too long
    if (player1_size > 11){
        player1_new = player1_.substr(0, 11);
    }
    if (player2_size > 11){
        player2_new = player2_.substr(0, 11);
    }


    std::cout << "╔═══════════╗" << std::endl;
    std::cout << "║" << "\033[1;31m" << player1_new << "\033[0m" << std::setw(14 - player1_size) << "║" << std::endl;
    std::cout << "╠═══╦═══╦═══╣" << std::endl;
    std::cout << "║ " << std::setw(1) << getColor(0) << " ║ " << std::setw(1) << getColor(1) << " ║ " << std::setw(1) << getColor(2) << " ║" << std::endl;
    std::cout << "╠═══╬═══╬═══╣" << std::endl;
    std::cout << "║ " << std::setw(1) << getColor(3) << " ║ " << std::setw(1) << getColor(4) << " ║ " << std::setw(1) << getColor(5) << " ║" << std::endl;
    std::cout << "╠═══╬═══╬═══╣" << std::endl;
    std::cout << "║ " << std::setw(1) << getColor(6) << " ║ " << std::setw(1) << getColor(7) << " ║ " << std::setw(1) << getColor(8) << " ║" << std::endl;
    std::cout << "╠═══╩═══╩═══╣" << std::endl;
    std::cout << "║" "\033[1;34m" << player2_new << "\033[0m" << std::setw(14 - player2_size) << "║" << std::endl;
    std::cout << "╚═══════════╝" << std::endl;
}

bool TicTacToe::checkWin() {
    // Check rows (horizontal)
    for (int i = 0; i < 9; i += 3) {
        if (board_[i] == board_[i+1] && board_[i+1] == board_[i+2]) {
            return true;
        }
    }

    // Check columns (vertical)
    for (int i = 0; i < 3; i++) {
        if (board_[i] == board_[i+3] && board_[i+3] == board_[i+6]) {
            return true;
        }
    }

    // Check diagonals (diagonal)
    if (board_[0] == board_[4] && board_[4] == board_[8]) {
        return true;
    }
    if (board_[2] == board_[4] && board_[4] == board_[6]) {
        return true;
    }

    // No win = 
    return false;
}

bool TicTacToe::checkTie() {
    for (std::string cell : board_) {
        if (cell != "X" && cell != "O") {
            return false;
        }
    }
    return !checkWin();

    /*
    ! Explanation:
    * If any of the element is not filled with "X" or "O" ,
    * t will return false indicating the game is not tied yet. 
    
    * If all the elements are filled and checkWin() returns false, 
    * it will return true indicating the game is tied.
    */
}

bool TicTacToe::makeMove(int move) {
    if (move < 1 || move > 9) {
        return false;
    }
    if (board_[move-1] == "X" || board_[move-1] == "O") {
        return false;
    }

    if (currentPlayer_ == player1_) {
        board_[move-1] = "X";
    } else {
        board_[move-1] = "O";
    }
    return true;
}

int TicTacToe::algorithm() {
    return rand() % 9 + 1;
}