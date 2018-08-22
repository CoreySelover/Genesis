
// Copyright 2018 Corey Selover3

#include "Map.h"

#include "Constants.h"
#include "Game.h"

Map::Map(Game* game, bool active)
    : Screen(game, active) {

    // Load all tile textures ahead of time
    m_game->addTexture("resources/textures/TEXTURE_GRASS.png");
    m_game->addTexture("resources/textures/TEXTURE_WATER.png");
    m_game->addTexture("resources/textures/TEXTURE_BLANK.png");

    populateStartingMap();
}

void Map::populateStartingMap() {
    for(int x = 0; x < Constants::MAP_WIDTH; x++) {
        for(int y = 0; y < Constants::MAP_HEIGHT; y++) {

        }
    }
}

void Map::update() {
}

void Map::draw() {
}

Map::~Map() {
}

Texture* Map::texture(std::string filePath) {
    return m_game->texture(filePath);
}
