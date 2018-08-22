
// Copyright 2018 Corey Selover

#include "Splash.h"

#include "Game.h"
#include "Texture.h"

Splash::Splash(Game* game, std::string imagePath, float duration = 3.f)
    : Screen(game) {

    loadFile(imagePath);

    m_duration = duration;
}

void Splash::update() {}

void Splash::draw() {

}

void Splash::loadFile(std::string imagePath) {
    m_sprite.setTexture(m_game->addTexture(imagePath)->get());
}

Splash::~Splash() {}
