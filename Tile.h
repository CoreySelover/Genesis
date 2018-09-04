
// Copyright 2018 Corey Selover

#ifndef TILE_H
#define TILE_H

// External libraries
#include <SFML/Graphics.hpp>

class Map;

enum TileType {
    TILE_GRASS,
    TILE_WATER,
    TILE_BLANK
};

// TODO - Is this a ManagedObject?
class Tile {
public:
    Tile(Map* map, int x, int y, TileType type = TILE_BLANK);

    void update();

    ~Tile();

    // Getters and Setters

    sf::Sprite& sprite();

    void setSpriteTexture();

    void changeType(TileType newType);

    TileType getType();

    sf::Vector2f coordinatesAsPixels();

    sf::Vector2f centerCoordsAsPixels();

private:
    Map* m_map;

    int m_x;

    int m_y;

    TileType m_type;

    sf::Sprite m_sprite;
};

#endif // TILE_H
