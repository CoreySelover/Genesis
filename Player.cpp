
// Copyright 2018 Corey Selover

#include "Player.h"

#include <math.h>

#include "Game.h"
#include "Map.h"
#include "Texture.h"
#include "Tool.h"
#include "Tile.h"
#include "HudObject.h"

Player::Player(Game* game, int x, int y, bool canMove)
    : Entity(game, x, y, canMove){

    m_sprite.setTexture(m_game->addTexture("resources/textures/TEXTURE_PLAYER.png")->get());
    // TODO - un-hard code this
    m_sprite.setOrigin(sf::Vector2f(32,32));
    m_maxSpeed              = atoi(m_game->getGameValue("player_speed").c_str());
    m_auraRadius            = atoi(m_game->getGameValue("player_aura").c_str());
    m_maxMana               = atoi(m_game->getGameValue("player_mana").c_str());
    m_manaRechargeRate      = atoi(m_game->getGameValue("player_mana_recharge").c_str());
    m_manaCost[TILE_GRASS]  = atoi(m_game->getGameValue("aura_grass_cost").c_str());
    m_manaCost[TILE_FOREST] = atoi(m_game->getGameValue("aura_forest_cost").c_str());
    m_manaCost[TILE_WATER]  = atoi(m_game->getGameValue("aura_water_cost").c_str());
    m_manaCost[TILE_ROCK]   = atoi(m_game->getGameValue("aura_rock_cost").c_str());

    m_currentMana       = m_maxMana;

    setAuraType(TILE_GRASS);

    m_left  = false;
    m_right = false;
    m_up    = false;
    m_down  = false;
    m_mouseDown = false;
}

void Player::update() {

    // Movement
    if(m_left) {
        if(m_up)        { walk(ULEFT); }
        else if(m_down) { walk(DLEFT); }
        else            { walk(LEFT);  }
    }
    else if(m_right) {
        if(m_up)        { walk(URIGHT); }
        else if(m_down) { walk(DRIGHT); }
        else            { walk(RIGHT);  }
    }
    else if(m_up)       { walk(UP);   }
    else if(m_down)     { walk(DOWN); }

    // Display correct Mana aura type.
    static_cast<AuraHudObject*>(m_game->hudObject("grass_aura_hud"))->setActive(false);
    static_cast<AuraHudObject*>(m_game->hudObject("rock_aura_hud"))->setActive(false);
    static_cast<AuraHudObject*>(m_game->hudObject("water_aura_hud"))->setActive(false);

    switch(m_auraType) {
        case TILE_GRASS:
            static_cast<AuraHudObject*>(m_game->hudObject("grass_aura_hud"))->setActive(true);
            break;
        case TILE_ROCK:
            static_cast<AuraHudObject*>(m_game->hudObject("rock_aura_hud"))->setActive(true);
            break;
        case TILE_WATER:
            static_cast<AuraHudObject*>(m_game->hudObject("water_aura_hud"))->setActive(true);
            break;
        default:
            break;
    }

    // Create tiles
    if (m_mouseDown && m_currentMana - m_manaCost[m_auraType] >= 0) {
        if(createAt(m_game->worldCoords(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)))
            m_currentMana -= m_manaCost[m_auraType];
    }

    // Update Mana
    if(!m_mouseDown && m_manaTimer.getElapsedTime().asSeconds() >= 0.2 && m_currentMana < m_maxMana) {
        m_currentMana += std::min(m_manaRechargeRate, m_maxMana - m_currentMana);
        m_manaTimer.restart();
    }

    // Sync sprite
    m_sprite.setPosition(m_position);

}

void Player::draw() {
    m_game->draw(m_sprite);
}

void Player::processInput(sf::Event event) {
    if(event.type == sf::Event::MouseButtonPressed) {
        switch(event.mouseButton.button) {
            case sf::Mouse::Left:
                m_mouseDown = true;
                break;
            default:
                break;
        }
    }
    if(event.type == sf::Event::MouseButtonReleased) {
        switch(event.mouseButton.button) {
            case sf::Mouse::Left:
                m_mouseDown = false;
                break;
            default:
                break;
        }
    }
    if(event.type == sf::Event::KeyPressed) {
        switch(event.key.code) {
        case sf::Keyboard::A:
            m_left = true;
            break;
        case sf::Keyboard::D:
            m_right = true;
            break;
        case sf::Keyboard::W:
            m_up = true;
            break;
        case sf::Keyboard::S:
            m_down = true;
            break;
        case sf::Keyboard::Num1:
            setAuraType(TILE_GRASS);
            break;
        case sf::Keyboard::Num2:
            setAuraType(TILE_ROCK);
            break;
        case sf::Keyboard::Num3:
            setAuraType(TILE_WATER);
            break;
        default:
            break;
        }
    }
    if(event.type == sf::Event::KeyReleased) {
        switch(event.key.code) {
        case sf::Keyboard::A:
            m_left = false;
            break;
        case sf::Keyboard::D:
            m_right = false;
            break;
        case sf::Keyboard::W:
            m_up = false;
            break;
        case sf::Keyboard::S:
            m_down = false;
            break;
        }
    }
}

void Player::walk(Direction direction) {
    switch(direction) {
    case LEFT:
        m_position.x -= m_maxSpeed;
        break;
    case RIGHT:
        m_position.x += m_maxSpeed;
        break;
    case UP:
        m_position.y -= m_maxSpeed;
        break;
    case DOWN:
        m_position.y += m_maxSpeed;
        break;
    case ULEFT:
        m_position.x -= m_maxSpeed / sqrt(2);
        m_position.y -= m_maxSpeed / sqrt(2);
        break;
    case URIGHT:
        m_position.x += m_maxSpeed / sqrt(2);
        m_position.y -= m_maxSpeed / sqrt(2);
        break;
    case DLEFT:
        m_position.x -= m_maxSpeed / sqrt(2);
        m_position.y += m_maxSpeed / sqrt(2);
        break;
    case DRIGHT:
        m_position.x += m_maxSpeed / sqrt(2);
        m_position.y += m_maxSpeed / sqrt(2);
        break;
    }
}

bool Player::createAt(sf::Vector2f coords) {
    return static_cast<Map*>(m_game->screen("map"))->checkTile(coords, m_auraRadius, (TileType)m_auraType);
}

int Player::maxMana() const {
    return m_maxMana;
}

int Player::currentMana() const {
    return m_currentMana;
}

int Player::auraRadius() const {
    return m_auraRadius;
}

void Player::setAuraType(int auraType) {
    m_auraType = auraType;
}


