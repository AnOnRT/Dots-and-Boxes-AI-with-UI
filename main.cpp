// main.cpp
#include "GameController.h"
#include "GameView.h"
#include <iostream>
#include <SFML/Graphics.hpp>


int main() {

    GameView view;
    GameController gameController(view);
    gameController.playGame();
    return 0;

}


