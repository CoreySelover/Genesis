
// Copyright 2018 Corey Selover

#include "Game.h"

// Project files
#include "Manager.h"

Game::Game() {}

BootError Game::boot() {

    // Window
    m_window.create(sf::VideoMode(800, 600), "Genesis");

    // Set up managers
    m_managers[TEXTURE_MANAGER] = new Manager();
    m_managers[ENTITY_MANAGER] = new Manager();
    m_managers[SCREEN_MANAGER] = new Manager();

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

        m_window.clear();

        /* Have all Managers update and draw.
         * We don't do this in a single loop because O(2n) == O(n)
         * for all intents and purposes and we theoretically are taking a more
         * data-oriented design approach by updating all managers in one go,
         * then drawing all managers in one go but this is just a hunch.
         */
        std::map<ManagerType, Manager*>::iterator itr;
        for(itr = m_managers.begin(); itr != m_managers.end(); itr++) {
            itr->second->update();
        }
        for(itr = m_managers.begin(); itr != m_managers.end(); itr++) {
            itr->second->draw();
        }

        m_window.display();
    }

    return RUN_SUCCESS;
}

ShutdownError Game::shutdown() {

    // Delete managers
    std::map<ManagerType, Manager*>::iterator itr;
    for(itr = m_managers.begin(); itr != m_managers.end(); itr++) {
        delete itr->second;
    }
    m_managers.clear();

    m_window.close();

    m_running = false;

    return SHUTDOWN_SUCCESS;
}
