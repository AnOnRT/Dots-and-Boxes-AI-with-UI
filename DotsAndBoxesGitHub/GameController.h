
#ifndef DOTSANDBOXES_GAMECONTROLLER_H
#define DOTSANDBOXES_GAMECONTROLLER_H

#include "Board.h"
#include "Player.h"
#include "GameView.h"


class GameController {
    Board board;
    Player player1;
    Player player2;
    GameView& view;
    bool currentPlayer;

public:
    int DEPTH = 3;
    int maxBoardSize = 5;
    int minBoardSize = 3;

    GameController(int size);
    GameController(GameView& view);

    GameController(int size, const std::string& playerName, char playerSymbol,
                   const std::string& computerName, char computerSymbol, GameView& view, bool currentPl);


    void playGame();
    std::pair<std::string, std::string> processPlayerMove(Player& player, std::pair<std::string, std::string> msgs);
    void switchPlayer();
    // AI and game logic methods
    int minimax(Board& board, int depth, bool isMaximizingPlayer, int alpha, int beta, Player& computer, Player& human);
    Move findBestMove(Board& board, Player& computer, Player& human);
    int minimax_advanced(Board& board, int depth, bool isMaximizingPlayer, int alpha, int beta, Player& computer, Player& human);
    Move findBestMove_advanced(Board& board, Player& computer, Player& human);
    void drawGrid(sf::RenderWindow& window, int gridSize, int dotSize, int spacing) ;


};

#endif //DOTSANDBOXES_GAMECONTROLLER_H
