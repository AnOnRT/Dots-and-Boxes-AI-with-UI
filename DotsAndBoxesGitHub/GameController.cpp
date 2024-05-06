#include "GameController.h"

GameController::GameController(int size, const std::string& playerName, char playerSymbol,
               const std::string& computerName, char computerSymbol, GameView& view, bool currentPl)
        : board(size), player1(playerName, playerSymbol), player2(computerName, computerSymbol),
          view(view), currentPlayer(currentPl) {}

GameController::GameController(GameView& view)
        :view(view){
    int boardSize = view.promptForBoardSize2(minBoardSize, maxBoardSize);
//    std::cout<< "Board Size: " << boardSize << std::endl;
    std::string playerName = view.promptForPlayerName2();
    if (playerName.length() >= 10) {
        playerName = playerName.substr(0, 10);
    }
//    std::cout<< "Player Name: " << playerName << std::endl;
    char playerSymbol = view.promptForPlayerSymbol2();
//    std::cout<< "Player Symbol: " << playerSymbol << std::endl;
    char computerSymbol = (playerSymbol == 'X' ? 'O' : 'X');
    bool currentPl = view.askStartFirst2();
//    std::cout<< "Current Player: " << currentPl << std::endl;

    while(boardSize==0 || playerName.empty() || (playerSymbol!='X' && playerSymbol!='O')){
        std::cout<<"Invalid input. Game is not starting"<<std::endl;
        exit(0);
    }
    board = Board(boardSize);
    player1 = Player(playerName, playerSymbol);
    player2 = Player("Computer", computerSymbol);
    currentPlayer = currentPl;
}




void GameController::playGame() {

    std::pair<std::string, std::string> msgs;
    while (!board.isGameOver() && view.window.isOpen()) {
        sf::Event event;
        while (view.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                view.window.close();
        }

        std::string curName = currentPlayer ? player1.getName() : player2.getName();

        view.window.clear(sf::Color::Black);
        view.drawBoard2(board.getSize(), msgs.second, msgs.first, currentPlayer, curName);
        view.window.display();
        if (currentPlayer) {
            msgs = processPlayerMove(player1, msgs);
        } else {
            msgs = processPlayerMove(player2, msgs);
        }
        switchPlayer();
    }
    while (view.window.isOpen()) {
        view.window.clear(sf::Color::Black);
        sf::Event event;
        while (view.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                view.window.close();
        }
        view.drawBoard2(board.getSize());
        view.displayFinalScore(player1.getName(), player1.getSymbol(), player2.getName(), player2.getSymbol(), board.calculateScores(player1.getSymbol(), player2.getSymbol()).first, board.calculateScores(player1.getSymbol(), player2.getSymbol()).second);
        view.window.display();

    }

}
std::pair<std::string, std::string> GameController::processPlayerMove(Player& player, std::pair<std::string, std::string> msgs) {
    bool validMove = false;
    Move move;
    std::string msg_h = msgs.first;
    std::string msg_c = msgs.second;
    do {

        if (player.getName() == "Computer") {
            move = findBestMove_advanced(board, player2, player1); // Assuming human is the other player
            //view.showMessage(player.getName() + " (" + player.getSymbol() + ") - Entered move " + std::to_string(move.x) + " " + std::to_string(move.y) + " " + move.dir);
            //view.drawBoard2(board.getSize(), msgs.second, msgs.first, currentPlayer, player.getName());
            msg_c = player.getName() + " (" + player.getSymbol() + ") - Entered move " + std::to_string(move.x) + " " + std::to_string(move.y) + " " + move.dir;
        }
        else {
            bool validInput = false;
            sf::Event event;
            while (view.window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    view.window.close();
                if (event.type == sf::Event::MouseButtonPressed) {
                    validInput = view.handleMouseInput();
                }
            }

            std::pair<std::pair<int, int>, char> move_form = view.determineMove2();
            move = Move(move_form.first.first, move_form.first.second, move_form.second);
            view.drawBoard2(board.getSize(), msgs.second, msgs.first, currentPlayer, player.getName());
            view.window.display();
        }
        validMove = board.makeMove(move, player);

        if (!validMove) {
            //view.drawBoard(board);
            view.clearClicks();
        } else {
            if (player.getName() != "Computer") {
                msg_h = player.getName() + " (" + player.getSymbol() + ") - Entered move " + std::to_string(move.x) + " " + std::to_string(move.y) + " " + move.dir;
//                view.clicks.clear();
                view.emptyClick();
            }
            else {
                msg_c = player.getName() + " (" + player.getSymbol() + ") - Entered move " + std::to_string(move.x) + " " + std::to_string(move.y) + " " + move.dir;
            }

              view.addLine(view.createLine(move.x, move.y, move.dir));
            if (board.checkCompleteBox(move)) {
//                view.showMessage("A box was completed! " + player.getName() + " gets another turn.");
//                view.owners = board.getOwnersArray();
                  view.setOwners(board.getOwnersArray());
            } else {
                break;
            }
//            view.drawBoard2(board.getSize(), msgs.second, msgs.first, currentPlayer, player.getName());
        }

        view.drawBoard2(board.getSize(), msgs.second, msgs.first, currentPlayer, player.getName());

    } while ((!validMove || board.checkCompleteBox(move)) && !board.isGameOver() && view.window.isOpen());
    return std::pair<std::string, std::string>(msg_h, msg_c);
}

void GameController::switchPlayer() {
    currentPlayer = !currentPlayer;
}


int GameController::minimax(Board& board, int depth, bool isMaximizingPlayer, int alpha, int beta, Player& computer, Player& human) {
    if (depth == 0 || board.isGameOver()) {
        return board.evaluateBoard(computer.getSymbol(), human.getSymbol());
    }

    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;
        for (auto& move : board.getAllPossibleMoves()) {
            board.makeMove(move, computer); // Check if a box was completed
            bool completed = board.checkCompleteBox(move);

            int eval = minimax(board, depth - 1, completed ? isMaximizingPlayer : !isMaximizingPlayer, alpha, beta, computer, human);
            board.undoMove(move, computer, human); // Undo for the computer

            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else {
        int minEval = INT_MAX;
        for (auto& move : board.getAllPossibleMoves()) {
            board.makeMove(move, human); // Check if a box was completed
            bool completed = board.checkCompleteBox(move);

            int eval = minimax(board, depth - 1, completed ? isMaximizingPlayer : !isMaximizingPlayer, alpha, beta, computer, human);
            board.undoMove(move, computer, human); // Undo for the human

            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

Move GameController::findBestMove(Board& board, Player& computer, Player& human) {
    int bestValue = INT_MIN;
    Move bestMove = { -1, -1, ' ' }; // Initialize with an invalid move

    // Get all possible moves from the Board instance
    auto moves = board.getAllPossibleMoves();

    for (auto& move : moves) {
        board.makeMove(move, computer);
        int moveValue = minimax(board, DEPTH - 1, false, INT_MIN, INT_MAX, computer, human);
        board.undoMove(move, computer, human);

        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = move;
        }
    }

    return bestMove;
}

int GameController::minimax_advanced(Board& board, int depth, bool isMaximizingPlayer, int alpha, int beta, Player& computer, Player& human) {
    if (depth == 0 || board.isGameOver()) {
        // Determine whose evaluation perspective to use based on the current player
        char currentPlayerSymbol = isMaximizingPlayer ? human.getSymbol() : computer.getSymbol();
        return board.evaluateBoardAdvanced(computer.getSymbol(), human.getSymbol(), currentPlayerSymbol);
    }

    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;
        for (auto& move : board.getAllPossibleMoves()) {
            board.makeMove(move, computer);
            bool completed = board.checkCompleteBox(move); // Assume returns true if a box was completed

            // Continue as maximizing player if a box was completed, otherwise switch
            int eval = minimax_advanced(board, depth - 1, completed ? isMaximizingPlayer : !isMaximizingPlayer, alpha, beta, computer, human);
            board.undoMove(move, human, computer); // Undo the move

            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
                break;
        }
        return maxEval;
    }
    else {
        int minEval = INT_MAX;
        for (auto& move : board.getAllPossibleMoves()) {
            board.makeMove(move, human);
            bool completed = board.checkCompleteBox(move); // Assume returns true if a box was completed

            // Continue as minimizing player if a box was completed, otherwise switch
            int eval = minimax_advanced(board, depth - 1, completed ? isMaximizingPlayer : !isMaximizingPlayer, alpha, beta, computer, human);
            board.undoMove(move, human, computer); // Undo the move

            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
                break;
        }
        return minEval;
    }}

Move GameController::findBestMove_advanced(Board& board, Player& computer, Player& human) {
    int bestValue = INT_MIN;
    Move bestMove = { -1, -1, ' ' }; // Initialize with an invalid move

    // Get all possible moves from the Board instance
    auto moves = board.getAllPossibleMoves();

    for (auto& move : moves) {
        board.makeMove(move, computer);
        int moveValue = minimax_advanced(board, DEPTH - 1, false, INT_MIN, INT_MAX, computer, human);
        board.undoMove(move, computer, human);

        if (moveValue > bestValue) {
            bestValue = moveValue;
            bestMove = move;
        }
    }

    return bestMove;
}