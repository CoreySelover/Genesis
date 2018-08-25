
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
    m_targetLocation = sf::Vector2i(x, y);
}

void Player::update() {
    //std::cout << m_xPosition << ", " << m_yPosition << std::endl;

    // X
    if(m_xPosition < m_targetLocation.x) {
        m_xPosition += m_maxSpeed;
    }
    else if (m_xPosition > m_targetLocation.x) {
        m_xPosition -= m_maxSpeed;
    }

    // Y
    if(m_yPosition < m_targetLocation.y) {
        m_yPosition += m_maxSpeed;
    }
    else if (m_yPosition > m_targetLocation.y) {
        m_yPosition -= m_maxSpeed;
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

void Player::moveTo(sf::Vector2i coords) {
    m_targetLocation = coords;
}
