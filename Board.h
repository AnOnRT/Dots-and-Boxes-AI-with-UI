#ifndef DOTSANDBOXES_BOARD_H
#define DOTSANDBOXES_BOARD_H

#include <vector>
#include <iostream>
#include "Player.h"
#include "Move.h"
#include "Box.h"

class Board {
public:
    explicit Board(int size);
    Board(){
        size = 3;
    };

    std::vector<Move> getAllPossibleMoves() const;
    bool makeMove(const Move& move, Player& player);
    bool checkCompleteBox(const Move& move) const;

    void adjustOwnershipAndScore(Box& box, Player& computer, Player& human);
    void undoMove(const Move& mv, Player& computer, Player& human);


    bool isGameOver() const;


    int evaluateBoard(char computerSymbol, char humanSymbol) const;
    int evaluateBoardAdvanced(char computerSymbol, char humanSymbol, char currentPlayerSymbol) const;

    int evaluateChainPotential(int x, int y, char playerSymbol) const;
    int evaluateDirection( int startX, int startY, int dx, int dy, char playerSymbol) const;
    bool isChainable(const Box& box, int dx, int dy) const;
    bool valid(int x, int y, int size) const;

    std::pair<int, int> calculateScores(char player1Symbol, char player2Symbol) const;

    int getSize() const;

    std::vector<Box>& operator[](int index) {
        return board[index];
    }

    const std::vector<Box>& operator[](int index) const {
        return board[index];
    }
    bool getEdgeState(int x, int y, char direction) const;

    std::vector<char> getOwnersArray() const;

private:
    int size;
    std::vector<std::vector<Box>> board;
};

#endif //DOTSANDBOXES_BOARD_H
