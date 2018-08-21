
// Copyright 2018 Corey Selover

#include "Splash.h"

Splash::Splash(Game* game, std::string imagePath, float duration = 3.f)
    : Screen(game) {

    loadFile(imagePath);

    m_duration = duration;
}

void Splash::update() {}

void Splash::draw() {}

void Splash::loadFile(std::string imagePath) {

}

Splash::~Splash() {}
