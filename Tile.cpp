
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
    setStatsAccordingToType();

    m_northIsGrass = false;
    m_southIsGrass = false;
    m_eastIsGrass = false;
    m_westIsGrass = false;
}

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
        case TILE_ROCK:
            m_sprite.setTexture(m_map->texture("resources/textures/TEXTURE_ROCK.png")->get());
            break;
        default:
            m_sprite.setTexture(m_map->texture("resources/textures/TEXTURE_BLANK.png")->get());
            break;
    }

    m_sprite.setOrigin(sf::Vector2f(0,0));
    m_sprite.setPosition(m_x * m_map->m_game->tileWidth(), m_y * m_map->m_game->tileHeight());
    m_sprite.setTextureRect(sf::IntRect(2*m_map->m_game->tileWidth(), 2*m_map->m_game->tileHeight(), m_map->m_game->tileWidth(), m_map->m_game->tileHeight()));
}

void Tile::setStatsAccordingToType() {
    switch(m_type) {
        case TILE_BLANK:
            m_maxHealth     = -1;
            m_movementSpeed = 0;
            break;
        case TILE_GRASS:
            // TODO - shouldn't it be game's responsibility to give us this value in a readable way
            // so we don't have to cast it?
            m_maxHealth     = atoi(m_map->m_game->getGameValue("tile_grass_health").c_str());
            m_movementSpeed = atoi(m_map->m_game->getGameValue("tile_grass_speed").c_str());
            break;
        case TILE_WATER:
            m_maxHealth     = atoi(m_map->m_game->getGameValue("tile_water_health").c_str());
            m_movementSpeed = atoi(m_map->m_game->getGameValue("tile_water_speed").c_str());
            break;
        case TILE_ROCK:
            m_maxHealth     = atoi(m_map->m_game->getGameValue("tile_rock_health").c_str());;
            m_movementSpeed = atoi(m_map->m_game->getGameValue("tile_rock_speed").c_str());
            break;
        default:
            m_maxHealth     = -1;
            m_movementSpeed = 0;
            break;
    }

    m_currentHealth = m_maxHealth;
}

void Tile::updateSprite() {
    // North
    if(m_y > 0 && m_map->tileByGrid(m_x, m_y - 1)->getType() == m_type) {
        m_northIsGrass = true;
    }
    // South
    if(m_y < m_map->m_game->mapHeight() && m_map->tileByGrid(m_x, m_y + 1)->getType() == m_type) {
        m_southIsGrass = true;
    }
    // West
    if(m_x > 0 && m_map->tileByGrid(m_x - 1, m_y)->getType() == m_type) {
        m_westIsGrass = true;
    }
    // East
    if(m_x < m_map->m_game->mapWidth() && m_map->tileByGrid(m_x + 1, m_y)->getType() == m_type) {
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
    bool sameType = (m_type == newType);

    m_type = newType;
    setSpriteTexture();

    if(!sameType) setStatsAccordingToType();
}

void Tile::decreaseHealth(int damage) {
    m_currentHealth -= damage;

    if (m_currentHealth <= 0) {
        changeType(TileType::TILE_BLANK);
        m_map->removeFromValidMonsterTiles(m_x, m_y);
    }
}

TileType Tile::getType() {
    return m_type;
}

int Tile::getSpeed() {
    return m_movementSpeed;
}

sf::Vector2f Tile::coordinatesAsPixels() {
    return sf::Vector2f(m_x * m_map->m_game->tileWidth(), m_y * m_map->m_game->tileHeight());
}

sf::Vector2f Tile::centerCoordsAsPixels() {
    return sf::Vector2f(m_x * m_map->m_game->tileWidth() + (m_map->m_game->tileWidth() / 2),
                        m_y * m_map->m_game->tileHeight() + (m_map->m_game->tileHeight() / 2));
}

Tile::~Tile() { }
