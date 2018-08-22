
// Copyright 2018 Corey Selover

#include "Game.h"

// Project files
#include "Manager.h"
#include "Player.h"
#include "Splash.h"

Game::Game() {}

BootError Game::boot() {

    // Window
    m_window.create(sf::VideoMode(800, 600), "Genesis");

    // Set up managers
    m_managers[TEXTURE_MANAGER] = new Manager();
    m_managers[ENTITY_MANAGER] = new Manager();
    m_managers[SCREEN_MANAGER] = new Manager();

    m_managers[SCREEN_MANAGER]->add("happy_rock", new Splash(this, "resources/textures/splash.png", 3.f));
    m_currentScreen = "happy_rock";

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

        if(!m_running) return RUN_SUCCESS;

        // Update managers as appropriate.
        m_managers[SCREEN_MANAGER]->get(m_currentScreen)->update();
        m_managers[ENTITY_MANAGER]->update();

        // Draw
        m_window.clear();
        m_managers[SCREEN_MANAGER]->get(m_currentScreen)->draw();
        m_managers[ENTITY_MANAGER]->draw();

        m_window.display();
    }

    return RUN_SUCCESS;
}

ShutdownError Game::shutdown() {

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

    m_running = false;

    return SHUTDOWN_SUCCESS;
}
