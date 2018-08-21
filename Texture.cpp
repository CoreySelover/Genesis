
// Copyright 2018 Corey Selover

#include "Texture.h"

Texture::Texture(Game* game, std::string filePath)
    : ManagedObject(game) {

    m_texture.loadFromFile(filePath);
}

sf::Texture& Texture::get() {
    return m_texture;
}
