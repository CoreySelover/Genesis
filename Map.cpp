
// Copyright 2018 Corey Selover3

#include "Map.h"

#include "Game.h"
#include "Tile.h"
#include "Player.h"

Map::Map(Game* game, bool active, int mapSeed)
    : Screen(game, active) {

    m_view = m_game->defaultView();

    // Load all tile textures ahead of time
    m_game->addTexture("resources/textures/TEXTURE_GRASS.png");
    m_game->addTexture("resources/textures/TEXTURE_WATER.png");
    m_game->addTexture("resources/textures/TEXTURE_BLANK.png");

    // Create and populate Entities
    m_entMan = new Manager();

    // Create and populate grid
    populateStartingMap(mapSeed);


}

void Map::populateStartingMap(int seed) {

    // Create blank tiles
    for(int x = 0; x < m_game->mapWidth(); x++) {
        m_grid.push_back(std::vector<Tile*>());
        for(int y = 0; y < m_game->mapHeight(); y++) {
            m_grid[x].push_back(new Tile(this, x, y));
        }
    }

    sf::Vector2f playerPos;

    /* Default map.
     *
     * If this line fails, it means Tiles weren't populated correctly above.
     * Check data.ini for weirdness.
     */
    m_grid[0][0]->changeType(TILE_GRASS);
    if(seed == 1) {
        sf::Vector2i centerOfMap = m_game->mapCenterAsCoordinates();
        m_grid[centerOfMap.x][centerOfMap.y]->changeType(TILE_GRASS);
        m_grid[centerOfMap.x - 1][centerOfMap.y]->changeType(TILE_GRASS);
        m_grid[centerOfMap.x + 1][centerOfMap.y]->changeType(TILE_GRASS);
        m_grid[centerOfMap.x][centerOfMap.y - 1]->changeType(TILE_GRASS);
        m_grid[centerOfMap.x][centerOfMap.y + 1]->changeType(TILE_GRASS);
        m_view.setCenter(m_grid[centerOfMap.x][centerOfMap.y]->centerCoordsAsPixels());
        playerPos = sf::Vector2f(centerOfMap.x * m_game->tileWidth(), centerOfMap.y * m_game->tileHeight());
    }
    // Mutate the seed
    else {
    }

    // Create Player and set starting position.
    m_entMan->add("Player", new Player(m_game, playerPos.x, playerPos.y, true));

}

void Map::update() {
    m_entMan->update();
}

void Map::draw() {
    m_game->setView(m_view);

    // Draw from "back" (top) of the map "forward" (down)
    for(int y = 0; y < m_game->mapHeight(); y++) {
        for(int x = 0; x < m_game->mapWidth(); x++) {
            m_game->draw(m_grid[x][y]->sprite());
        }
    }

    // Draw entities
    m_entMan->draw();
}

Map::~Map() {
    // Delete entities
    m_entMan->shutdown();

    // Delete tiles
    for(int y = 0; y < m_game->mapHeight(); y++) {
        for(int x = 0; x < m_game->mapWidth(); x++) {
            delete m_grid[x][y];
        }
    }
    m_grid.clear();
}

Texture* Map::texture(std::string filePath) {
    return m_game->texture(filePath);
}
