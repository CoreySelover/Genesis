
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

    m_northIsGrass = false;
    m_southIsGrass = false;
    m_eastIsGrass = false;
    m_westIsGrass = false;
}

Tile::~Tile() { }

void Tile::update() { }

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
    m_sprite.setTextureRect(sf::IntRect(2*m_map->m_game->tileWidth(), 2*m_map->m_game->tileHeight(), m_map->m_game->tileWidth(), m_map->m_game->tileHeight()));
}

void Tile::updateSprite() {
    // North
    if(m_y > 0 && m_map->tile(m_x, m_y - 1)->getType() == TILE_GRASS) {
        m_northIsGrass = true;
    }
    // South
    if(m_y < m_map->m_game->mapHeight() && m_map->tile(m_x, m_y + 1)->getType() == TILE_GRASS) {
        m_southIsGrass = true;
    }
    // West
    if(m_x > 0 && m_map->tile(m_x - 1, m_y)->getType() == TILE_GRASS) {
        m_westIsGrass = true;
    }
    // East
    if(m_x < m_map->m_game->mapWidth() && m_map->tile(m_x + 1, m_y)->getType() == TILE_GRASS) {
        m_eastIsGrass = true;
    }

    if(m_northIsGrass) {

        /* __________Tile layout_______________
         * |           |           |           |
         * |  None     |     S     |     NE    |
         * |___________|___________|___________|
         * |           |           |           |
         * |  N        |     SE    |     All   |
         * |___________|___________|___________|
         * |           |           |           |
         * |  E        |     SW    |           |
         * |___________|___________|___________|
         * |           |           |           |
         * |  W        |     NW    |           |
         * |___________|___________|___________|
         */

        if(m_southIsGrass || (m_eastIsGrass && m_westIsGrass)) {
            // 4 sides
            m_sprite.setTextureRect(sf::IntRect(2*m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight(),
                                                m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight()));
        }
        else if(m_eastIsGrass) {
            // north and east
            m_sprite.setTextureRect(sf::IntRect(2*m_map->m_game->tileWidth(),
                                                0,
                                                m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight()));
        }
        else if (m_westIsGrass) {
            // north and west
            m_sprite.setTextureRect(sf::IntRect(m_map->m_game->tileWidth(),
                                                3*m_map->m_game->tileHeight(),
                                                m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight()));
        }
        else {
            // just north
            m_sprite.setTextureRect(sf::IntRect(0,
                                                m_map->m_game->tileHeight(),
                                                m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight()));
        }
    }
    else if(m_southIsGrass) {
        if(m_eastIsGrass && m_westIsGrass) {
            // 4 sides
            m_sprite.setTextureRect(sf::IntRect(2*m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight(),
                                                m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight()));
        }
        else if(m_eastIsGrass) {
            // south and east
            m_sprite.setTextureRect(sf::IntRect(m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight(),
                                                m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight()));
        }
        else if (m_westIsGrass) {
            // south and west
            m_sprite.setTextureRect(sf::IntRect(m_map->m_game->tileWidth(),
                                                2*m_map->m_game->tileHeight(),
                                                m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight()));
        }
        else {
            // just south
            m_sprite.setTextureRect(sf::IntRect(m_map->m_game->tileWidth(),
                                                0,
                                                m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight()));
        }
    }
    else if(m_eastIsGrass && !m_westIsGrass) {
        // just east
        m_sprite.setTextureRect(sf::IntRect(0,
                                            2*m_map->m_game->tileHeight(),
                                            m_map->m_game->tileWidth(),
                                            m_map->m_game->tileHeight()));

    }
    else if(m_westIsGrass && !m_eastIsGrass) {
        // just west
        m_sprite.setTextureRect(sf::IntRect(0,
                                            3*m_map->m_game->tileHeight(),
                                            m_map->m_game->tileWidth(),
                                            m_map->m_game->tileHeight()));

    }
    else {  // East and West
        // 4 sides
        m_sprite.setTextureRect(sf::IntRect(2*m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight(),
                                                m_map->m_game->tileWidth(),
                                                m_map->m_game->tileHeight()));
    }
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
