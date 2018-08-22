
// Copyright 2018 Corey Selover

#ifndef GAME_H
#define GAME_H

// Standard library
#include <map>

// External libraries
#include <SFML/Graphics.hpp>

// Project files
class Manager;
class Entity;
class Texture;
class Screen;

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
    TEXTURE_MANAGER
};

class Game {

public:
    Game();

    BootError boot();

    RunError run();

    ShutdownError shutdown();

    // Getters and setters

    Entity* entity(std::string name);

    Texture* addTexture(std::string filePath);

    Texture* texture(std::string name);

    Screen* screen(std::string name);

    void draw(sf::Drawable&);

private:
    friend class ManagedObject;

    // Window and related logic

    sf::RenderWindow m_window;

    bool m_running;

    // Managers

    std::map<ManagerType, Manager*> m_managers;

    std::string m_currentScreen;

};
#endif // GAME_H
