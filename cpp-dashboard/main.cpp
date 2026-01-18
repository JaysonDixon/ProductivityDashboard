// main.cpp
// Personal Productivity Dashboard - Complete Version
// Features: Habit Tracking, Streaks, Trends, Analytics, Gamification, Animations, Audio, Rule Engine

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <functional>
#include <ctime>
#include <string>

// -------------------------------
// Utility: Get today's date string
// -------------------------------
std::string getToday() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", now);
    return std::string(buf);
}

// -------------------------------
// Habit Log with streaks & trends
// -------------------------------
class HabitLog {
private:
    struct HabitData {
        int totalCount = 0;
        int currentStreak = 0;
        std::string lastDate = "";
        std::vector<int> weeklyCounts;
    };

    std::map<std::string, HabitData> habits;

public:
    void logHabit(const std::string& habitName) {
        std::string today = getToday();
        HabitData& h = habits[habitName];

        h.totalCount++;

        if (h.lastDate == today) {
            // already logged today
        } else if (h.lastDate.empty()) {
            h.currentStreak = 1;
        } else {
            time_t t = time(nullptr);
            tm* now = localtime(&t);
            now->tm_mday -= 1;
            mktime(now);
            char buf[11];
            strftime(buf, sizeof(buf), "%Y-%m-%d", now);
            std::string yesterday(buf);

            if (h.lastDate == yesterday) {
                h.currentStreak++;
            } else {
                h.currentStreak = 1;
            }
        }

        h.lastDate = today;

        if (h.weeklyCounts.size() >= 7) h.weeklyCounts.erase(h.weeklyCounts.begin());
        h.weeklyCounts.push_back(1);

        std::cout << "Habit logged: " << habitName
                  << " | Streak: " << h.currentStreak
                  << " | Total: " << h.totalCount << std::endl;
        
        saveToFile();
    }

    const std::map<std::string, HabitData>& getHabits() const { return habits; }

    int getStreak(const std::string& habitName) const {
        auto it = habits.find(habitName);
        return (it != habits.end()) ? it->second.currentStreak : 0;
    }

    int getTotalCount(const std::string& habitName) const {
        auto it = habits.find(habitName);
        return (it != habits.end()) ? it->second.totalCount : 0;
    }

    std::string getTrend(const std::string& habitName) const {
        auto it = habits.find(habitName);
        if (it == habits.end()) return "No data";

        const auto& counts = it->second.weeklyCounts;
        if (counts.size() < 2) return "Insufficient";

        int sumFirstHalf = 0, sumSecondHalf = 0;
        int mid = counts.size() / 2;
        for (int i = 0; i < mid; i++) sumFirstHalf += counts[i];
        for (size_t i = mid; i < counts.size(); i++) sumSecondHalf += counts[i];

        if (sumSecondHalf > sumFirstHalf) return "Up";
        else if (sumSecondHalf < sumFirstHalf) return "Down";
        else return "Stable";
    }

    void saveToFile() {
        std::ofstream file("habit_log.txt");
        for (auto& h : habits) {
            file << h.first << " " << h.second.totalCount << " " 
                 << h.second.currentStreak << " " << h.second.lastDate << "\n";
        }
    }

    void loadFromFile() {
        std::ifstream file("habit_log.txt");
        std::string name, date;
        int count, streak;
        while (file >> name >> count >> streak >> date) {
            habits[name].totalCount = count;
            habits[name].currentStreak = streak;
            habits[name].lastDate = date;
        }
    }
};

// -------------------------------
// Analytics Module
// -------------------------------
class AnalyticsModule {
public:
    void update(const HabitLog& log) {
        std::cout << "Analytics updated. Total habits tracked: " << log.getHabits().size() << std::endl;
    }

    int getTotalHabits(const HabitLog& log) const {
        return log.getHabits().size();
    }
};

// -------------------------------
// Suggestion Engine
// -------------------------------
class SuggestionEngine {
private:
    std::vector<std::string> tips = {
        "Stay consistent!",
        "Small steps lead to big wins.",
        "Celebrate progress, not perfection.",
        "Track habits daily for best results.",
        "Build momentum with streaks!",
        "Every day is a new opportunity."
    };
public:
    std::string getSuggestion() {
        return tips[rand() % tips.size()];
    }
};

// -------------------------------
// Gamified Environment
// -------------------------------
class GamifiedEnvironment {
private:
    int xp = 0;
    int level = 1;
public:
    void update() {
        xp += 10;
        if (xp >= level * 50) {
            level++;
            std::cout << "Level up! You are now level " << level << std::endl;
        }
    }

    int getXP() const { return xp; }
    int getLevel() const { return level; }

    void draw(sf::RenderWindow& window, sf::Font& font) {
        sf::Text status("XP: " + std::to_string(xp) + " | Level: " + std::to_string(level), font, 18);
        status.setFillColor(sf::Color::Green);
        status.setPosition(100.f, 100.f);
        window.draw(status);
    }
};

// -------------------------------
// Chart View
// -------------------------------
class ChartView {
public:
    void draw(sf::RenderWindow& window, const HabitLog& log, sf::Font& font) {
        int x = 100;
        int y = 500;
        int barWidth = 40;
        int spacing = 20;

        for (auto& h : log.getHabits()) {
            int barHeight = h.second.totalCount * 5;
            if (barHeight > 200) barHeight = 200;

            sf::RectangleShape bar(sf::Vector2f(barWidth, barHeight));
            bar.setFillColor(sf::Color::Blue);
            bar.setPosition(x, y - barHeight);
            window.draw(bar);

            sf::Text label(h.first.substr(0, 4), font, 12);
            label.setFillColor(sf::Color::Black);
            label.setPosition(x - 5, y + 5);
            window.draw(label);

            x += barWidth + spacing;
            if (x > 700) break;
        }
    }
};

// -------------------------------
// Stats View
// -------------------------------
class StatsView {
public:
    void draw(sf::RenderWindow& window, sf::Font& font, const HabitLog& log) {
        int y = 200;
        for (auto& pair : log.getHabits()) {
            const std::string& name = pair.first;

            std::string textStr = name + " | Streak: " + std::to_string(log.getStreak(name))
                                  + " | Total: " + std::to_string(log.getTotalCount(name))
                                  + " | Trend: " + log.getTrend(name);

            sf::Text text(textStr, font, 14);
            text.setFillColor(sf::Color::Black);
            text.setPosition(100.f, (float)y);
            window.draw(text);

            y += 25;
            if (y > 400) break;
        }
    }
};

// -------------------------------
// Rule Engine
// -------------------------------
class Rule {
public:
    std::function<bool()> condition;
    std::function<void()> action;

    Rule(std::function<bool()> cond, std::function<void()> act)
        : condition(cond), action(act) {}

    void evaluate() {
        if (condition()) {
            action();
        }
    }
};

class RuleEngine {
private:
    std::vector<Rule> rules;
public:
    void addRule(const Rule& rule) {
        rules.push_back(rule);
    }

    void evaluateAll() {
        for (auto& r : rules) {
            r.evaluate();
        }
    }
};

// -------------------------------
// Animation Manager
// -------------------------------
class Animation {
private:
    sf::CircleShape shape;
    float speed;
    float phase;
public:
    Animation(float spd = 100.f) : speed(spd), phase(0.f) {
        shape.setRadius(20.f);
        shape.setFillColor(sf::Color::Cyan);
        shape.setPosition(100.f, 450.f);
    }

    void update(float deltaTime) {
        phase += deltaTime;
        float offset = sin(phase * 2.0f) * 50.0f;
        shape.setPosition(100.f + offset, 450.f);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
};

// -------------------------------
// Audio Manager
// -------------------------------
class AudioManager {
private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
public:
    void loadSound(const std::string& file) {
        if (!buffer.loadFromFile(file)) {
            std::cerr << "Failed to load sound: " << file << " (optional)" << std::endl;
        } else {
            sound.setBuffer(buffer);
        }
    }

    void playSound() {
        if (buffer.getSampleCount() > 0) {
            sound.play();
        }
    }
};

// -------------------------------
// Application Entry Point
// -------------------------------
int main() {
    sf::RenderWindow window(sf::VideoMode(900, 650), "Personal Productivity Dashboard");

    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Warning: Failed to load font. Using default font." << std::endl;
    }

    sf::Text title("Personal Productivity Dashboard", font, 26);
    title.setFillColor(sf::Color::Black);
    title.setPosition(150.f, 20.f);

    sf::Text instructions("Press [Space] = Log Exercise | [W] = Log Work | [R] = Log Reading | [M] = Log Meditation", font, 12);
    instructions.setFillColor(sf::Color(100, 100, 100));
    instructions.setPosition(50.f, 60.f);

    HabitLog habitLog;
    habitLog.loadFromFile();
    
    AnalyticsModule analytics;
    SuggestionEngine suggestions;
    ChartView charts;
    StatsView stats;
    GamifiedEnvironment gamified;
    RuleEngine ruleEngine;
    Animation animation(150.f);
    AudioManager audio;

    audio.loadSound("assets/click.wav");

    sf::Text suggestionText("Tip: " + suggestions.getSuggestion(), font, 16);
    suggestionText.setFillColor(sf::Color(200, 50, 50));
    suggestionText.setPosition(100.f, 140.f);

    ruleEngine.addRule(Rule(
        [&]() { return !habitLog.getHabits().empty(); },
        [&]() { analytics.update(habitLog); }
    ));

    ruleEngine.addRule(Rule(
        [&]() { return gamified.getXP() % 50 == 0 && gamified.getXP() > 0; },
        [&]() { 
            suggestionText.setString("Motivation: " + suggestions.getSuggestion());
        }
    ));

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                bool logged = false;
                
                if (event.key.code == sf::Keyboard::Space) {
                    habitLog.logHabit("Exercise");
                    logged = true;
                }
                else if (event.key.code == sf::Keyboard::W) {
                    habitLog.logHabit("Work");
                    logged = true;
                }
                else if (event.key.code == sf::Keyboard::R) {
                    habitLog.logHabit("Reading");
                    logged = true;
                }
                else if (event.key.code == sf::Keyboard::M) {
                    habitLog.logHabit("Meditation");
                    logged = true;
                }

                if (logged) {
                    audio.playSound();
                    gamified.update();
                    ruleEngine.evaluateAll();
                    suggestionText.setString("Tip: " + suggestions.getSuggestion());
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        animation.update(deltaTime);

        window.clear(sf::Color::White);
        window.draw(title);
        window.draw(instructions);
        window.draw(suggestionText);
        stats.draw(window, font, habitLog);
        charts.draw(window, habitLog, font);
        gamified.draw(window, font);
        animation.draw(window);
        window.display();
    }

    return 0;
}
