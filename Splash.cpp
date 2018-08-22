
// Copyright 2018 Corey Selover

#include "Splash.h"

#include "Game.h"
#include "Texture.h"

Splash::Splash(Game* game, std::string imagePath, sf::Time duration)
    : Screen(game) {

    loadFile(imagePath);

    m_duration = duration;
}

void Splash::update() {
    if(elapsedTime() >= m_duration) {
        m_game->nextScreen();
    }
}

void Splash::draw() {
    m_game->draw(m_sprite);
}

void Splash::loadFile(std::string imagePath) {
    m_sprite.setTexture(m_game->addTexture(imagePath)->get());
    m_sprite.setOrigin(m_game->texture(imagePath)->center());
    m_sprite.setPosition(m_game->windowCenter());
}

Splash::~Splash() {}
