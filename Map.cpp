
// Copyright 2018 Corey Selover

#include "Map.h"

#include "Game.h"
#include "Tile.h"
#include "Tool.h"
#include "Player.h"
#include "Monster.h"

Map::Map(Game* game, bool active, int mapSeed)
    : Screen(game, active) {

    m_view = m_game->defaultView();

    // Load all tile textures ahead of time
    m_game->addTexture("resources/textures/TEXTURE_GRASS.png");
    m_game->addTexture("resources/textures/TEXTURE_WATER.png");
    m_game->addTexture("resources/textures/TEXTURE_BLANK.png");
    m_game->addTexture("resources/textures/TEXTURE_ROCK.png");

    // Create and populate Entities
    m_entMan = new Manager();

    // Create and populate grid
    populateStartingMap(mapSeed);

    m_previousCheckedTile = sf::Vector2i();
    m_previousCheckedTileType = TILE_BLANK;

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
    if(seed == 1) {
        sf::Vector2i centerOfMap = m_game->mapCenterAsCoordinates();
        m_grid[centerOfMap.x][centerOfMap.y]->changeType(TILE_GRASS);
        m_grid[centerOfMap.x - 1][centerOfMap.y]->changeType(TILE_GRASS);
        m_grid[centerOfMap.x + 1][centerOfMap.y]->changeType(TILE_GRASS);
        m_grid[centerOfMap.x][centerOfMap.y - 1]->changeType(TILE_GRASS);
        m_grid[centerOfMap.x][centerOfMap.y + 1]->changeType(TILE_GRASS);
        m_view.setCenter(m_grid[centerOfMap.x][centerOfMap.y]->centerCoordsAsPixels());
        playerPos = Tool::tileToPixels(centerOfMap);
    }
    // Mutate the seed
    else {
    }

    updateTileSprites();

    // Create Player and set starting position.
    m_entMan->add("Player", new Player(m_game, playerPos.x, playerPos.y, true));

}

void Map::update() {
    m_entMan->update();

    m_view.setCenter(static_cast<Player*>(m_entMan->get("Player"))->getPixelPosition());

    if(m_monsterTimer.getElapsedTime().asSeconds() > 5) {
        createMonster();
        m_monsterTimer.restart();
    }
}

void Map::draw() {

    // Draw from "back" (top) of the map "forward" (down)
    for(int y = 0; y < m_game->mapHeight(); y++) {
        for(int x = 0; x < m_game->mapWidth(); x++) {
            m_game->draw(m_grid[x][y]->sprite());
        }
    }

    // Draw entities
    m_entMan->draw();
}

void Map::processInput(sf::Event event) {
    // User clicked on a GUI element
    if(event.type == sf::Event::MouseButtonPressed) {
        // TODO - implement GUI manager (subclass?)
        //if(m_guiMan->processInput(event)) {
        //    return;
        //}
    }

    static_cast<Player*>(m_entMan->get("Player"))->processInput(event);

    if(event.type == sf::Event::MouseButtonReleased) {
        updateTileSprites();
    }
}

void Map::createMonster(int x, int y, int monsterType) {

    // Create monster at random location on map
    if(x == -1 && y == -1) {
        // No valid tiles.
        if(m_validMonsterTiles.size() == 0) return;
        sf::Vector2f monsterPos = randomMonsterPos();
        std::string terrorName = m_entMan->nextName("terror");
        m_entMan->add(terrorName, new Terror(terrorName, m_game, monsterPos.x, monsterPos.y, true));
    }
    // Create monster at specified location
    else {
        std::string terrorName = m_entMan->nextName("terror");
        m_entMan->add(terrorName, new Terror(terrorName, m_game, x, y, true));
    }
}

sf::Vector2f Map::randomMonsterPos() {
    int whichTile = rand() % (m_validMonsterTiles.size() - 1);
    return Tool::tileToPixels(sf::Vector2i(m_validMonsterTiles[whichTile].first, m_validMonsterTiles[whichTile].second));
}

void Map::removeFromValidMonsterTiles(int x, int y) {
    m_validMonsterTiles.erase(std::remove(m_validMonsterTiles.begin(), m_validMonsterTiles.end(), std::pair<int, int>(x, y)), m_validMonsterTiles.end());
}

bool Map::checkTile(sf::Vector2f pixelPosition, int auraRadius, TileType auraType) {
    sf::Vector2i tileCoords = Tool::pixelsToTile(pixelPosition, m_game->tileHeight(), m_game->tileWidth());
    bool shouldCostMana = true;

    // Tile is out of bounds and we should not change anything
    if(tileCoords.x >= m_game->mapWidth() || tileCoords.x < 0 || tileCoords.y >= m_game->mapHeight() || tileCoords.y < 0) {
        shouldCostMana = false;
    }
    else if(tileCoords == m_previousCheckedTile && auraType == m_previousCheckedTileType) {
        shouldCostMana = false;
    }

    // We either have a different tile location or a different tile type, so we need to do the work.
    if (shouldCostMana) {

        // Handle auraRadius of 1 differently because the math doesn't quite work out.
        if (auraRadius == 1) {
            m_grid[tileCoords.x][tileCoords.y]->changeType(auraType);
            m_grid[std::max(0, tileCoords.x - 1)][tileCoords.y]->changeType(auraType);
            m_grid[std::min(m_game->mapWidth(), tileCoords.x + 1)][tileCoords.y]->changeType(auraType);
            m_grid[tileCoords.x][std::max(0, tileCoords.y - 1)]->changeType(auraType);
            m_grid[tileCoords.x][std::min(m_game->mapHeight(), tileCoords.y + 1)]->changeType(auraType);

            m_validMonsterTiles.push_back(std::pair<int, int>(tileCoords.x, tileCoords.y));
            m_validMonsterTiles.push_back(std::pair<int, int>(std::max(0, tileCoords.x - 1), tileCoords.y));
            m_validMonsterTiles.push_back(std::pair<int, int>(std::min(m_game->mapWidth(), tileCoords.x + 1), tileCoords.y));
            m_validMonsterTiles.push_back(std::pair<int, int>(tileCoords.x, std::max(0, tileCoords.y - 1)));
            m_validMonsterTiles.push_back(std::pair<int, int>(tileCoords.x, std::min(m_game->mapHeight(), tileCoords.y + 1)));
        }
        else {
            int y = 1;
            for(int x = std::max(tileCoords.x - auraRadius, 0); x < std::min(tileCoords.x, m_game->mapWidth()); x++) {
                m_grid[x][tileCoords.y]->changeType(auraType);
                m_validMonsterTiles.push_back(std::pair<int, int>(x, tileCoords.y));
                for(int yy = y; yy > 0; yy--) {
                    m_grid[x][std::min(tileCoords.y + yy, m_game->mapHeight() - 1)]->changeType(auraType);
                    m_grid[x][std::max(tileCoords.y - yy, 0)]->changeType(auraType);
                    m_validMonsterTiles.push_back(std::pair<int, int>(x, std::min(tileCoords.y + yy, m_game->mapHeight() - 1)));
                    m_validMonsterTiles.push_back(std::pair<int, int>(x, std::max(tileCoords.y - yy, 0)));
                }
                y++;
            }
            y = auraRadius;
            for(int x = std::min(tileCoords.x, m_game->mapWidth()); x < std::min(tileCoords.x + auraRadius, m_game->mapWidth()); x++) {
                m_grid[x][tileCoords.y]->changeType(auraType);
                m_validMonsterTiles.push_back(std::pair<int, int>(x, tileCoords.y));
                for(int yy = y; yy > 0; yy--) {
                    m_grid[x][std::min(tileCoords.y + yy, m_game->mapHeight() - 1)]->changeType(auraType);
                    m_grid[x][std::max(tileCoords.y - yy, 0)]->changeType(auraType);
                    m_validMonsterTiles.push_back(std::pair<int, int>(x, std::min(tileCoords.y + yy, m_game->mapHeight() - 1)));
                    m_validMonsterTiles.push_back(std::pair<int, int>(x, std::max(tileCoords.y - yy, 0)));
                }
                y--;
            }
        }
    }

    m_previousCheckedTile = tileCoords;
    m_previousCheckedTileType = auraType;
    return shouldCostMana;
}

void Map::updateTileSprites() {
    for(int x = 0; x < m_game->mapWidth(); x++) {
        for(int y = 0; y < m_game->mapHeight(); y++) {
            if(m_grid[x][y]->getType() != TILE_BLANK) {
                m_grid[x][y]->updateSprite();
            }
        }
    }
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

Tile* Map::tileByGrid(int x, int y) {
    return m_grid[x][y];
}

Tile* Map::tileByPixels(int x, int y) {
    sf::Vector2i tile = Tool::pixelsToTile(sf::Vector2f(x, y), m_game->tileWidth(), m_game->tileHeight());
    return m_grid[tile.x][tile.y];
}
