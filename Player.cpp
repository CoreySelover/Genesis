
// Copyright 2018 Corey Selover

#include "Player.h"

#include "Game.h"
#include "Texture.h"

Player::Player(Game* game, int x, int y, bool canMove)
    : Entity(game, x, y, canMove){

    m_sprite.setTexture(m_game->addTexture("resources/textures/TEXTURE_PLAYER.png")->get());
    m_sprite.setOrigin(sf::Vector2f(0,0));
    m_sprite.setPosition(x, y);

    m_maxSpeed = 3;
    m_targetLocation = sf::Vector2f(x, y);
}

void Player::update() {

    float remainingX = std::min(m_maxSpeed, abs(m_xPosition - m_targetLocation.x));
    float remainingY = std::min(m_maxSpeed, abs(m_yPosition - m_targetLocation.y));

    // X
    if(m_xPosition < m_targetLocation.x) {
        m_xPosition += remainingX;
    }
    else if (m_xPosition > m_targetLocation.x) {
        m_xPosition -= remainingX;
    }

    // Y
    if(m_yPosition < m_targetLocation.y) {
        m_yPosition += remainingY;
    }
    else if (m_yPosition > m_targetLocation.y) {
        m_yPosition -= remainingY;
    }

    m_sprite.setPosition(sf::Vector2f(m_xPosition, m_yPosition));
}

void Player::draw() {
    m_game->draw(m_sprite);
}

void Player::processInput(sf::Event event) {
    if(event.type == sf::Event::MouseButtonPressed) {
        switch(event.mouseButton.button) {
            case sf::Mouse::Left:
                moveTo(m_game->worldCoords(event.mouseButton.x, event.mouseButton.y));
                break;
            default:
                break;
        }
    }
}

void Player::moveTo(sf::Vector2f coords) {
    m_targetLocation = coords;
}
