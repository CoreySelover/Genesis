
// Copyright 2018 Corey Selover

#include "Player.h"

#include "Game.h"
#include "Texture.h"
#include "Tool.h"

Player::Player(Game* game, int x, int y, bool canMove)
    : Entity(game, x, y, canMove){

    m_sprite.setTexture(m_game->addTexture("resources/textures/TEXTURE_PLAYER.png")->get());
    m_sprite.setOrigin(sf::Vector2f(0,0));
    m_sprite.setPosition(x, y);

    m_maxSpeed = 3;
    m_targetLocation = sf::Vector2f(x, y);
}

void Player::update() {

    if(abs(Tool::distance(m_targetLocation, m_position)) > 0.5) {
        float xDiff = m_position.x - m_targetLocation.x;
        float deltaX = m_maxSpeed * xDiff / Tool::distance(m_position, m_targetLocation);
        float yDiff = m_position.y - m_targetLocation.y;
        float deltaY = m_maxSpeed * yDiff / Tool::distance(m_position, m_targetLocation);

        m_position -= sf::Vector2f(deltaX, deltaY);
    }

    m_sprite.setPosition(m_position);
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
