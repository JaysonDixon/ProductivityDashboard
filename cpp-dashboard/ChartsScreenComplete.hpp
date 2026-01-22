// ChartsScreenComplete.hpp
// Complete Charts Implementation with 6 Days Sample Data

#ifndef CHARTS_SCREEN_COMPLETE_HPP
#define CHARTS_SCREEN_COMPLETE_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include "ChartsDataModel.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>

class ChartsScreenComplete : public Screen {
private:
    sf::Font* font;
    sf::Text title;
    Button backButton;
    std::function<void(ScreenType)> onNavigate;
    ChartsDataModel dataModel;
    
    sf::Text statsText;
    std::vector<sf::RectangleShape> bars;
    std::vector<sf::Text> labels;
    std::vector<sf::Text> values;

public:
    ChartsScreenComplete(sf::Font& screenFont, std::function<void(ScreenType)> navigateCallback)
        : font(&screenFont), onNavigate(navigateCallback),
          backButton(20.f, 20.f, 100.f, 40.f, "Back", *font) {
        
        title.setFont(*font);
        title.setString("Charts & Analytics");
        title.setCharacterSize(32);
        title.setFillColor(sf::Color(50, 50, 50));
        title.setPosition(200.f, 20.f);

        statsText.setFont(*font);
        statsText.setCharacterSize(16);
        statsText.setFillColor(sf::Color(50, 50, 50));
        statsText.setPosition(150.f, 80.f);
        
        updateStats();
        createCharts();

        backButton.setOnClick([this]() {
            if (onNavigate) onNavigate(ScreenType::MENU);
        });
    }

    void updateStats() {
        std::stringstream ss;
        ss << "Weekly Summary (6 Days):\n\n";
        ss << "Exercise Days: " << dataModel.getTotalExerciseDays() << "/6 days\n";
        ss << "Average Water: " << dataModel.getAverageWater() << " glasses/day\n";
        ss << "Total Reading: " << dataModel.getTotalReadingMinutes() << " minutes\n";
        ss << "\nBar Chart: Daily Water Intake";
        
        statsText.setString(ss.str());
    }

    void createCharts() {
        const auto& weekData = dataModel.getWeekData();
        int maxWater = dataModel.getMaxValue("water");
        
        float startX = 150.f;
        float baseY = 500.f;
        float barWidth = 60.f;
        float spacing = 100.f;
        float maxBarHeight = 200.f;
        
        bars.clear();
        labels.clear();
        values.clear();
        
        for (size_t i = 0; i < weekData.size(); i++) {
            // Calculate bar height proportionally
            float barHeight = (weekData[i].waterGlasses / (float)maxWater) * maxBarHeight;
            
            // Create bar
            sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));
            bar.setPosition(startX + i * spacing, baseY - barHeight);
            bar.setFillColor(sf::Color(70, 130, 180));
            bars.push_back(bar);
            
            // Create day label
            sf::Text dayLabel(weekData[i].date, *font, 14);
            dayLabel.setFillColor(sf::Color(50, 50, 50));
            dayLabel.setPosition(startX + i * spacing + 15.f, baseY + 10.f);
            labels.push_back(dayLabel);
            
            // Create value label
            sf::Text valueLabel(std::to_string(weekData[i].waterGlasses), *font, 16);
            valueLabel.setFillColor(sf::Color(70, 130, 180));
            valueLabel.setPosition(startX + i * spacing + 20.f, baseY - barHeight - 25.f);
            values.push_back(valueLabel);
        }
    }

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override {
        backButton.handleEvent(event, window);
    }

    void update(float deltaTime) override {
        backButton.update();
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(title);
        backButton.draw(window);
        window.draw(statsText);
        
        // Draw chart axes
        sf::RectangleShape xAxis(sf::Vector2f(650.f, 2.f));
        xAxis.setPosition(150.f, 500.f);
        xAxis.setFillColor(sf::Color(100, 100, 100));
        window.draw(xAxis);
        
        sf::RectangleShape yAxis(sf::Vector2f(2.f, 220.f));
        yAxis.setPosition(150.f, 280.f);
        yAxis.setFillColor(sf::Color(100, 100, 100));
        window.draw(yAxis);
        
        // Draw bars and labels
        for (auto& bar : bars) {
            window.draw(bar);
        }
        for (auto& label : labels) {
            window.draw(label);
        }
        for (auto& value : values) {
            window.draw(value);
        }
    }

    ScreenType getType() const override {
        return ScreenType::CHARTS;
    }
};

#endif
