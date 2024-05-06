#include "Board.h"

Board::Board(int size) : size(size), board(size, std::vector<Box>(size)) {}

int Board::getSize() const{
    return size;
}

bool Board::getEdgeState(int x, int y, char direction) const{
    if (x < 0 || x >= size || y < 0 || y >= size) {
        return false;
    }

    switch (direction) {
        case 'L':
            return board[y][x].left.isDrawn;
        case 'R':
            return board[y][x].right.isDrawn;
        case 'U':
            return board[y][x].top.isDrawn;
        case 'D':
            return board[y][x].bottom.isDrawn;
        default:
            return false;
    }
}

std::vector<Move> Board::getAllPossibleMoves() const {
    std::vector<Move> moves;

    for (int y = 0; y < board.size(); ++y) {
        for (int x = 0; x < board[y].size(); ++x) {
            // Check each edge of the box and if it's not drawn, add it as a possible move
            if (!board[y][x].left.isDrawn && x >= 0) {
                moves.push_back({ x, y, 'L' });
            }
            if (!board[y][x].top.isDrawn && y >= 0) {
                moves.push_back({ x, y, 'U' });
            }
            if (!board[y][x].right.isDrawn && x <= board[y].size() - 1) {
                moves.push_back({ x, y, 'R' });
            }
            if (!board[y][x].bottom.isDrawn && y <= board.size() - 1) {
                moves.push_back({ x, y, 'D' });
            }
        }
    }
    return moves;
}

bool Board::makeMove(const Move& mv, Player& currentPlayer) {

    if (mv.x < 0 || mv.x >= board.size() || mv.y < 0 || mv.y >= board.size()) {
        return false;
    }
    auto markEdgeAndUpdateOwnership = [&currentPlayer](Edge& edge, Box& box) {
        edge.isDrawn = true;
        if (box.isCompleted() && box.owner == ' ') {
            box.owner = currentPlayer.getSymbol();
            currentPlayer.incrementScore();
        }
    };
    bool completedABox = false;
    switch (mv.dir) {
        case 'L':
            if (board[mv.y][mv.x].left.isDrawn) return false;
            markEdgeAndUpdateOwnership(board[mv.y][mv.x].left, board[mv.y][mv.x]);
            if (mv.x > 0) {
                markEdgeAndUpdateOwnership(board[mv.y][mv.x - 1].right, board[mv.y][mv.x - 1]);
            }
            break;
        case 'R':
            if (board[mv.y][mv.x].right.isDrawn) return false;
            markEdgeAndUpdateOwnership(board[mv.y][mv.x].right, board[mv.y][mv.x]);
            if (mv.x < board.size() - 1) {
                markEdgeAndUpdateOwnership(board[mv.y][mv.x + 1].left, board[mv.y][mv.x + 1]);
            }
            break;
        case 'U':
            if (board[mv.y][mv.x].top.isDrawn) return false;
            markEdgeAndUpdateOwnership(board[mv.y][mv.x].top, board[mv.y][mv.x]);
            if (mv.y > 0) {
                markEdgeAndUpdateOwnership(board[mv.y - 1][mv.x].bottom, board[mv.y - 1][mv.x]);
            }
            break;
        case 'D':
            if (board[mv.y][mv.x].bottom.isDrawn) return false;
            markEdgeAndUpdateOwnership(board[mv.y][mv.x].bottom, board[mv.y][mv.x]);
            if (mv.y < board.size() - 1) {
                markEdgeAndUpdateOwnership(board[mv.y + 1][mv.x].top, board[mv.y + 1][mv.x]);
            }
            break;
        default:
            return false;
    }

    return true;
}

bool Board::checkCompleteBox(const Move& mv) const{
    bool completedABox = board[mv.y][mv.x].isCompleted() ||
                         (mv.dir == 'L' && mv.x > 0 && board[mv.y][mv.x - 1].isCompleted()) ||
                         (mv.dir == 'R' && mv.x < board.size() - 1 && board[mv.y][mv.x + 1].isCompleted()) ||
                         (mv.dir == 'U' && mv.y > 0 && board[mv.y - 1][mv.x].isCompleted()) ||
                         (mv.dir == 'D' && mv.y < board.size() - 1 && board[mv.y + 1][mv.x].isCompleted());
    return completedABox;
}

void Board::adjustOwnershipAndScore(Box& box, Player& computer, Player& human) {
    if (!box.isCompleted()) {
        return;
    }

    if (box.owner == computer.getSymbol()) {
        computer.decrementScore();
        box.owner = ' ';
    }
    else if (box.owner == human.getSymbol()) {
        human.decrementScore();
        box.owner = ' ';
    }
}

void Board::undoMove(const Move& mv, Player& computer, Player& human) {
    if (board[mv.y][mv.x].isCompleted()) {
        adjustOwnershipAndScore(board[mv.y][mv.x], computer, human);
    }

    if (mv.dir == 'L' && mv.x > 0 && board[mv.y][mv.x - 1].isCompleted()) {
        adjustOwnershipAndScore(board[mv.y][mv.x - 1], computer, human);
    }

    if (mv.dir == 'R' && mv.x < board.size() - 1 && board[mv.y][mv.x + 1].isCompleted()) {
        adjustOwnershipAndScore(board[mv.y][mv.x + 1], computer, human);
    }

    if (mv.dir == 'U' && mv.y > 0 && board[mv.y - 1][mv.x].isCompleted()) {
        adjustOwnershipAndScore(board[mv.y - 1][mv.x], computer, human);
    }

    if (mv.dir == 'D' && mv.y < board.size() - 1 && board[mv.y + 1][mv.x].isCompleted()) {
        adjustOwnershipAndScore(board[mv.y + 1][mv.x], computer, human);
    }


    switch (mv.dir) {
        case 'L':
            board[mv.y][mv.x].left.isDrawn = false;
            if (mv.x > 0) {
                board[mv.y][mv.x - 1].right.isDrawn = false;
            }
            break;
        case 'R':
            board[mv.y][mv.x].right.isDrawn = false;
            if (mv.x < board.size() - 1) {
                board[mv.y][mv.x + 1].left.isDrawn = false;
            }
            break;
        case 'U':
            board[mv.y][mv.x].top.isDrawn = false;
            if (mv.y > 0) {
                board[mv.y - 1][mv.x].bottom.isDrawn = false;
            }
            break;
        case 'D':
            board[mv.y][mv.x].bottom.isDrawn = false;
            if (mv.y < board.size() - 1) {
                board[mv.y + 1][mv.x].top.isDrawn = false;
            }
            break;
    }
}

std::vector<char> Board::getOwnersArray() const {
    std::vector<char> owners;
    owners.reserve(size * size);  // Pre-allocate memory assuming 'size' is the dimension of your board

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            owners.push_back(board[y][x].getOwner());
        }
    }

    return owners;
}

bool Board::isGameOver() const {
    bool gameOver = true;
    for (const auto& row : board) {
        for (const auto& box : row) {
            if (!box.isCompleted()) {
                gameOver = false;
                break;
            }
        }
        if (!gameOver) {
            break;
        }
    }
    return gameOver;
}

int Board::evaluateBoard(char computerSymbol, char humanSymbol) const{
    int computerScore = 0, humanScore = 0;

    for (const auto& row : board) {
        for (const auto& box : row) {
            if (box.owner == computerSymbol) ++computerScore;
            else if (box.owner == humanSymbol) ++humanScore;
        }
    }

    return computerScore - humanScore;
}

int Board::evaluateBoardAdvanced(char computerSymbol, char humanSymbol, char currentPlayerSymbol) const{
    int computerScore = 0, humanScore = 0;
    int computerPotential = 0, humanPotential = 0;
    int totalEdges = 0;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            const auto& box = board[i][j];
            int edgeCount = (box.top.isDrawn ? 1 : 0) + (box.bottom.isDrawn ? 1 : 0)
                            + (box.left.isDrawn ? 1 : 0) + (box.right.isDrawn ? 1 : 0);

            totalEdges += edgeCount;
            if (box.owner == computerSymbol) {
                computerScore++;
            }
            else if (box.owner == humanSymbol) {
                humanScore++;
            }

            if (edgeCount == 3) {
                if (currentPlayerSymbol == computerSymbol) {
                    computerPotential++;
                }
                else {
                    humanPotential++;
                }
            }

            if (edgeCount == 2) {
                int chainValue = evaluateChainPotential(i, j, currentPlayerSymbol);
                if (currentPlayerSymbol == computerSymbol) {
                    computerPotential += chainValue;
                }
                else {
                    humanPotential += chainValue;
                }
            }
        }
    }

    int scoreDifference = computerScore - humanScore;
    int potentialDifference = computerPotential - humanPotential;

    float weight = 0; // Default weight for potential difference.
    int totalPossibleEdges = board.size() * board[0].size() * 4;
    float gameProgress = static_cast<float>(totalEdges) / totalPossibleEdges;

    if (gameProgress < 0.5) {
        weight = 1; // Early game, prioritize potential more.
    } else if (gameProgress > 0.5) {
        weight = 0; // Late game, prioritize actual score.
    }

    return scoreDifference + int(weight * potentialDifference);

}

int Board::evaluateChainPotential(int x, int y, char playerSymbol) const {
    int chainValue = 0;
    std::vector<std::pair<int, int>> directions = { {0, 1}, {1, 0} };

    for (auto& dir : directions) {
        int forwardChain = evaluateDirection(x, y, dir.first, dir.second, playerSymbol);
        int backwardChain= evaluateDirection(x, y, -dir.first, -dir.second, playerSymbol);
        chainValue += forwardChain + backwardChain;
    }

    return chainValue;
}

int Board::evaluateDirection( int startX, int startY, int dx, int dy, char playerSymbol) const{
    int tempX = startX + dx;
    int tempY = startY + dy;
    int potential = 0;

    while (valid(tempX, tempY, board.size()) && isChainable(board[tempX][tempY], dx, dy)) {
        if (board[tempX][tempY].owner == ' ') {  // If no owner yet, it's a potential gain
            potential++;
        }
        tempX += dx;
        tempY += dy;
    }

    return potential;
}

bool Board::isChainable(const Box& box, int dx, int dy) const{
    return (box.left.isDrawn && box.right.isDrawn && !box.top.isDrawn && !box.bottom.isDrawn) || (box.top.isDrawn && box.bottom.isDrawn && !box.left.isDrawn && !box.right.isDrawn);
}

bool Board::valid(int x, int y, int size) const{
    return x >= 0 && y >= 0 && x < size && y < size;
}

std::pair<int, int> Board::calculateScores(char player1Symbol, char player2Symbol) const {
    int player1Score = 0, player2Score = 0;
    for (const auto& row : board) {
        for (const auto& box : row) {
            if (box.owner == player1Symbol) {
                ++player1Score;
            }
            else if (box.owner == player2Symbol) {
                ++player2Score;
            }
        }
    }
    return std::make_pair(player1Score, player2Score);
}

