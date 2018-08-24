
// Copyright 2018 Corey Selover

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Manager.h"

// External libraries
#include <SFML/Graphics.hpp>

class Texture : public ManagedObject {
public:
    Texture(Game* game, std::string filePath, bool repeated = false);

    void update() {}

    void draw() {}

    ~Texture() {}

    // Getters and Setters

    sf::Texture& get();

    sf::Vector2f center();

private:
    sf::Texture m_texture;
};

#endif // TEXTURE_H
