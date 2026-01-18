// main_console.cpp
// Personal Productivity Dashboard - Console Version (No SFML)
// Features: Habit Tracking, Streaks, Trends, Analytics, Gamification

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>

// -------------------------------
// Utility Functions
// -------------------------------
std::string getToday() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", now);
    return std::string(buf);
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
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
            std::cout << "\n[!] Already logged " << habitName << " today!" << std::endl;
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

        std::cout << "\n[+] " << habitName << " logged!" << std::endl;
        std::cout << "    Streak: " << h.currentStreak << " days | Total: " << h.totalCount << std::endl;
        
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
        if (counts.size() < 2) return "New";

        int sumFirstHalf = 0, sumSecondHalf = 0;
        int mid = counts.size() / 2;
        for (int i = 0; i < mid; i++) sumFirstHalf += counts[i];
        for (size_t i = mid; i < counts.size(); i++) sumSecondHalf += counts[i];

        if (sumSecondHalf > sumFirstHalf) return "↑ Trending Up";
        else if (sumSecondHalf < sumFirstHalf) return "↓ Trending Down";
        else return "→ Stable";
    }

    void saveToFile() {
        std::ofstream file("habit_log.txt");
        for (auto& h : habits) {
            file << h.first << "|" << h.second.totalCount << "|" 
                 << h.second.currentStreak << "|" << h.second.lastDate << "\n";
        }
    }

    void loadFromFile() {
        std::ifstream file("habit_log.txt");
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name, date;
            int count, streak;
            
            std::getline(ss, name, '|');
            ss >> count;
            ss.ignore();
            ss >> streak;
            ss.ignore();
            std::getline(ss, date);
            
            habits[name].totalCount = count;
            habits[name].currentStreak = streak;
            habits[name].lastDate = date;
        }
    }

    void displayStats() const {
        if (habits.empty()) {
            std::cout << "\n  No habits tracked yet. Start logging today!\n" << std::endl;
            return;
        }

        std::cout << "\n╔════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                      HABIT STATISTICS                          ║" << std::endl;
        std::cout << "╠════════════════════════════════════════════════════════════════╣" << std::endl;
        
        for (const auto& pair : habits) {
            std::cout << "║ " << std::left << std::setw(15) << pair.first 
                     << " │ Streak: " << std::setw(3) << pair.second.currentStreak
                     << " │ Total: " << std::setw(4) << pair.second.totalCount
                     << " │ " << std::setw(15) << getTrend(pair.first) << " ║" << std::endl;
        }
        
        std::cout << "╚════════════════════════════════════════════════════════════════╝" << std::endl;
    }

    void displayChart() const {
        if (habits.empty()) return;

        std::cout << "\n  PROGRESS CHART:\n" << std::endl;
        
        int maxCount = 0;
        for (const auto& pair : habits) {
            if (pair.second.totalCount > maxCount) maxCount = pair.second.totalCount;
        }

        for (const auto& pair : habits) {
            std::cout << "  " << std::left << std::setw(12) << pair.first << " │";
            int barLength = (pair.second.totalCount * 40) / std::max(1, maxCount);
            for (int i = 0; i < barLength; i++) std::cout << "█";
            std::cout << " " << pair.second.totalCount << std::endl;
        }
        std::cout << std::endl;
    }
};

// -------------------------------
// Gamified Environment
// -------------------------------
class GamifiedEnvironment {
private:
    int xp = 0;
    int level = 1;
    std::string filename = "gamification.txt";

public:
    void update() {
        xp += 10;
        if (xp >= level * 50) {
            level++;
            std::cout << "\n★★★ LEVEL UP! You are now level " << level << " ★★★\n" << std::endl;
        }
        saveToFile();
    }

    void display() const {
        int xpNeeded = level * 50;
        int xpProgress = xp % 50;
        float progress = (float)xpProgress / 50.0f * 100.0f;
        
        std::cout << "\n  ⚡ Level " << level << " │ XP: " << xp 
                  << " │ Progress to next level: " << (int)progress << "%" << std::endl;
        
        std::cout << "  [";
        int bars = (int)(progress / 5);
        for (int i = 0; i < 20; i++) {
            if (i < bars) std::cout << "=";
            else std::cout << " ";
        }
        std::cout << "] " << xpProgress << "/" << 50 << " XP\n" << std::endl;
    }

    void saveToFile() {
        std::ofstream file(filename);
        file << xp << " " << level;
    }

    void loadFromFile() {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> xp >> level;
        }
    }

    int getXP() const { return xp; }
    int getLevel() const { return level; }
};

// -------------------------------
// Suggestion Engine
// -------------------------------
class SuggestionEngine {
private:
    std::vector<std::string> tips = {
        "Stay consistent - small daily actions create big results!",
        "Small steps lead to big wins. Keep going!",
        "Celebrate progress, not perfection.",
        "Track habits daily for best results.",
        "Build momentum with streaks!",
        "Every day is a new opportunity to improve.",
        "Consistency beats intensity. Show up every day!",
        "Your future self will thank you for today's efforts.",
        "One habit at a time - master the basics first.",
        "Progress is progress, no matter how small."
    };
public:
    std::string getSuggestion() {
        return tips[rand() % tips.size()];
    }
};

// -------------------------------
// Main Menu System
// -------------------------------
void displayHeader() {
    std::cout << "\n╔════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         PERSONAL PRODUCTIVITY DASHBOARD - CONSOLE              ║" << std::endl;
    std::cout << "║                    " << getToday() << "                          ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════╝" << std::endl;
}

void displayMenu() {
    std::cout << "\n  MENU:" << std::endl;
    std::cout << "  [1] Log Exercise" << std::endl;
    std::cout << "  [2] Log Work" << std::endl;
    std::cout << "  [3] Log Reading" << std::endl;
    std::cout << "  [4] Log Meditation" << std::endl;
    std::cout << "  [5] Log Custom Habit" << std::endl;
    std::cout << "  [6] View Statistics" << std::endl;
    std::cout << "  [7] View Progress Chart" << std::endl;
    std::cout << "  [8] Get Motivation Tip" << std::endl;
    std::cout << "  [0] Exit" << std::endl;
    std::cout << "\n  Enter choice: ";
}

// -------------------------------
// Application Entry Point
// -------------------------------
int main() {
    HabitLog habitLog;
    GamifiedEnvironment gamified;
    SuggestionEngine suggestions;

    habitLog.loadFromFile();
    gamified.loadFromFile();

    srand(time(nullptr));

    bool running = true;
    
    while (running) {
        clearScreen();
        displayHeader();
        gamified.display();
        habitLog.displayStats();
        displayMenu();

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                habitLog.logHabit("Exercise");
                gamified.update();
                break;
            case 2:
                habitLog.logHabit("Work");
                gamified.update();
                break;
            case 3:
                habitLog.logHabit("Reading");
                gamified.update();
                break;
            case 4:
                habitLog.logHabit("Meditation");
                gamified.update();
                break;
            case 5: {
                std::cout << "\n  Enter custom habit name: ";
                std::string customHabit;
                std::getline(std::cin, customHabit);
                if (!customHabit.empty()) {
                    habitLog.logHabit(customHabit);
                    gamified.update();
                }
                break;
            }
            case 6:
                clearScreen();
                displayHeader();
                habitLog.displayStats();
                std::cout << "\n  Press Enter to continue...";
                std::cin.get();
                break;
            case 7:
                clearScreen();
                displayHeader();
                habitLog.displayChart();
                std::cout << "\n  Press Enter to continue...";
                std::cin.get();
                break;
            case 8:
                std::cout << "\n  💡 TIP: " << suggestions.getSuggestion() << std::endl;
                std::cout << "\n  Press Enter to continue...";
                std::cin.get();
                break;
            case 0:
                running = false;
                std::cout << "\n  Thanks for using Productivity Dashboard! Keep building those habits! 🚀\n" << std::endl;
                break;
            default:
                std::cout << "\n  Invalid choice. Press Enter to continue...";
                std::cin.get();
                break;
        }
    }

    return 0;
}
