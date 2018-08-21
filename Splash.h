
// Copyright 2018 Corey Selover

#ifndef SPLASH_H
#define SPLASH_H

#include "Screen.h"

class Splash : public Screen {
public:
    Splash(Game* game, std::string imagePath, float duration);

    void update();

    void draw();

    ~Splash();

    // Other

    void loadFile(std::string imagePath);

private:
    sf::Sprite m_sprite;

    std::string m_imagePath;

    float m_duration;

};
#endif // SPLASH_H
