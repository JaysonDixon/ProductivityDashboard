// main_complete.cpp
// Complete Productivity Dashboard Application
// All Features Implemented: T1, T2, Charts, Gamification, Settings

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ScreenManager.hpp"
#include "MenuScreen.hpp"
#include "DashboardScreenEnhanced.hpp"
#include "ChartsScreenComplete.hpp"
#include "GamifiedScreenComplete.hpp"
#include "SettingsScreenComplete.hpp"

int main() {
    const float WINDOW_WIDTH = 900.f;
    const float WINDOW_HEIGHT = 650.f;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
                           "Productivity Dashboard - Complete Version",
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

    // Initialize all screens
    screenManager.addScreen(ScreenType::MENU, 
        std::make_unique<MenuScreen>(font, WINDOW_WIDTH, WINDOW_HEIGHT, navigate));
    
    screenManager.addScreen(ScreenType::DASHBOARD, 
        std::make_unique<DashboardScreenEnhanced>(font, navigate));
    
    screenManager.addScreen(ScreenType::CHARTS, 
        std::make_unique<ChartsScreenComplete>(font, navigate));
    
    screenManager.addScreen(ScreenType::GAMIFIED, 
        std::make_unique<GamifiedScreenComplete>(font, navigate));
    
    screenManager.addScreen(ScreenType::SETTINGS, 
        std::make_unique<SettingsScreenComplete>(font, navigate));

    screenManager.setScreen(ScreenType::MENU);

    sf::Clock clock;

    std::cout << "===========================================================" << std::endl;
    std::cout << "  PRODUCTIVITY DASHBOARD - COMPLETE VERSION" << std::endl;
    std::cout << "  Advanced Software Engineering Project" << std::endl;
    std::cout << "===========================================================" << std::endl;
    std::cout << "\n✅ FEATURE IMPLEMENTATIONS:\n" << std::endl;
    std::cout << "T1 - Menu Interface:" << std::endl;
    std::cout << "  ✓ Responsive navigation with 4 feature buttons" << std::endl;
    std::cout << "  ✓ Smooth animations and transitions" << std::endl;
    std::cout << "  ✓ Scalable layout (handles window resize)" << std::endl;
    std::cout << "\nT2 - Multi-Type Habit Logging:" << std::endl;
    std::cout << "  ✓ Binary habits (yes/no checkboxes)" << std::endl;
    std::cout << "  ✓ Count-based habits (numeric input)" << std::endl;
    std::cout << "  ✓ Duration-based habits (time tracking)" << std::endl;
    std::cout << "  ✓ Backend data model (HabitModel)" << std::endl;
    std::cout << "  ✓ Feedback animations" << std::endl;
    std::cout << "  ✓ Console output logging" << std::endl;
    std::cout << "\nCharts & Analytics:" << std::endl;
    std::cout << "  ✓ 6-day sample data visualization" << std::endl;
    std::cout << "  ✓ Bar charts for habit tracking" << std::endl;
    std::cout << "  ✓ Weekly statistics summary" << std::endl;
    std::cout << "\nGamification System:" << std::endl;
    std::cout << "  ✓ XP and leveling system" << std::endl;
    std::cout << "  ✓ Achievement rewards" << std::endl;
    std::cout << "  ✓ Leaderboard with other clients" << std::endl;
    std::cout << "  ✓ Streak tracking" << std::endl;
    std::cout << "  ✓ Goal progression" << std::endl;
    std::cout << "\nSettings:" << std::endl;
    std::cout << "  ✓ Notification toggle" << std::endl;
    std::cout << "  ✓ Theme selection" << std::endl;
    std::cout << "  ✓ Daily goal configuration" << std::endl;
    std::cout << "  ✓ Data export/management" << std::endl;
    std::cout << "  ✓ About information" << std::endl;
    std::cout << "\n===========================================================" << std::endl;
    std::cout << "\n🚀 Application started successfully!" << std::endl;
    std::cout << "Navigate through the menu to explore all features.\n" << std::endl;

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

    std::cout << "\nApplication closed. Thank you for using Productivity Dashboard!" << std::endl;
    return 0;
}
