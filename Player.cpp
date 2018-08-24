
// Copyright 2018 Corey Selover

#include "Player.h"

#include "Game.h"
#include "Texture.h"

Player::Player(Game* game, int x, int y, bool canMove)
    : Entity(game, x, y, canMove){

    m_sprite.setTexture(m_game->addTexture("resources/textures/TEXTURE_PLAYER.png")->get());
    m_sprite.setOrigin(sf::Vector2f(0,0));
    m_sprite.setPosition(x, y);
}

void Player::update() {
}

void Player::draw() {
    m_game->draw(m_sprite);
}
