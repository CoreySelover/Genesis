
// Copyright 2018 Corey Selover

#ifndef MAP_H
#define MAP_H

#include "Screen.h"
#include "Tile.h"

class Texture;
class Manager;

class Map : public Screen {
public:
    Map(Game* game, bool active = false, int mapSeed = 1);

    void populateStartingMap(int seed);

    void update();

    void draw();

    void processInput(sf::Event event);

    void checkTile(sf::Vector2f pixelPosition, int auraRadius, TileType auraType);

    void updateTileSprites();

    // Getters and Setters

    Texture* texture(std::string filePath);

    Tile* tile(int x, int y);

    ~Map();

private:
    std::vector<std::vector<Tile*> > m_grid;

};

#endif // MAP_H
