
// Copyright 2018 Corey Selover

#ifndef TILE_H
#define TILE_H

// External libraries
#include <SFML/Graphics.hpp>

class Map;

enum TileType {
    TILE_GRASS,
    TILE_FOREST,
    TILE_WATER,
    TILE_ROCK,
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

    void setStatsAccordingToType();

    void updateSprite();

    void changeType(TileType newType);

    void decreaseHealth(int damage);

    TileType getType();

    int getSpeed();

    sf::Vector2f coordinatesAsPixels();

    sf::Vector2f centerCoordsAsPixels();

private:
    Map* m_map;

    int m_x;
    int m_y;

    TileType m_type;
    int m_currentHealth;
    int m_maxHealth;
    int m_movementSpeed;

    sf::Sprite m_sprite;

    // TODO - rename these
    bool m_northIsGrass;
    bool m_southIsGrass;
    bool m_eastIsGrass;
    bool m_westIsGrass;
};

#endif // TILE_H
