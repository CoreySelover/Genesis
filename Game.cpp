
// Copyright 2018 Corey Selover

#include "Game.h"

// External libs
#include <fstream>

// Project files
#include "Console.h"
#include "Manager.h"
#include "Entity.h"
#include "Splash.h"
#include "Map.h"
#include "Texture.h"

Game::Game() {}

BootError Game::boot() {

    loadGameValues();

    // Window
    //m_window.create(sf::VideoMode::getFullscreenModes()[0], "Genesis", sf::Style::Fullscreen);
    m_window.create(sf::VideoMode(800,600), "Genesis");

    // Set up managers
    m_managers[TEXTURE_MANAGER] = new Manager();
    m_managers[SCREEN_MANAGER] = new Manager();

    // Console
    m_console = new Console(this);

    // TODO - turn these back on for release.
    //m_managers[SCREEN_MANAGER]->add("happy_rock", new Splash(this, "resources/textures/splash.png", sf::seconds(3.0f)));
    //m_managers[SCREEN_MANAGER]->add("disclaimer", new Splash(this, "resources/textures/splash2.png", sf::seconds(3.0f)));
    m_managers[SCREEN_MANAGER]->add("map", new Map(this));
    //m_screenQueue.push("happy_rock");
    //m_screenQueue.push("disclaimer");
    m_screenQueue.push("map");

    m_running = true;

    return BOOT_SUCCESS;
}

void Game::loadGameValues() {
    std::ifstream input( "data.ini" );
    for( std::string line; getline( input, line ); )
    {
        std::string first = line.substr(0, line.find("="));
        std::string second = line.substr(line.find("=") + 1);

        /* The above code will set first and second to the same value if
         * the line contains no = sign.  In other words, if the line is
         * something like [Map], we don't want to parse it and we can
         * ignore it.
         */
        if(first.compare(second) != 0) {
            m_gameValues[first] = second;
        }
    }
}

RunError Game::run() {

    while(m_running) {

        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                shutdown();
            }
            if (event.type == sf::Event::TextEntered && m_console->active()) {
                m_console->handle(event);
            }
            else if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Tilde) {
                    m_console->toggle();
                }
                else if(!m_console->active()) {
                    switch(event.key.code) {
                        default:
                            break;
                    }
                }
            }
        }

        // No more screens to display.  Time to quit.
        if(m_screenQueue.empty()) {
            shutdown();
        }
        if(!m_running) return RUN_SUCCESS;

        // Update managers as appropriate.
        std::string currentScreen = m_screenQueue.front();
        m_managers[SCREEN_MANAGER]->get(currentScreen)->update();
        m_console->update();

        // Draw game objects, screens, etc.
        m_window.clear();
        m_managers[SCREEN_MANAGER]->get(currentScreen)->draw();

        // Draw console
        m_window.setView(m_window.getDefaultView());
        m_console->draw();
        m_window.display();
    }

    return RUN_SUCCESS;
}

ShutdownError Game::shutdown() {

    m_running = false;

    delete m_console;

    // Shutdown managers
    std::map<ManagerType, Manager*>::iterator itr;
    for(itr = m_managers.begin(); itr != m_managers.end(); itr++) {
        itr->second->shutdown();
    }

    // Delete managers
    for(itr = m_managers.begin(); itr != m_managers.end(); itr++) {
        delete itr->second;
    }
    m_managers.clear();

    m_window.close();

    return SHUTDOWN_SUCCESS;
}

///////////////////////////////////
//      Drawing and Screen       //
///////////////////////////////////

void Game::draw(sf::Drawable& drawable) {
    m_window.draw(drawable);
}

void Game::nextScreen() {
    if(!m_screenQueue.empty()) {
        m_screenQueue.pop();
    }
    if(!m_screenQueue.empty()) {
        static_cast<Screen*>(m_managers[SCREEN_MANAGER]->get(m_screenQueue.front()))->restartClock();
    }
}

///////////////////////////////////
//      Getters and Setters      //
///////////////////////////////////

Entity* Game::entity(std::string name) {
    return static_cast<Entity*>(m_managers[ENTITY_MANAGER]->get(name));
}

Texture* Game::texture(std::string name) {
    return static_cast<Texture*>(m_managers[TEXTURE_MANAGER]->get(name));
}

Texture* Game::addTexture(std::string filePath, bool repeated) {
    return static_cast<Texture*>(m_managers[TEXTURE_MANAGER]->add(filePath, new Texture(this, filePath, repeated)));
}

Screen* Game::screen(std::string name) {
    return static_cast<Screen*>(m_managers[SCREEN_MANAGER]->get(name));
}

void Game::setView(sf::View view) { m_window.setView(view); }

sf::Vector2f Game::windowCenter() { return sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2); }

sf::Vector2u Game::windowSize() { return m_window.getSize(); }

const sf::View& Game::defaultView() { return m_window.getDefaultView(); }

sf::Vector2i Game::mapCenterAsPixels() { return sf::Vector2i(mapWidth() * tileWidth() / 2, mapHeight() * tileHeight() / 2); }

sf::Vector2i Game::mapCenterAsCoordinates() { return sf::Vector2i(mapWidth() / 2, mapHeight() / 2); }

int Game::mapWidth() { return std::atoi(m_gameValues["map_width"].c_str()); }

int Game::mapHeight() { return std::atoi(m_gameValues["map_height"].c_str()); }

int Game::tileWidth() { return std::atoi(m_gameValues["tile_width"].c_str()); }

int Game::tileHeight() { return std::atoi(m_gameValues["tile_height"].c_str()); }

///////////////////////////////////
//              Util             //
///////////////////////////////////

void Game::printGameValues() {
    std::map<std::string, std::string>::iterator itr;
    for (itr = m_gameValues.begin(); itr != m_gameValues.end(); itr++) {
        std::cout << itr->first << "=" << itr->second << std::endl;
    }
}


