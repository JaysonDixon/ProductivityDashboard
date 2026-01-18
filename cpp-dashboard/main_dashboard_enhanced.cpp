// main_dashboard_enhanced.cpp
// T2 Enhanced Implementation - Multi-Type Habit Logging
// Personal Productivity Dashboard with Binary, Count, and Duration Habits

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ScreenManager.hpp"
#include "MenuScreen.hpp"
#include "DashboardScreenEnhanced.hpp"
#include "ChartsScreen.hpp"
#include "GamifiedScreen.hpp"
#include "SettingsScreen.hpp"

int main() {
    const float WINDOW_WIDTH = 900.f;
    const float WINDOW_HEIGHT = 650.f;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
                           "Productivity Dashboard - Enhanced T2",
                           sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Warning: Failed to load font. Using default font." << std::endl;
    }

    ScreenManager screenManager;

    auto navigate = [&screenManager](ScreenType type) {
        screenManager.setScreen(type);
    };

    screenManager.addScreen(ScreenType::MENU, 
        std::make_unique<MenuScreen>(font, WINDOW_WIDTH, WINDOW_HEIGHT, navigate));
    
    screenManager.addScreen(ScreenType::DASHBOARD, 
        std::make_unique<DashboardScreenEnhanced>(font, navigate));
    
    screenManager.addScreen(ScreenType::CHARTS, 
        std::make_unique<ChartsScreen>(font, navigate));
    
    screenManager.addScreen(ScreenType::GAMIFIED, 
        std::make_unique<GamifiedScreen>(font, navigate));
    
    screenManager.addScreen(ScreenType::SETTINGS, 
        std::make_unique<SettingsScreen>(font, navigate));

    screenManager.setScreen(ScreenType::MENU);

    sf::Clock clock;

    std::cout << "==================================================" << std::endl;
    std::cout << "  Productivity Dashboard - Enhanced T2" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "\nT1 - Menu Interface: ✓ Implemented" << std::endl;
    std::cout << "  - Dashboard navigation button" << std::endl;
    std::cout << "  - Charts navigation button" << std::endl;
    std::cout << "  - Gamified View navigation button" << std::endl;
    std::cout << "  - Settings navigation button" << std::endl;
    std::cout << "  - Responsive layout" << std::endl;
    std::cout << "\nT2 Enhanced - Multi-Type Habit Logging: ✓ Implemented" << std::endl;
    std::cout << "  - Binary habits (yes/no checkboxes)" << std::endl;
    std::cout << "  - Count-based habits (numeric input)" << std::endl;
    std::cout << "  - Duration-based habits (time tracking)" << std::endl;
    std::cout << "  - Backend data model (HabitModel)" << std::endl;
    std::cout << "  - Feedback animations" << std::endl;
    std::cout << "  - Console output logging" << std::endl;
    std::cout << "  - Data persistence" << std::endl;
    std::cout << "\n==================================================" << std::endl;
    std::cout << "\nApplication started successfully!" << std::endl;
    std::cout << "Try logging different habit types.\n" << std::endl;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            screenManager.handleEvent(event, window);
        }

        float deltaTime = clock.restart().asSeconds();
        screenManager.update(deltaTime);

        window.clear(sf::Color(240, 240, 245));
        screenManager.draw(window);
        window.display();
    }

    return 0;
}
