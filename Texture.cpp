
// Copyright 2018 Corey Selover

#include "Texture.h"

Texture::Texture(Game* game, std::string filePath, bool repeated)
    : ManagedObject(game) {

    m_texture.loadFromFile(filePath);
    m_texture.setRepeated(repeated);
}

sf::Texture& Texture::get() {
    return m_texture;
}

sf::Vector2f Texture::center() {
    return sf::Vector2f(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}
