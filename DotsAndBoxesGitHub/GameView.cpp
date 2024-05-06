
#include "GameView.h"
#include <iostream>
#include <filesystem>

GameView::GameView() : window(sf::VideoMode(500, 600), "Dots and Boxes", sf::Style::Close) {
//    std::cout << "Current path is " << std::filesystem::current_path() << std::endl;
    namespace fs = std::filesystem;
    fs::path sourceFilePath = __FILE__;
    fs::path sourceDir = sourceFilePath.parent_path();
    fs::path fontPath = sourceDir / "Roboto-Black.ttf";
    if (!font.loadFromFile(fontPath.string())) {
        std::cerr << "Failed to load font\n";
    }
    window.setFramerateLimit(60);
    setupText();
}


void GameView::clearClicks() {
    if(clicks.size() == 2){
        clicks.clear();
    }
}

void GameView::emptyClick(){
    clicks.clear();
}


void GameView::setOwners(const std::vector<char>& owners) {
    this->owners = owners;
}
void GameView::addLine(const Line& line) {
    lines.push_back(line);
}

std::pair<std::pair<int, int>, char> GameView::determineMove2() {
    if (clicks.size() != 2) {
        return {{-1, -1}, ' '};
    }

    const auto& first = clicks[0];
    const auto& second = clicks[1];


    int x, y;
    char direction;
    if (first.x == second.x) {
        // Vertical movement
        if (first.y == second.y + 1) {
            // First is below second
            if(second.x - 1 >= 0){
                x = second.x-1;
                y = second.y;
                direction = 'R';
            }
            else{
                x = second.x;
                y = second.y;
                direction = 'L';
            }
        } else if (first.y + 1 == second.y) {
            if (first.x - 1 >= 0){
                x = first.x-1;
                y = first.y;
                direction = 'R';
            }
            else{
                x = first.x;
                y = first.y;
                direction = 'L';
            }
        }
    } else if (first.y == second.y) {
        // Horizontal movement
        if (first.x == second.x + 1) {
            // First is to the right of second
            if(second.y - 1 >= 0){
                x = second.x;
                y = second.y-1;
                direction = 'D';
            }
            else{
                x = second.x;
                y = second.y;
                direction = 'U';
            }
        } else if (first.x + 1 == second.x) {
            // Second is to the right of first
            if(first.y - 1 >= 0){
                x = first.x;
                y = first.y-1;
                direction = 'D';
            }
            else{
                x = first.x;
                y = first.y;
                direction = 'U';
            }

        }
    }
    clicks.clear(); // Clear the clicks if the positions are not adjacent

    return {{x, y}, direction};; // Return an empty move if none of the conditions match
}


bool GameView::areAdjacent(const GridPosition& pos1, const GridPosition& pos2) {
    // Check if the positions are horizontally or vertically adjacent
    return ((pos1.x == pos2.x && std::abs(pos1.y - pos2.y) == 1) ||
            (pos1.y == pos2.y && std::abs(pos1.x - pos2.x) == 1));
}
bool GameView::handleMouseInput() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        GridPosition gridPos = {
                static_cast<int>(mousePos.x / spacing),
                static_cast<int>(mousePos.y / spacing)
        };

        if (clicks.empty() || (clicks.size() == 1 && !(clicks.back().x == gridPos.x && clicks.back().y == gridPos.y))) {
            clicks.push_back(gridPos);
        }

        if (clicks.size() == 2 && areAdjacent(clicks[0], clicks[1])) {
            return true;
        }
        else if (clicks.size() == 2 && !areAdjacent(clicks[0], clicks[1])){
            clicks.clear(); // Clear the clicks if the positions are not adjacent
        }
        return false;
    }
    return false;
}


void GameView::drawLine2(const GridPosition& start, const GridPosition& end) {
    sf::VertexArray line(sf::Lines, 2);
    line[0].position = sf::Vector2f(start.x * spacing + spacing / 10 + spacing/5, start.y * spacing + spacing / 10 + + spacing/5);
    line[1].position = sf::Vector2f(end.x * spacing + spacing / 10 + + spacing/5, end.y * spacing + spacing / 10 + + spacing/5);
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;
    window.draw(line);
}
void GameView::drawAllLines() {
    for (const auto& line : lines) {
        drawLine2(line.start, line.end);
    }
}


void GameView::drawBoard2(int gridSize, std::string msg_c, std::string msg_h, bool change, std::string curName) {
    window.clear(sf::Color::Black);
    sf::CircleShape dot(dotSize);
    dot.setFillColor(sf::Color::White);

    sf::Text ownerText;
    ownerText.setFont(font);
    ownerText.setCharacterSize(20);  // Adjust size as needed
    ownerText.setFillColor(sf::Color::Red);

    int index = 0;
    for (int i = 0; i <= gridSize; ++i) {
        for (int j = 0; j <= gridSize; ++j) {
            dot.setPosition(j * spacing + spacing/5, i * spacing + spacing/5);
            window.draw(dot);

            if(i != gridSize && j != gridSize && !owners.empty()) {
                ownerText.setPosition(j * spacing + spacing/1.5, i * spacing + spacing / 1.7);
                std::string s(1, owners[index]);
                ownerText.setString(owners[index]);
                window.draw(ownerText);
                index++;
            }
        }
    }

    if(change){
        size_t pos = msg_h.find(' ');
        std::string firstWord = msg_h.substr(0, pos); // Extract from start to the first space
        if(firstWord == ""){
            firstWord = curName;
        }
        if(curName != ""){
            showMessage2(firstWord + "'s turn", 0, 7);
        }
    }
    else{
        size_t pos = msg_c.find(' ');
        std::string firstWord = msg_c.substr(0, pos); // Extract from start to the first space
        if(firstWord == ""){
            firstWord = curName;
        }
        if(curName != ""){
            showMessage2(firstWord + "'s turn", 0, 7);
        }
    }

    showMessage2(msg_h, 0, 8);
    showMessage2(msg_c, 0, 9);

    std::string message = "  When it is your turn, \n  click on two adjacent dots \n  to draw a line between them.";
    showMessage2(message, 5, 0, 15, sf::Color::Yellow);
    drawAllLines();
}

void GameView::displayFinalScore(const std::string player1Name, char player1Sym, const std::string player2Name, char player2Sym, int player1Score, int player2Score){
    std::string msg = "Final score: " + player1Name + " (" + player1Sym + ")" + " - " + std::to_string(player1Score) +
            ", " + player2Name + " (" + player2Sym + ")" + " - " + std::to_string(player2Score);
    showMessage2(msg, 0, 5, 20, sf::Color::Green);
}


void GameView::showMessage(const std::string& message) {
    std::cout << message << std::endl;
}
void GameView::showMessage2(const std::string& message, int posx, int posy, int size, sf::Color color) {
    sf::Text msg;
    msg.setFont(font);
    msg.setCharacterSize(size);
    msg.setFillColor(color);
    msg.setPosition(posx * spacing + spacing/1.5, posy * spacing + spacing / 1.7);
    msg.setString(message);
    window.draw(msg);
}


Line GameView::createLine(int x, int y, char direction) {
    Line line;


    switch (direction) {
        case 'U': // Left
            line.start.y = y;
            line.start.x = x;

            line.end.y = y;
            line.end.x = x + 1;
            break;
        case 'D': // Right
            line.start.y = y + 1;
            line.start.x = x;

            line.end.y = y + 1;
            line.end.x = x + 1;
            break;
        case 'L': // Up
            line.start.y = y;
            line.start.x = x;

            line.end.y = y + 1;
            line.end.x = x;
            break;
        case 'R': // Down
            line.start.y = y;
            line.start.x = x + 1;

            line.end.y = y + 1;
            line.end.x = x + 1;
            break;
        default: // In case of invalid direction, return start as end to denote no movement
            line.end = line.start;
            break;
    }

    return line;
}

void GameView::setupText() {
    welcomeMessage.setFont(font);
    welcomeMessage.setCharacterSize(24);
    welcomeMessage.setFillColor(sf::Color::Green);
    welcomeMessage.setPosition(50, 50);
    welcomeMessage.setString("      Welcome to Dots and Boxes! \n Please enter the following details:");

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(50, 120);

    inputBox.setSize(sf::Vector2f(350, 50));
    inputBox.setPosition(50, 150);
    inputBox.setFillColor(sf::Color::White);

    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(60, 150);
}
int GameView::promptForBoardSize2(int min, int max) {
    return promptForInt("Enter the size of the board (" + std::to_string(min) + "-" + std::to_string(max) + ")", min, max);
}

std::string GameView::promptForPlayerName2() {
    return promptForString("Enter your name: ");
}

char GameView::promptForPlayerSymbol2() {
    std::string symbol = promptForString("Choose your symbol (X/O): ");
    if(symbol.length() == 2){
        symbol = symbol[1];
    }
    while (symbol != "X" && symbol != "O" && symbol != "x" && symbol != "o" && window.isOpen()) {
        symbol = promptForString("Invalid symbol. Please enter 'X' or 'O': ");
    }
    inputText.setString("");
    return toupper(symbol[0]);
}
bool GameView::askStartFirst2() {
    std::string input = promptForString("Do you want to start first? (Y/N): ");
    while (input != "Y" && input != "y" && input != "N" && input != "n" && window.isOpen()) {
        input = promptForString("Invalid input. Please enter 'Y' for yes or 'N' for no: ");
    }
    return (toupper(input[0]) == 'Y');
}

std::string GameView::promptForString(const std::string& prompt) {
    std::string input;
    text.setString(prompt);
    inputText.setString("");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered) {

                if (event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back();
                } else if (event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != '\n' && event.text.unicode != '\r') {
                    input += static_cast<char>(event.text.unicode);
                }
//                    std::cout<<event.text.unicode<<std::endl;
//                    std::cout<<input<<std::endl;
                inputText.setString(input);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !input.empty()) {
                return input;
            }
        }
        window.clear();
        window.draw(welcomeMessage);
        window.draw(text);
        window.draw(inputBox);
        window.draw(inputText);
        window.display();
    }
    return ""; // Should handle window close better
}

int GameView::promptForInt(const std::string& prompt, int min, int max) {
    int value = 0;
    std::string input;
    do {
        input = promptForString(prompt);
        std::stringstream ss(input);
        ss >> value;
    } while ((value < min || value > max || input.empty()) && window.isOpen());
    return value;
}


int GameView::promptForBoardSize() {
    int size;
    std::cout << "Enter the size of the board (minimum 3, maximum 7): ";
    while (!(std::cin >> size) || size < 3 || size > 7) {
        std::cout << "Invalid input. Please enter a number greater than or equal to 3 and less than or equal 7: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return size;
}


std::string GameView::promptForPlayerName() {
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    return name;
}

char GameView::promptForPlayerSymbol() {
    char symbol;
    std::cout << "Choose your symbol (X/O): ";
    while (!(std::cin >> symbol) || (symbol != 'X' && symbol != 'O' && symbol != 'x' && symbol != 'o')) {
        std::cout << "Invalid symbol. Please enter 'X' or 'O': ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return toupper(symbol);
}

void GameView::getMoveInput(int& x, int& y, char& direction) {
    while (true) {
        if (std::cin >> y >> x >> direction) {
            direction = std::toupper(direction);
            if (std::cin.fail() || x < 0 || y < 0 || !(direction == 'L' || direction == 'R' || direction == 'U' || direction == 'D')) {
                std::cout << "Invalid input. Please use the format 'x y direction' where directions are L, R, U, or D. Try again: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                return; // Valid input
            }
        } else {
            std::cout << "Invalid input. Please enter numeric values for coordinates and a character for direction. Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

bool GameView::askStartFirst() {
    std::cout << "Do you want to start first, if yes, then write Y if no then anything else? (Y/N): ";
    char response;
    std::cin >> response;
    return (toupper(response) == 'Y');
}