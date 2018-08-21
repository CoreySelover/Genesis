
// Copyright 2018 Corey Selover

#ifndef GAME_H
#define GAME_H

// Standard library
#include <map>

// External libraries
#include <SFML/Graphics.hpp>

// Project files
class Manager;

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
    ENTITY_MANAGER
};

class Game {

public:
    Game();

    BootError boot();

    RunError run();

    ShutdownError shutdown();

private:

    // Window and related logic
    sf::RenderWindow m_window;

    bool m_running;

    // Game logic
    std::map<ManagerType, Manager*> m_managers;
};
#endif // GAME_H
