// DashboardScreenEnhanced.hpp
// T2 Enhanced - Dashboard with Binary, Count, and Duration Habit Types

#ifndef DASHBOARD_SCREEN_ENHANCED_HPP
#define DASHBOARD_SCREEN_ENHANCED_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "HabitModel.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>

class DashboardScreenEnhanced : public Screen {
private:
    sf::Font* font;
    sf::Text title;
    Button backButton;
    std::function<void(ScreenType)> onNavigate;
    
    HabitModel habitModel;
    
    // Habit type selection
    std::vector<Button> habitTypeButtons;
    std::string selectedHabitName;
    HabitType selectedHabitType;
    
    // Input controls
    sf::RectangleShape checkBox;
    bool checkBoxChecked;
    sf::RectangleShape countInputBox;
    sf::Text countInputText;
    std::string countInput;
    bool countInputActive;
    sf::RectangleShape durationInputBox;
    sf::Text durationInputText;
    std::string durationInput;
    bool durationInputActive;
    
    Button submitButton;
    sf::Text instructionsText;
    sf::Text habitListText;
    
    // Feedback animation
    sf::CircleShape feedbackCircle;
    float feedbackAlpha;
    bool showFeedback;
    sf::Text feedbackText;

public:
    DashboardScreenEnhanced(sf::Font& screenFont, std::function<void(ScreenType)> navigateCallback)
        : font(&screenFont), onNavigate(navigateCallback),
          backButton(20.f, 20.f, 100.f, 40.f, "Back", *font),
          submitButton(650.f, 350.f, 150.f, 50.f, "Log Habit", *font,
                      sf::Color(60, 179, 113), sf::Color(90, 209, 143), sf::Color(40, 159, 93)),
          checkBoxChecked(false), countInputActive(false), durationInputActive(false),
          feedbackAlpha(0.f), showFeedback(false),
          selectedHabitType(HabitType::BINARY) {
        
        title.setFont(*font);
        title.setString("Dashboard - Multi-Type Habit Logging");
        title.setCharacterSize(28);
        title.setFillColor(sf::Color(50, 50, 50));
        title.setPosition(150.f, 20.f);

        // Create habit type buttons
        createHabitTypeButtons();

        // Checkbox for binary habits
        checkBox.setSize(sf::Vector2f(30.f, 30.f));
        checkBox.setPosition(150.f, 250.f);
        checkBox.setFillColor(sf::Color::White);
        checkBox.setOutlineThickness(2.f);
        checkBox.setOutlineColor(sf::Color(100, 100, 100));

        // Count input
        countInputBox.setPosition(150.f, 250.f);
        countInputBox.setSize(sf::Vector2f(150.f, 40.f));
        countInputBox.setFillColor(sf::Color::White);
        countInputBox.setOutlineThickness(2.f);
        countInputBox.setOutlineColor(sf::Color(150, 150, 150));
        
        countInputText.setFont(*font);
        countInputText.setCharacterSize(20);
        countInputText.setFillColor(sf::Color::Black);
        countInputText.setPosition(160.f, 258.f);

        // Duration input
        durationInputBox.setPosition(150.f, 250.f);
        durationInputBox.setSize(sf::Vector2f(150.f, 40.f));
        durationInputBox.setFillColor(sf::Color::White);
        durationInputBox.setOutlineThickness(2.f);
        durationInputBox.setOutlineColor(sf::Color(150, 150, 150));
        
        durationInputText.setFont(*font);
        durationInputText.setCharacterSize(20);
        durationInputText.setFillColor(sf::Color::Black);
        durationInputText.setPosition(160.f, 258.f);

        // Instructions
        instructionsText.setFont(*font);
        instructionsText.setCharacterSize(16);
        instructionsText.setFillColor(sf::Color(100, 100, 100));
        instructionsText.setPosition(150.f, 220.f);

        // Habit list
        habitListText.setFont(*font);
        habitListText.setCharacterSize(16);
        habitListText.setFillColor(sf::Color(50, 50, 50));
        habitListText.setPosition(150.f, 420.f);
        updateHabitList();

        // Feedback circle
        feedbackCircle.setRadius(50.f);
        feedbackCircle.setPosition(400.f, 200.f);
        feedbackCircle.setFillColor(sf::Color(60, 179, 113, 0));

        feedbackText.setFont(*font);
        feedbackText.setString("Logged!");
        feedbackText.setCharacterSize(24);
        feedbackText.setFillColor(sf::Color(60, 179, 113, 0));
        feedbackText.setPosition(400.f, 220.f);

        backButton.setOnClick([this]() {
            if (onNavigate) onNavigate(ScreenType::MENU);
        });

        submitButton.setOnClick([this]() {
            logCurrentHabit();
        });
    }

    void createHabitTypeButtons() {
        float startX = 150.f;
        float startY = 80.f;
        float spacing = 110.f;

        std::vector<std::pair<std::string, HabitType>> habitTypes = {
            {"Exercise", HabitType::BINARY},
            {"Water", HabitType::COUNT},
            {"Reading", HabitType::DURATION},
            {"Push-ups", HabitType::COUNT},
            {"Meditation", HabitType::DURATION},
            {"Study", HabitType::DURATION}
        };

        for (size_t i = 0; i < habitTypes.size(); i++) {
            float x = startX + (i % 3) * spacing;
            float y = startY + (i / 3) * 70.f;
            
            Button btn(x, y, 100.f, 50.f, habitTypes[i].first, *font,
                      sf::Color(100, 149, 237), sf::Color(120, 169, 255), sf::Color(80, 129, 217));
            
            std::string name = habitTypes[i].first;
            HabitType type = habitTypes[i].second;
            
            btn.setOnClick([this, name, type]() {
                selectHabitType(name, type);
            });
            
            habitTypeButtons.push_back(btn);
        }

        selectedHabitName = "Exercise";
        selectedHabitType = HabitType::BINARY;
        updateInstructions();
    }

    void selectHabitType(const std::string& name, HabitType type) {
        selectedHabitName = name;
        selectedHabitType = type;
        countInput.clear();
        durationInput.clear();
        checkBoxChecked = false;
        updateInstructions();
    }

    void updateInstructions() {
        std::string text = "Selected: " + selectedHabitName + " - ";
        switch(selectedHabitType) {
            case HabitType::BINARY:
                text += "Check if completed";
                break;
            case HabitType::COUNT:
                text += "Enter count (e.g., 8 glasses)";
                break;
            case HabitType::DURATION:
                text += "Enter minutes (e.g., 30)";
                break;
        }
        instructionsText.setString(text);
    }

    void logCurrentHabit() {
        int value = 0;
        
        switch(selectedHabitType) {
            case HabitType::BINARY:
                value = checkBoxChecked ? 1 : 0;
                break;
            case HabitType::COUNT:
                if (!countInput.empty()) {
                    value = std::stoi(countInput);
                }
                break;
            case HabitType::DURATION:
                if (!durationInput.empty()) {
                    value = std::stoi(durationInput);
                }
                break;
        }

        if (selectedHabitType == HabitType::BINARY || value > 0) {
            habitModel.addHabit(selectedHabitName, selectedHabitType, value);
            updateHabitList();
            triggerFeedback();
            
            // Reset inputs
            checkBoxChecked = false;
            countInput.clear();
            durationInput.clear();
            countInputText.setString("");
            durationInputText.setString("");
        }
    }

    void triggerFeedback() {
        showFeedback = true;
        feedbackAlpha = 255.f;
    }

    void updateHabitList() {
        std::stringstream ss;
        ss << "Today's Habits (" << habitModel.getTotalCount() << " logged):\n\n";
        
        const auto& habits = habitModel.getTodayHabits();
        for (size_t i = 0; i < habits.size(); i++) {
            ss << (i + 1) << ". " << habits[i].name << " - ";
            
            switch(habits[i].type) {
                case HabitType::BINARY:
                    ss << (habits[i].value ? "✓ Done" : "✗ Not done");
                    break;
                case HabitType::COUNT:
                    ss << habits[i].value << "x";
                    break;
                case HabitType::DURATION:
                    ss << habits[i].value << " min";
                    break;
            }
            ss << "\n";
        }
        
        habitListText.setString(ss.str());
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {
        backButton.handleEvent(event, window);
        submitButton.handleEvent(event, window);
        
        for (auto& btn : habitTypeButtons) {
            btn.handleEvent(event, window);
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

            // Checkbox click
            if (selectedHabitType == HabitType::BINARY &&
                checkBox.getGlobalBounds().contains(mousePosF)) {
                checkBoxChecked = !checkBoxChecked;
            }

            // Count input click
            if (selectedHabitType == HabitType::COUNT) {
                countInputActive = countInputBox.getGlobalBounds().contains(mousePosF);
                countInputBox.setOutlineColor(countInputActive ? 
                    sf::Color(70, 130, 180) : sf::Color(150, 150, 150));
            }

            // Duration input click
            if (selectedHabitType == HabitType::DURATION) {
                durationInputActive = durationInputBox.getGlobalBounds().contains(mousePosF);
                durationInputBox.setOutlineColor(durationInputActive ? 
                    sf::Color(70, 130, 180) : sf::Color(150, 150, 150));
            }
        }

        // Text input for COUNT
        if (event.type == sf::Event::TextEntered && countInputActive && 
            selectedHabitType == HabitType::COUNT) {
            if (event.text.unicode == '\b' && !countInput.empty()) {
                countInput.pop_back();
            } else if (event.text.unicode >= '0' && event.text.unicode <= '9' && countInput.size() < 5) {
                countInput += static_cast<char>(event.text.unicode);
            }
            countInputText.setString(countInput);
        }

        // Text input for DURATION
        if (event.type == sf::Event::TextEntered && durationInputActive && 
            selectedHabitType == HabitType::DURATION) {
            if (event.text.unicode == '\b' && !durationInput.empty()) {
                durationInput.pop_back();
            } else if (event.text.unicode >= '0' && event.text.unicode <= '9' && durationInput.size() < 5) {
                durationInput += static_cast<char>(event.text.unicode);
            }
            durationInputText.setString(durationInput);
        }
    }

    void update(float deltaTime) override {
        backButton.update();
        submitButton.update();
        
        for (auto& btn : habitTypeButtons) {
            btn.update();
        }

        // Update feedback animation
        if (showFeedback) {
            feedbackAlpha -= 200.f * deltaTime;
            if (feedbackAlpha <= 0.f) {
                feedbackAlpha = 0.f;
                showFeedback = false;
            }
            sf::Color color = feedbackCircle.getFillColor();
            color.a = static_cast<sf::Uint8>(feedbackAlpha);
            feedbackCircle.setFillColor(color);
            feedbackText.setFillColor(color);
        }
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(title);
        backButton.draw(window);
        
        for (auto& btn : habitTypeButtons) {
            btn.draw(window);
        }

        window.draw(instructionsText);

        // Draw appropriate input control
        switch(selectedHabitType) {
            case HabitType::BINARY:
                window.draw(checkBox);
                if (checkBoxChecked) {
                    sf::RectangleShape check(sf::Vector2f(20.f, 20.f));
                    check.setPosition(155.f, 255.f);
                    check.setFillColor(sf::Color(60, 179, 113));
                    window.draw(check);
                }
                break;
            case HabitType::COUNT:
                window.draw(countInputBox);
                window.draw(countInputText);
                break;
            case HabitType::DURATION:
                window.draw(durationInputBox);
                window.draw(durationInputText);
                break;
        }

        submitButton.draw(window);
        window.draw(habitListText);

        // Draw feedback
        if (showFeedback) {
            window.draw(feedbackCircle);
            window.draw(feedbackText);
        }
    }

    ScreenType getType() const override {
        return ScreenType::DASHBOARD;
    }
};

#endif
