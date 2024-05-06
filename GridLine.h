//
// Created by Artur Papyan on 23.04.2024.
//

#ifndef DOTSANDBOXES_GRIDLINE_H
#define DOTSANDBOXES_GRIDLINE_H
struct GridPosition {
    int x, y;
};
struct Line {
    GridPosition start;
    GridPosition end;
};
#endif //DOTSANDBOXES_GRIDLINE_H
