
// Copyright 2018 Corey Selover

#ifndef GAME_H
#define GAME_H

// Standard library
#include <map>
#include <queue>

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

    // Getters and setters

    Entity* entity(std::string name);

    Texture* addTexture(std::string filePath);

    Texture* texture(std::string name);

    Screen* screen(std::string name);

    sf::Vector2f windowCenter();

    const sf::View& defaultView();

private:
    // Window and related logic

    sf::RenderWindow m_window;

    sf::View m_view;

    bool m_running;

    // Managers

    std::map<ManagerType, Manager*> m_managers;

    std::queue<std::string> m_screenQueue;

};
#endif // GAME_H
