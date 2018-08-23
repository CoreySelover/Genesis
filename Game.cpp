
// Copyright 2018 Corey Selover

#include "Game.h"

// Project files
#include "Constants.h"
#include "Manager.h"
#include "Player.h"
#include "Splash.h"
#include "Map.h"
#include "Texture.h"

Game::Game() {}

BootError Game::boot() {

    // Window
    m_window.create(sf::VideoMode::getFullscreenModes()[0], "Genesis", sf::Style::Fullscreen);

    // Set up managers
    m_managers[TEXTURE_MANAGER] = new Manager();
    m_managers[SCREEN_MANAGER] = new Manager();

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

RunError Game::run() {

    while(m_running) {

        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                shutdown();
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

        // Draw
        m_window.clear();
        m_managers[SCREEN_MANAGER]->get(currentScreen)->draw();
        m_window.display();
    }

    return RUN_SUCCESS;
}

ShutdownError Game::shutdown() {

    m_running = false;

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

Texture* Game::addTexture(std::string filePath) {
    return static_cast<Texture*>(m_managers[TEXTURE_MANAGER]->add(filePath, new Texture(this, filePath)));
}

Screen* Game::screen(std::string name) {
    return static_cast<Screen*>(m_managers[SCREEN_MANAGER]->get(name));
}

void Game::setView(sf::View view) {
    m_window.setView(view);
}

sf::Vector2f Game::windowCenter() {
    return sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2);
}

const sf::View& Game::defaultView() {
    return m_window.getDefaultView();
}


