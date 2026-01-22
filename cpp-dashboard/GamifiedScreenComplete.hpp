// GamifiedScreenComplete.hpp
// Complete Gamification with Goals, Rewards, and Leaderboard
// WITH NAVIGATION BUTTONS TO OTHER SCREENS

#ifndef GAMIFIED_SCREEN_COMPLETE_HPP
#define GAMIFIED_SCREEN_COMPLETE_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "GamificationModel.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>

class GamifiedScreenComplete : public Screen {
private:
    sf::Font* font;
    sf::Text title;
    Button backButton;
    Button dashboardButton;
    Button chartsButton;
    Button settingsButton;
    std::function<void(ScreenType)> onNavigate;
    GamificationModel gamification;
    
    sf::Text levelText;
    sf::Text xpText;
    sf::Text streakText;
    sf::RectangleShape xpBar;
    sf::RectangleShape xpBarBg;
    sf::Text achievementsTitle;
    std::vector<sf::Text> achievementTexts;
    sf::Text leaderboardTitle;
    std::vector<sf::Text> leaderboardTexts;
    sf::Text nextGoalText;

public:
    GamifiedScreenComplete(sf::Font& screenFont, std::function<void(ScreenType)> navigateCallback)
        : font(&screenFont), onNavigate(navigateCallback),
          backButton(20.f, 20.f, 80.f, 35.f, "Menu", *font),
          dashboardButton(110.f, 20.f, 110.f, 35.f, "Dashboard", *font,
                         sf::Color(70, 130, 180), sf::Color(100, 160, 210), sf::Color(50, 110, 160)),
          chartsButton(230.f, 20.f, 80.f, 35.f, "Charts", *font,
                      sf::Color(60, 179, 113), sf::Color(90, 209, 143), sf::Color(40, 159, 93)),
          settingsButton(320.f, 20.f, 90.f, 35.f, "Settings", *font,
                        sf::Color(147, 112, 219), sf::Color(177, 142, 249), sf::Color(127, 92, 199)) {
        
        title.setFont(*font);
        title.setString("Gamified View - Progress & Rewards");
        title.setCharacterSize(28);
        title.setFillColor(sf::Color(50, 50, 50));
        title.setPosition(420.f, 22.f);

        // Level and XP display
        levelText.setFont(*font);
        levelText.setCharacterSize(24);
        levelText.setFillColor(sf::Color(255, 140, 0));
        levelText.setPosition(150.f, 80.f);
        
        xpText.setFont(*font);
        xpText.setCharacterSize(18);
        xpText.setFillColor(sf::Color(70, 130, 180));
        xpText.setPosition(150.f, 115.f);
        
        streakText.setFont(*font);
        streakText.setCharacterSize(20);
        streakText.setFillColor(sf::Color(255, 69, 0));
        streakText.setPosition(500.f, 85.f);
        
        // XP Progress Bar
        xpBarBg.setSize(sf::Vector2f(300.f, 25.f));
        xpBarBg.setPosition(150.f, 145.f);
        xpBarBg.setFillColor(sf::Color(200, 200, 200));
        xpBarBg.setOutlineThickness(2.f);
        xpBarBg.setOutlineColor(sf::Color(100, 100, 100));
        
        xpBar.setSize(sf::Vector2f(0.f, 25.f));
        xpBar.setPosition(150.f, 145.f);
        xpBar.setFillColor(sf::Color(60, 179, 113));
        
        // Achievements Section
        achievementsTitle.setFont(*font);
        achievementsTitle.setString("🏆 Achievements & Rewards:");
        achievementsTitle.setCharacterSize(20);
        achievementsTitle.setFillColor(sf::Color(50, 50, 50));
        achievementsTitle.setPosition(150.f, 200.f);
        
        // Leaderboard Section
        leaderboardTitle.setFont(*font);
        leaderboardTitle.setString("🏅 Leaderboard (Top Players):");
        leaderboardTitle.setCharacterSize(20);
        leaderboardTitle.setFillColor(sf::Color(50, 50, 50));
        leaderboardTitle.setPosition(150.f, 380.f);
        
        // Next Goal
        nextGoalText.setFont(*font);
        nextGoalText.setCharacterSize(16);
        nextGoalText.setFillColor(sf::Color(255, 140, 0));
        nextGoalText.setPosition(150.f, 180.f);
        
        updateDisplay();

        // Navigation button callbacks
        backButton.setOnClick([this]() {
            if (onNavigate) onNavigate(ScreenType::MENU);
        });

        dashboardButton.setOnClick([this]() {
            if (onNavigate) onNavigate(ScreenType::DASHBOARD);
        });

        chartsButton.setOnClick([this]() {
            if (onNavigate) onNavigate(ScreenType::CHARTS);
        });

        settingsButton.setOnClick([this]() {
            if (onNavigate) onNavigate(ScreenType::SETTINGS);
        });
    }

    void updateDisplay() {
        // Update level and XP
        std::stringstream ss;
        ss << "⭐ Level " << gamification.getCurrentLevel();
        levelText.setString(ss.str());
        
        ss.str("");
        ss << "XP: " << gamification.getXPProgress() << " / " 
           << gamification.getXPForNextLevel() << " (Total: " 
           << gamification.getCurrentXP() << ")";
        xpText.setString(ss.str());
        
        ss.str("");
        ss << "🔥 " << gamification.getCurrentStreak() << " Day Streak!";
        streakText.setString(ss.str());
        
        // Update XP bar
        float progress = (float)gamification.getXPProgress() / gamification.getXPForNextLevel();
        xpBar.setSize(sf::Vector2f(300.f * progress, 25.f));
        
        // Next goal
        ss.str("");
        ss << "📍 Next Goal: " << gamification.getNextGoal();
        nextGoalText.setString(ss.str());
        
        // Update achievements
        achievementTexts.clear();
        const auto& achievements = gamification.getAchievements();
        float yPos = 230.f;
        
        for (size_t i = 0; i < achievements.size() && i < 4; i++) {
            sf::Text achText;
            achText.setFont(*font);
            achText.setCharacterSize(15);
            achText.setPosition(160.f, yPos);
            
            ss.str("");
            ss << achievements[i].icon << " " << achievements[i].name;
            if (achievements[i].unlocked) {
                ss << " ✓ UNLOCKED";
                achText.setFillColor(sf::Color(60, 179, 113));
            } else {
                ss << " (" << achievements[i].description << ")";
                achText.setFillColor(sf::Color(150, 150, 150));
            }
            
            achText.setString(ss.str());
            achievementTexts.push_back(achText);
            yPos += 30.f;
        }
        
        // Update leaderboard
        leaderboardTexts.clear();
        const auto& leaderboard = gamification.getLeaderboard();
        yPos = 410.f;
        
        for (size_t i = 0; i < leaderboard.size(); i++) {
            sf::Text lbText;
            lbText.setFont(*font);
            lbText.setCharacterSize(16);
            lbText.setPosition(160.f, yPos);
            
            ss.str("");
            ss << (i + 1) << ". " << leaderboard[i].username 
               << " - Level " << leaderboard[i].level 
               << " (" << leaderboard[i].totalXP << " XP)";
            
            lbText.setString(ss.str());
            
            if (leaderboard[i].username == "You") {
                lbText.setFillColor(sf::Color(255, 140, 0));
                lbText.setStyle(sf::Text::Bold);
            } else {
                lbText.setFillColor(sf::Color(50, 50, 50));
            }
            
            leaderboardTexts.push_back(lbText);
            yPos += 25.f;
        }
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {
        backButton.handleEvent(event, window);
        dashboardButton.handleEvent(event, window);
        chartsButton.handleEvent(event, window);
        settingsButton.handleEvent(event, window);
    }

    void update(float deltaTime) override {
        backButton.update();
        dashboardButton.update();
        chartsButton.update();
        settingsButton.update();
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(title);
        backButton.draw(window);
        dashboardButton.draw(window);
        chartsButton.draw(window);
        settingsButton.draw(window);
        
        // Draw progress section
        window.draw(levelText);
        window.draw(xpText);
        window.draw(streakText);
        window.draw(xpBarBg);
        window.draw(xpBar);
        window.draw(nextGoalText);
        
        // Draw achievements
        window.draw(achievementsTitle);
        for (auto& text : achievementTexts) {
            window.draw(text);
        }
        
        // Draw leaderboard
        window.draw(leaderboardTitle);
        for (auto& text : leaderboardTexts) {
            window.draw(text);
        }
    }

    ScreenType getType() const override {
        return ScreenType::GAMIFIED;
    }
};

#endif
