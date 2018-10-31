
// Copyright 2018 Corey Selover

#ifndef GAME_H
#define GAME_H

// Standard library
#include <map>
#include <queue>
#include <vector>

// External libraries
#include <SFML/Graphics.hpp>

// Project files
class Console;
class Manager;
class Entity;
class Texture;
class Screen;
class HudObject;

// TODO - Are these really necessary?
enum BootError {
    BOOT_SUCCESS
};

enum RunError {
    RUN_SUCCESS
};

enum ShutdownError {
    SHUTDOWN_SUCCESS
};

enum ManagerType {
    ENTITY_MANAGER,
    SCREEN_MANAGER,
    TEXTURE_MANAGER,
    HUD_MANAGER
};

class Game {

public:

    // Overall architecture

    Game();

    BootError boot();

    RunError run();

    ShutdownError shutdown();

    // Drawing and Screen handling

    void draw(sf::Drawable& drawable);

    void nextScreen();

    void setActiveScreen(std::string);

    void setView(sf::View view);

    // Controls

    void processInput(sf::Event event);

    // Getters and setters

    Entity* entity(std::string name);

    Texture* addTexture(std::string filePath, bool repeated = false);

    Texture* texture(std::string name);

    Screen* screen(std::string name);

    HudObject* hudObject(std::string name);

    sf::Vector2f windowCenter();

    sf::Vector2u windowSize();

    const sf::View& defaultView();

    sf::Vector2i mapCenterAsPixels();

    sf::Vector2i mapCenterAsCoordinates();

    sf::Vector2f worldCoords(int x, int y);

    int mapWidth();

    int mapHeight();

    int tileWidth();

    int tileHeight();

    // Console

    void runCommand(std::string command);

    void assignGameValue(std::string variable, std::string value, bool saveToDisk);

    std::string getGameValue(std::string variable);

    void loadGameValues();

    void saveGameValues();

    // Util

    void printGameValues();

private:
    // Window and related logic

    sf::RenderWindow m_window;

    Console* m_console;

    // Managers

    std::map<ManagerType, Manager*> m_managers;

    std::queue<std::string> m_screenQueue;

    std::string m_currentScreen;

    // Game logic

    bool m_running;

    sf::Clock m_gameClock;

    /* We store game values in this map, accessible by std::string so that they
     * can be easily manipulated through the console.
     */
    std::map<std::string, std::string> m_gameValues;

    std::vector<std::string> m_commands;

};
#endif // GAME_H
