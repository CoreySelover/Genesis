
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

    void processInput(sf::Event event);

    void checkTile(sf::Vector2f pixelPosition, int auraRadius);

    void updateTileSprites();

    // Getters and Setters

    Texture* texture(std::string filePath);

    Tile* tile(int x, int y);

    ~Map();

private:
    std::vector<std::vector<Tile*> > m_grid;

    Manager* m_entMan;
};

#endif // MAP_H
