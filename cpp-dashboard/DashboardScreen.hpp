// DashboardScreen.hpp
// T2 - Dashboard with Habit Logging Input

#ifndef DASHBOARD_SCREEN_HPP
#define DASHBOARD_SCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class DashboardScreen : public Screen {
private:
    sf::Font* font;
    sf::Text title;
    sf::Text habitPrompt;
    sf::RectangleShape inputBox;
    sf::Text inputText;
    std::string currentInput;
    bool isInputActive;
    Button backButton;
    Button logButton;
    std::vector<std::string> loggedHabits;
    sf::Text habitsList;
    std::function<void(ScreenType)> onNavigate;

public:
    DashboardScreen(sf::Font& screenFont, std::function<void(ScreenType)> navigateCallback)
        : font(&screenFont), isInputActive(false), onNavigate(navigateCallback),
          backButton(20.f, 20.f, 100.f, 40.f, "Back", *font),
          logButton(600.f, 250.f, 120.f, 50.f, "Log Habit", *font,
                   sf::Color(60, 179, 113), sf::Color(90, 209, 143), sf::Color(40, 159, 93)) {
        
        title.setFont(*font);
        title.setString("Dashboard - Habit Logging");
        title.setCharacterSize(32);
        title.setFillColor(sf::Color(50, 50, 50));
        title.setPosition(200.f, 30.f);

        habitPrompt.setFont(*font);
        habitPrompt.setString("Enter habit name:");
        habitPrompt.setCharacterSize(20);
        habitPrompt.setFillColor(sf::Color(70, 70, 70));
        habitPrompt.setPosition(150.f, 150.f);

        inputBox.setPosition(150.f, 200.f);
        inputBox.setSize(sf::Vector2f(400.f, 50.f));
        inputBox.setFillColor(sf::Color::White);
        inputBox.setOutlineThickness(2.f);
        inputBox.setOutlineColor(sf::Color(150, 150, 150));

        inputText.setFont(*font);
        inputText.setCharacterSize(20);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(160.f, 215.f);

        habitsList.setFont(*font);
        habitsList.setCharacterSize(18);
        habitsList.setFillColor(sf::Color(50, 50, 50));
        habitsList.setPosition(150.f, 350.f);

        backButton.setOnClick([this]() {
            if (onNavigate) onNavigate(ScreenType::MENU);
        });

        logButton.setOnClick([this]() {
            logHabit();
        });
    }

    void logHabit() {
        if (!currentInput.empty()) {
            loggedHabits.push_back(currentInput);
            currentInput.clear();
            inputText.setString("");
            updateHabitsList();
        }
    }

    void updateHabitsList() {
        std::string listText = "Logged Habits Today:\n\n";
        for (size_t i = 0; i < loggedHabits.size(); i++) {
            listText += "  " + std::to_string(i + 1) + ". " + loggedHabits[i] + "\n";
        }
        habitsList.setString(listText);
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {
        backButton.handleEvent(event, window);
        logButton.handleEvent(event, window);

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            isInputActive = inputBox.getGlobalBounds().contains(mousePosF);
            
            if (isInputActive) {
                inputBox.setOutlineColor(sf::Color(70, 130, 180));
            } else {
                inputBox.setOutlineColor(sf::Color(150, 150, 150));
            }
        }

        if (event.type == sf::Event::TextEntered && isInputActive) {
            if (event.text.unicode == '\b') {
                if (!currentInput.empty()) {
                    currentInput.pop_back();
                }
            } else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                logHabit();
            } else if (event.text.unicode < 128 && event.text.unicode != '\t') {
                if (currentInput.size() < 30) {
                    currentInput += static_cast<char>(event.text.unicode);
                }
            }
            inputText.setString(currentInput);
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && isInputActive) {
            logHabit();
        }
    }

    void update(float deltaTime) override {
        backButton.update();
        logButton.update();
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(title);
        backButton.draw(window);
        window.draw(habitPrompt);
        window.draw(inputBox);
        window.draw(inputText);
        logButton.draw(window);
        window.draw(habitsList);
    }

    ScreenType getType() const override {
        return ScreenType::DASHBOARD;
    }
};

#endif
