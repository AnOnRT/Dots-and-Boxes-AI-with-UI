#ifndef DOTSANDBOXES_BOX_H
#define DOTSANDBOXES_BOX_H

struct Edge {
    bool isDrawn;
    Edge() : isDrawn(false) {}
};

struct Box {
    Edge left, top, right, bottom;
    char owner;
    Box();
    bool isCompleted() const;
    char getOwner() const;
};

#endif //DOTSANDBOXES_BOX_H
