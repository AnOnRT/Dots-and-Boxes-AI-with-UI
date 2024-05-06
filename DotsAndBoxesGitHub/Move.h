#ifndef DOTSANDBOXES_MOVE_H
#define DOTSANDBOXES_MOVE_H

struct Move {
    int x, y;
    char dir;
    Move() : x(0), y(0), dir(' ') {}

    Move(int initX, int initY, char initDir)
            : x(initX), y(initY), dir(initDir) {
    }
};

#endif //DOTSANDBOXES_MOVE_H
