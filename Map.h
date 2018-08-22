
// Copyright 2018 Corey Selover

#ifndef MAP_H
#define MAP_H

#include "Screen.h"

class Tile;
class Texture;

class Map : public Screen {
public:
    Map(Game* game, bool active = false);

    void populateStartingMap();

    void update();

    void draw();

    Texture* texture(std::string filePath);

    ~Map();

private:
    std::vector<std::vector<Tile*> > m_grid;
};

#endif // MAP_H
