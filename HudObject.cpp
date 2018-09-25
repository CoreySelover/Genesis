
// Copyright 2018 Corey Selover

#include "HudObject.h"

#include "Game.h"
#include "Texture.h"

HudObject::HudObject(Game* game,
                     std::string fileName,
                     sf::IntRect textureRect,
                     int x,
                     int y,
                     bool visibleAtStart = true)
    : ManagedObject(game) {

    m_sprite.setTexture(m_game->addTexture(fileName)->get());
    // TODO - un-hard code this
    m_sprite.setOrigin(sf::Vector2f(0,0));
    m_sprite.setTextureRect(textureRect);
    m_textureRect = textureRect;

    m_position = sf::Vector2f(m_game->windowCenter().x - m_game->windowSize().x / 2 + x,
                              m_game->windowCenter().y - m_game->windowSize().y / 2 + y);
    m_sprite.setPosition(m_position);

    m_visible = visibleAtStart;
}

void HudObject::update() {}

void HudObject::draw() {
    if(m_visible) m_game->draw(m_sprite);
}

sf::Vector2f HudObject::getPosition() {
    return m_position;
}

void HudObject::setPosition(sf::Vector2f pos) {
    m_position = pos;
}

