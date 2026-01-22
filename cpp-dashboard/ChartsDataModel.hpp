// ChartsDataModel.hpp
// Sample data model for 6 days of habit tracking

#ifndef CHARTS_DATA_MODEL_HPP
#define CHARTS_DATA_MODEL_HPP

#include <string>
#include <vector>
#include <map>

struct DailyData {
    std::string date;
    int exerciseCount;
    int waterGlasses;
    int readingMinutes;
    int meditationMinutes;
    int studyMinutes;
    
    DailyData(const std::string& d, int ex, int wa, int re, int me, int st)
        : date(d), exerciseCount(ex), waterGlasses(wa), readingMinutes(re),
          meditationMinutes(me), studyMinutes(st) {}
};

class ChartsDataModel {
private:
    std::vector<DailyData> weekData;
    
public:
    ChartsDataModel() {
        // Sample data for 6 days
        weekData.push_back(DailyData("Mon", 1, 8, 45, 20, 120));
        weekData.push_back(DailyData("Tue", 1, 6, 30, 15, 90));
        weekData.push_back(DailyData("Wed", 0, 7, 60, 25, 150));
        weekData.push_back(DailyData("Thu", 1, 9, 40, 30, 100));
        weekData.push_back(DailyData("Fri", 1, 8, 50, 20, 110));
        weekData.push_back(DailyData("Sat", 0, 5, 70, 35, 80));
    }
    
    const std::vector<DailyData>& getWeekData() const {
        return weekData;
    }
    
    int getTotalExerciseDays() const {
        int count = 0;
        for (const auto& day : weekData) {
            count += day.exerciseCount;
        }
        return count;
    }
    
    int getAverageWater() const {
        int total = 0;
        for (const auto& day : weekData) {
            total += day.waterGlasses;
        }
        return weekData.empty() ? 0 : total / weekData.size();
    }
    
    int getTotalReadingMinutes() const {
        int total = 0;
        for (const auto& day : weekData) {
            total += day.readingMinutes;
        }
        return total;
    }
    
    int getMaxValue(const std::string& habitType) const {
        int maxVal = 0;
        for (const auto& day : weekData) {
            int val = 0;
            if (habitType == "exercise") val = day.exerciseCount;
            else if (habitType == "water") val = day.waterGlasses;
            else if (habitType == "reading") val = day.readingMinutes;
            else if (habitType == "meditation") val = day.meditationMinutes;
            else if (habitType == "study") val = day.studyMinutes;
            
            if (val > maxVal) maxVal = val;
        }
        return maxVal;
    }
};

#endif
