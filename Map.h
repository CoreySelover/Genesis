
// Copyright 2018 Corey Selover

#ifndef MAP_H
#define MAP_H

#include "Screen.h"

class Tile;

class Map : public Screen {
public:
    Map(Game* game, bool active = false);

    void update();

    void draw();

    ~Map();

private:
    const int MAX_HEIGHT;
    const int MAX_WIDTH;

    std::vector<std::vector<Tile*> > m_grid;
};

#endif // MAP_H
