
// Copyright 2018 Corey Selover

#include "Tile.h"

#include "Game.h"
#include "Map.h"
#include "Texture.h"

Tile::Tile(Map* map, int x, int y, TileType type)
    : m_map(map),
    m_x(x),
    m_y(y),
    m_type(type) {

    setSpriteTexture();
}

Tile::~Tile() { }

void Tile::update() {}

sf::Sprite& Tile::sprite() {
    return m_sprite;
}

void Tile::setSpriteTexture() {
    switch(m_type) {
        case TILE_BLANK:
            m_sprite.setTexture(m_map->texture("resources/textures/TEXTURE_BLANK.png")->get());
            break;
        case TILE_GRASS:
            m_sprite.setTexture(m_map->texture("resources/textures/TEXTURE_GRASS.png")->get());
            break;
        case TILE_WATER:
            m_sprite.setTexture(m_map->texture("resources/textures/TEXTURE_WATER.png")->get());
            break;
        default:
            m_sprite.setTexture(m_map->texture("resources/textures/TEXTURE_BLANK.png")->get());
            break;
    }

    m_sprite.setOrigin(sf::Vector2f(0,0));
    m_sprite.setPosition(m_x * m_map->m_game->tileWidth(), m_y * m_map->m_game->tileHeight());
    m_sprite.setTextureRect(sf::IntRect(0, 0, m_map->m_game->tileWidth(), m_map->m_game->tileHeight()));
}

void Tile::changeType(TileType newType) {
    m_type = newType;
    setSpriteTexture();
}

TileType Tile::getType() {
    return m_type;
}

sf::Vector2f Tile::coordinatesAsPixels() {
    return sf::Vector2f(m_x * m_map->m_game->tileWidth(), m_y * m_map->m_game->tileHeight());
}

sf::Vector2f Tile::centerCoordsAsPixels() {
    return sf::Vector2f(m_x * m_map->m_game->tileWidth() + (m_map->m_game->tileWidth() / 2),
                        m_y * m_map->m_game->tileHeight() + (m_map->m_game->tileHeight() / 2));
}
