
// Copyright 2018 Corey Selover

#ifndef MAP_H
#define MAP_H

#include "Screen.h"

class Tile;
class Texture;
class Manager;

class Map : public Screen {
public:
    Map(Game* game, bool active = false, int mapSeed = 1);

    void populateStartingMap(int seed);

    void update();

    void draw();

    // Getters and Setters

    Texture* texture(std::string filePath);

    ~Map();

private:
    std::vector<std::vector<Tile*> > m_grid;

    Manager* m_entMan;

    // TODO - this will probably become a Camera class.
    sf::View m_view;
};

#endif // MAP_H
