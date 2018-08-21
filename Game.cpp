
// Copyright 2018 Corey Selover

#include "Game.h"

// Project files
#include "Manager.h"

Game::Game() {}

BootError Game::boot() {

    // Window
    m_window.create(sf::VideoMode(800, 600), "Genesis");

    // Set up managers
    m_managers[ENTITY_MANAGER] = new Manager();

    m_running = true;

    return BOOT_SUCCESS;
}

RunError Game::run() {

    while(m_running) {

        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                shutdown();
        }

        // Update loop
        m_window.clear();
        // Draw loop
        m_window.display();
    }

    return RUN_SUCCESS;
}

ShutdownError Game::shutdown() {

    // Delete managers
    delete m_managers[ENTITY_MANAGER];

    m_window.close();
    return SHUTDOWN_SUCCESS;
}
