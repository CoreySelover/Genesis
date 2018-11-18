
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

    // Gameplay

    void processInput(sf::Event event);

    void createMonster(int x = -1, int y = -1, int monsterType = 1);

    sf::Vector2f randomMonsterPos();

    // Returns 'true' if the tile is at a different location or a different type.
    bool checkTile(sf::Vector2f pixelPosition, int auraRadius, TileType auraType);

    void updateTileSprites();

    // Getters and Setters

    Texture* texture(std::string filePath);

    Tile* tileByGrid(int x, int y);

    Tile* tileByPixels(int x, int y);

    ~Map();

private:
    std::vector<std::vector<Tile*> >    m_grid;
    std::vector<std::pair<int, int> >     m_validMonsterTiles;

    sf::Vector2i m_previousCheckedTile;
    TileType m_previousCheckedTileType;

    sf::Clock m_monsterTimer;

};

#endif // MAP_H
