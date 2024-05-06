#ifndef DOTSANDBOXES_GAMEVIEW_H
#define DOTSANDBOXES_GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include "GridLine.h"


class GameView {
// Window object
    sf::Font font;

    std::vector<GridPosition> clicks;
    std::vector<Line> lines;
    std::vector<char> owners;

    sf::Text text;
    sf::RectangleShape inputBox;
    sf::Text inputText;
    sf::Text welcomeMessage;

public:

    const int spacing = 50; // Spacing between dots
    const int dotSize = 5; // Size of the dots
    sf::RenderWindow window;

    void clearClick();
    void setOwners(const std::vector<char>& owners);
    void addLine(const Line& line);
    void emptyClick();

    void showMessage(const std::string& message);
    void showMessage2(const std::string& message, int posx, int posy, int size=20, sf::Color color = sf::Color::Red);
    void displayFinalScore(const std::string player1Name, const char player1Sym, const std::string player2Name, const char player2Sym, int player1Score, int player2Score);


    GameView(); // Constructor
    //Copy constructor

    void drawBoard2(int size, std::string msg_h="", std::string msg_c="", bool change=true, std::string curName=""); // Method to draw the game board

    void setupText();
    int promptForBoardSize2(int min, int max);
    std::string promptForPlayerName2();
    char promptForPlayerSymbol2();
    bool askStartFirst2();
    std::string promptForString(const std::string& prompt);
    int promptForInt(const std::string& prompt, int min, int max);

    bool handleMouseInput();
    bool areAdjacent(const GridPosition& pos1, const GridPosition& pos2);

    void drawLine2(const GridPosition& start, const GridPosition& end);
    void drawAllLines();

    std::pair<std::pair<int, int>, char> determineMove2();

    void clearClicks();

    Line createLine(int x, int y, char direction);


    int promptForBoardSize();
    std::string promptForPlayerName();
    char promptForPlayerSymbol();
    void getMoveInput(int& x, int& y, char& direction);
    bool askStartFirst();
};


#endif //DOTSANDBOXES_GAMEVIEW_H
