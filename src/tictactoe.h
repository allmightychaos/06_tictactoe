#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>
#include <vector>

class TicTacToe {
public:
    TicTacToe(std::string player1, std::string player2);
    void play();
    void algorithmPlay();

private:
    std::string player1_;
    std::string player2_;
    std::string currentPlayer_;
    std::vector<std::string> board_;

    std::string getColor(int board_index);
    void printBoard();
    bool checkWin();
    bool checkTie();
    void switchPlayers();
    bool makeMove(int move);

    int algorithm();
};

#endif 