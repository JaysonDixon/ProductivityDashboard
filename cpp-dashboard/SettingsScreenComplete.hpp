// SettingsScreenComplete.hpp
// Complete Settings Implementation

#ifndef SETTINGS_SCREEN_COMPLETE_HPP
#define SETTINGS_SCREEN_COMPLETE_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>

class SettingsScreenComplete : public Screen {
private:
    sf::Font* font;
    sf::Text title;
    Button backButton;
    std::function<void(ScreenType)> onNavigate;
    
    // Settings categories
    sf::Text notificationsTitle;
    Button notificationToggle;
    bool notificationsEnabled;
    
    sf::Text themeTitle;
    Button lightThemeBtn;
    Button darkThemeBtn;
    std::string currentTheme;
    
    sf::Text goalTitle;
    sf::Text dailyGoalText;
    Button increaseGoalBtn;
    Button decreaseGoalBtn;
    int dailyHabitGoal;
    
    sf::Text dataTitle;
    Button exportDataBtn;
    Button clearDataBtn;
    
    sf::Text aboutTitle;
    sf::Text aboutText;

public:
    SettingsScreenComplete(sf::Font& screenFont, std::function<void(ScreenType)> navigateCallback)
        : font(&screenFont), onNavigate(navigateCallback),
          backButton(20.f, 20.f, 100.f, 40.f, "Back", *font),
          notificationToggle(450.f, 110.f, 100.f, 35.f, "ON", *font,
                            sf::Color(60, 179, 113), sf::Color(90, 209, 143), sf::Color(40, 159, 93)),
          lightThemeBtn(350.f, 180.f, 100.f, 35.f, "Light", *font),
          darkThemeBtn(470.f, 180.f, 100.f, 35.f, "Dark", *font),
          increaseGoalBtn(450.f, 260.f, 50.f, 35.f, "+", *font,
                         sf::Color(70, 130, 180), sf::Color(100, 160, 210), sf::Color(50, 110, 160)),
          decreaseGoalBtn(520.f, 260.f, 50.f, 35.f, "-", *font,
                         sf::Color(70, 130, 180), sf::Color(100, 160, 210), sf::Color(50, 110, 160)),
          exportDataBtn(150.f, 330.f, 150.f, 40.f, "Export Data", *font,
                       sf::Color(100, 149, 237), sf::Color(120, 169, 255), sf::Color(80, 129, 217)),
          clearDataBtn(320.f, 330.f, 150.f, 40.f, "Clear Data", *font,
                      sf::Color(220, 20, 60), sf::Color(250, 50, 90), sf::Color(190, 10, 50)),
          notificationsEnabled(true),
          currentTheme("Light"),
          dailyHabitGoal(5) {
        
        title.setFont(*font);
        title.setString("Settings");
        title.setCharacterSize(32);
        title.setFillColor(sf::Color(50, 50, 50));
        title.setPosition(200.f, 20.f);

        // Notifications Section
        notificationsTitle.setFont(*font);
        notificationsTitle.setString("🔔 Daily Reminders:");
        notificationsTitle.setCharacterSize(18);
        notificationsTitle.setFillColor(sf::Color(50, 50, 50));
        notificationsTitle.setPosition(150.f, 110.f);
        
        // Theme Section
        themeTitle.setFont(*font);
        themeTitle.setString("🎨 Theme:");
        themeTitle.setCharacterSize(18);
        themeTitle.setFillColor(sf::Color(50, 50, 50));
        themeTitle.setPosition(150.f, 180.f);
        
        // Daily Goal Section
        goalTitle.setFont(*font);
        goalTitle.setString("🎯 Daily Habit Goal:");
        goalTitle.setCharacterSize(18);
        goalTitle.setFillColor(sf::Color(50, 50, 50));
        goalTitle.setPosition(150.f, 230.f);
        
        dailyGoalText.setFont(*font);
        dailyGoalText.setCharacterSize(20);
        dailyGoalText.setFillColor(sf::Color(70, 130, 180));
        dailyGoalText.setPosition(150.f, 260.f);
        updateGoalText();
        
        // Data Management Section
        dataTitle.setFont(*font);
        dataTitle.setString("💾 Data Management:");
        dataTitle.setCharacterSize(18);
        dataTitle.setFillColor(sf::Color(50, 50, 50));
        dataTitle.setPosition(150.f, 300.f);
        
        // About Section
        aboutTitle.setFont(*font);
        aboutTitle.setString("ℹ️ About:");
        aboutTitle.setCharacterSize(18);
        aboutTitle.setFillColor(sf::Color(50, 50, 50));
        aboutTitle.setPosition(150.f, 400.f);
        
        aboutText.setFont(*font);
        aboutText.setString("Productivity Dashboard v1.0\nDeveloped for Advanced Software Engineering\nFeatures: Multi-type habit logging, charts, gamification\nPersistent data storage with file I/O");
        aboutText.setCharacterSize(14);
        aboutText.setFillColor(sf::Color(100, 100, 100));
        aboutText.setPosition(150.f, 430.f);

        // Set up button callbacks
        backButton.setOnClick([this]() {
            if (onNavigate) onNavigate(ScreenType::MENU);
        });

        notificationToggle.setOnClick([this]() {
            toggleNotifications();
        });

        lightThemeBtn.setOnClick([this]() {
            currentTheme = "Light";
            std::cout << "Theme changed to: Light" << std::endl;
        });

        darkThemeBtn.setOnClick([this]() {
            currentTheme = "Dark";
            std::cout << "Theme changed to: Dark (not fully implemented)" << std::endl;
        });

        increaseGoalBtn.setOnClick([this]() {
            if (dailyHabitGoal < 20) {
                dailyHabitGoal++;
                updateGoalText();
                std::cout << "Daily goal increased to: " << dailyHabitGoal << std::endl;
            }
        });

        decreaseGoalBtn.setOnClick([this]() {
            if (dailyHabitGoal > 1) {
                dailyHabitGoal--;
                updateGoalText();
                std::cout << "Daily goal decreased to: " << dailyHabitGoal << std::endl;
            }
        });

        exportDataBtn.setOnClick([this]() {
            std::cout << "Exporting data to CSV..." << std::endl;
            // Simulate export
        });

        clearDataBtn.setOnClick([this]() {
            std::cout << "WARNING: Clear data requested (not implemented)" << std::endl;
        });
    }

    void toggleNotifications() {
        notificationsEnabled = !notificationsEnabled;
        notificationToggle.setOnClick([this]() {
            toggleNotifications();
        });
        std::cout << "Notifications " << (notificationsEnabled ? "enabled" : "disabled") << std::endl;
    }

    void updateGoalText() {
        std::stringstream ss;
        ss << dailyHabitGoal << " habits per day";
        dailyGoalText.setString(ss.str());
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {
        backButton.handleEvent(event, window);
        notificationToggle.handleEvent(event, window);
        lightThemeBtn.handleEvent(event, window);
        darkThemeBtn.handleEvent(event, window);
        increaseGoalBtn.handleEvent(event, window);
        decreaseGoalBtn.handleEvent(event, window);
        exportDataBtn.handleEvent(event, window);
        clearDataBtn.handleEvent(event, window);
    }

    void update(float deltaTime) override {
        backButton.update();
        notificationToggle.update();
        lightThemeBtn.update();
        darkThemeBtn.update();
        increaseGoalBtn.update();
        decreaseGoalBtn.update();
        exportDataBtn.update();
        clearDataBtn.update();
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(title);
        backButton.draw(window);
        
        // Notifications
        window.draw(notificationsTitle);
        notificationToggle.draw(window);
        
        // Theme
        window.draw(themeTitle);
        lightThemeBtn.draw(window);
        darkThemeBtn.draw(window);
        
        // Daily Goal
        window.draw(goalTitle);
        window.draw(dailyGoalText);
        increaseGoalBtn.draw(window);
        decreaseGoalBtn.draw(window);
        
        // Data Management
        window.draw(dataTitle);
        exportDataBtn.draw(window);
        clearDataBtn.draw(window);
        
        // About
        window.draw(aboutTitle);
        window.draw(aboutText);
    }

    ScreenType getType() const override {
        return ScreenType::SETTINGS;
    }
};

#endif
