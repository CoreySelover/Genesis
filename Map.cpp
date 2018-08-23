
// Copyright 2018 Corey Selover3

#include "Map.h"

#include "Constants.h"
#include "Game.h"
#include "Tile.h"

Map::Map(Game* game, bool active, int mapSeed)
    : Screen(game, active) {

    // Load all tile textures ahead of time
    m_game->addTexture("resources/textures/TEXTURE_GRASS.png");
    m_game->addTexture("resources/textures/TEXTURE_WATER.png");
    m_game->addTexture("resources/textures/TEXTURE_BLANK.png");

    m_view = m_game->defaultView();

    populateStartingMap(mapSeed);
}

void Map::populateStartingMap(int seed) {
    // Create blank tiles
    for(int x = 0; x < Constants::MAP_WIDTH; x++) {
        m_grid.push_back(std::vector<Tile*>());
        for(int y = 0; y < Constants::MAP_HEIGHT; y++) {
            m_grid[x].push_back(new Tile(this, x, y));
        }
    }

    // Default map.
    m_grid[0][0]->changeType(TILE_GRASS);
    if(seed == 1) {
        sf::Vector2i center = Constants::mapCenterAsCoordinates();
        m_grid[center.x][center.y]->changeType(TILE_GRASS);
        m_grid[center.x - 1][center.y]->changeType(TILE_GRASS);
        m_grid[center.x + 1][center.y]->changeType(TILE_GRASS);
        m_grid[center.x][center.y - 1]->changeType(TILE_GRASS);
        m_grid[center.x][center.y + 1]->changeType(TILE_GRASS);
        m_view.setCenter(m_grid[center.x][center.y]->coordinatesAsPixels());
    }
    // Mutate the seed
    else {

    }



}

void Map::update() {
}

void Map::draw() {
    m_game->setView(m_view);

    // Draw from "back" (top) of the map "forward" (down)
    for(int y = 0; y < Constants::MAP_HEIGHT; y++) {
        for(int x = 0; x < Constants::MAP_WIDTH; x++) {
            m_game->draw(m_grid[x][y]->sprite());
        }
    }
}

Map::~Map() {
}

Texture* Map::texture(std::string filePath) {
    return m_game->texture(filePath);
}
