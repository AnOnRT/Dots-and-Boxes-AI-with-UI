
#include "Player.h"

// Default constructor
Player::Player() : name(""), symbol(' '), score(0) {}

// Parametrized constructor
Player::Player(std::string name, char sym) : name(name), symbol(sym), score(0) {}

// Method to increment the score
void Player::incrementScore() {
    ++score;
}

void Player::decrementScore(){
    --score;
}

int Player::getScore() const {
    return score;
}

char Player::getSymbol() const {
    return symbol;
}

std::string Player::getName() const {
    return name;
}

void Player::setName(const std::string& name1) {
    name = name1;
}

void Player::setSymbol(const char& sym) {
    symbol = sym;
}