// HabitModel.hpp
// Backend Data Model for Habit Logging

#ifndef HABIT_MODEL_HPP
#define HABIT_MODEL_HPP

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iostream>

enum class HabitType {
    BINARY,      // Yes/No (checkbox)
    COUNT,       // Numeric count
    DURATION     // Time duration in minutes
};

struct Habit {
    std::string name;
    HabitType type;
    int value;           // For COUNT: the count, for DURATION: minutes, for BINARY: 0 or 1
    std::string timestamp;
    
    Habit(const std::string& n, HabitType t, int v)
        : name(n), type(t), value(v) {
        time_t now = time(nullptr);
        timestamp = std::string(ctime(&now));
        timestamp.pop_back(); // Remove newline
    }
};

class HabitModel {
private:
    std::vector<Habit> todayHabits;
    std::map<std::string, HabitType> habitTemplates;

public:
    HabitModel() {
        // Pre-defined habit templates
        habitTemplates["Exercise"] = HabitType::BINARY;
        habitTemplates["Reading"] = HabitType::DURATION;
        habitTemplates["Water"] = HabitType::COUNT;
        habitTemplates["Meditation"] = HabitType::DURATION;
        habitTemplates["Push-ups"] = HabitType::COUNT;
        habitTemplates["Study"] = HabitType::DURATION;
        
        loadFromFile();
    }

    void addHabit(const std::string& name, HabitType type, int value) {
        todayHabits.emplace_back(name, type, value);
        saveToFile();
        
        // Console feedback
        std::cout << "\n[LOGGED] " << name << " - ";
        switch(type) {
            case HabitType::BINARY:
                std::cout << (value ? "Completed ✓" : "Not done");
                break;
            case HabitType::COUNT:
                std::cout << value << " times";
                break;
            case HabitType::DURATION:
                std::cout << value << " minutes";
                break;
        }
        std::cout << std::endl;
    }

    const std::vector<Habit>& getTodayHabits() const {
        return todayHabits;
    }

    HabitType getHabitType(const std::string& name) const {
        auto it = habitTemplates.find(name);
        if (it != habitTemplates.end()) {
            return it->second;
        }
        return HabitType::BINARY; // Default
    }

    void saveToFile() {
        std::ofstream file("habits_data.txt");
        for (const auto& habit : todayHabits) {
            file << habit.name << "|"
                 << static_cast<int>(habit.type) << "|"
                 << habit.value << "|"
                 << habit.timestamp << "\n";
        }
    }

    void loadFromFile() {
        std::ifstream file("habits_data.txt");
        std::string line;
        
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name, timestamp;
            int typeInt, value;
            
            std::getline(ss, name, '|');
            ss >> typeInt;
            ss.ignore();
            ss >> value;
            ss.ignore();
            std::getline(ss, timestamp);
            
            Habit habit(name, static_cast<HabitType>(typeInt), value);
            habit.timestamp = timestamp;
            todayHabits.push_back(habit);
        }
    }

    int getTotalCount() const {
        return todayHabits.size();
    }

    int getCompletedCount() const {
        int count = 0;
        for (const auto& habit : todayHabits) {
            if (habit.type == HabitType::BINARY && habit.value == 1) {
                count++;
            } else if (habit.type == HabitType::COUNT && habit.value > 0) {
                count++;
            } else if (habit.type == HabitType::DURATION && habit.value > 0) {
                count++;
            }
        }
        return count;
    }
};

#endif
