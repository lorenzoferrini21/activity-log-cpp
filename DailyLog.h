#ifndef DAILYLOG_H
#define DAILYLOG_H

#include <string>
#include <vector>
#include "Activity.h"

class DailyLog {
public:

    explicit DailyLog(const std::string& date);
    //per evitare conversioni impilicite non volute

    void addActivity(const Activity& activity);

    const std::vector<Activity>& getActivities() const;

    std::string getDate() const;

    static std::string getCurrentDate();

    std::string toString() const;

    bool hasOverlaps() const;

    std::vector<int> getGapsInMinutes() const;

    int totalGapTime() const;

    std::vector<Activity> getActivitiesByCategory(Category category) const;

    int getTotalTimeByCategory(Category category) const;

    void saveToFile(const std::string& filename) const;
    static DailyLog loadFromFile(const std::string& filename);

private:
    std::string date;
    std::vector<Activity> activities;
};

#endif
