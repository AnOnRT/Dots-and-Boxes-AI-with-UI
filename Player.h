
#ifndef DOTSANDBOXES_PLAYER_H
#define DOTSANDBOXES_PLAYER_H

#include <string>

class Player {
    std::string name;
    char symbol;
    int score;
public:
    Player();
    explicit Player(std::string name, char sym);

    void incrementScore();
    void decrementScore();
    char getSymbol() const;
    int getScore() const;
    std::string getName() const;
    void setName(const std::string& name);
    void setSymbol(const char& sym);
};

#endif //DOTSANDBOXES_PLAYER_H
