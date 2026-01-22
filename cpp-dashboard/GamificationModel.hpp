// GamificationModel.hpp
// Gamification system with goals, rewards, and leaderboard

#ifndef GAMIFICATION_MODEL_HPP
#define GAMIFICATION_MODEL_HPP

#include <string>
#include <vector>
#include <map>

struct Achievement {
    std::string name;
    std::string description;
    int requiredValue;
    bool unlocked;
    std::string icon;
    
    Achievement(const std::string& n, const std::string& desc, int req, const std::string& ic)
        : name(n), description(desc), requiredValue(req), unlocked(false), icon(ic) {}
};

struct LeaderboardEntry {
    std::string username;
    int totalXP;
    int level;
    
    LeaderboardEntry(const std::string& user, int xp, int lvl)
        : username(user), totalXP(xp), level(lvl) {}
};

class GamificationModel {
private:
    int currentXP;
    int currentLevel;
    int currentStreak;
    std::vector<Achievement> achievements;
    std::vector<LeaderboardEntry> leaderboard;
    
public:
    GamificationModel() : currentXP(450), currentLevel(5), currentStreak(12) {
        initializeAchievements();
        initializeLeaderboard();
        checkAchievements();
    }
    
    void initializeAchievements() {
        achievements.push_back(Achievement("First Steps", "Log your first habit", 1, "🌱"));
        achievements.push_back(Achievement("Week Warrior", "7-day streak", 7, "🔥"));
        achievements.push_back(Achievement("Hydration Hero", "Drink 8 glasses 5 days", 5, "💧"));
        achievements.push_back(Achievement("Bookworm", "Read 300 minutes", 300, "📚"));
        achievements.push_back(Achievement("Zen Master", "Meditate 10 times", 10, "🧘"));
        achievements.push_back(Achievement("Level 5", "Reach level 5", 5, "⭐"));
    }
    
    void initializeLeaderboard() {
        // Sample leaderboard data (simulating other clients)
        leaderboard.push_back(LeaderboardEntry("Alex_Fit", 1250, 12));
        leaderboard.push_back(LeaderboardEntry("Sarah_Goals", 980, 10));
        leaderboard.push_back(LeaderboardEntry("Mike_Strong", 850, 9));
        leaderboard.push_back(LeaderboardEntry("You", 450, 5));
        leaderboard.push_back(LeaderboardEntry("Emma_Health", 380, 4));
        leaderboard.push_back(LeaderboardEntry("John_Zen", 320, 3));
    }
    
    void checkAchievements() {
        // Check which achievements are unlocked
        if (currentXP > 0) achievements[0].unlocked = true;
        if (currentStreak >= 7) achievements[1].unlocked = true;
        if (currentLevel >= 5) achievements[5].unlocked = true;
    }
    
    int getCurrentXP() const { return currentXP; }
    int getCurrentLevel() const { return currentLevel; }
    int getCurrentStreak() const { return currentStreak; }
    
    int getXPForNextLevel() const {
        return currentLevel * 100;
    }
    
    int getXPProgress() const {
        return currentXP % 100;
    }
    
    const std::vector<Achievement>& getAchievements() const {
        return achievements;
    }
    
    const std::vector<LeaderboardEntry>& getLeaderboard() const {
        return leaderboard;
    }
    
    std::string getNextGoal() const {
        for (const auto& ach : achievements) {
            if (!ach.unlocked) {
                return ach.name + ": " + ach.description;
            }
        }
        return "All goals completed!";
    }
};

#endif
