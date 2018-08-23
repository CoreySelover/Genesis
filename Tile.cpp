
// Copyright 2018 Corey Selover

#include "Tile.h"

#include "Constants.h"
#include "Map.h"
#include "Texture.h"

Tile::Tile(Map* map, int x, int y, TileType type)
    : m_map(map),
    m_x(x),
    m_y(y),
    m_type(type) {

    setSpriteTexture();

    m_sprite.setOrigin(sf::Vector2f(0,0));
    m_sprite.setPosition(m_x * Constants::TILE_WIDTH, m_y * Constants::TILE_HEIGHT);
}

void Tile::update() {}

sf::Sprite& Tile::sprite() {
    return m_sprite;
}

void Tile::setSpriteTexture() {
    // TODO - can't we do this in one line by having an enum for all textures? Is that nuts?
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
}

void Tile::changeType(TileType newType) {
    m_type = newType;
    setSpriteTexture();
}
