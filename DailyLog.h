#ifndef DAILYLOG_H
#define DAILYLOG_H

#include <string>
#include <vector>
#include "Activity.h"

class DailyLog {
public:
    // Costruttore
    explicit DailyLog(const std::string& date);

    // Aggiunge un'attività
    void addActivity(const Activity& activity);

    // Restituisce tutte le attività
    const std::vector<Activity>& getActivities() const;

    // Restituisce la data
    std::string getDate() const;

    std::string toString() const;

    bool hasOverlaps() const;

    std::vector<int> getGapsInMinutes() const;
    int totalGapTime() const;

    std::vector<Activity> getActivitiesByCategory(Category category) const;
    int getTotalTimeByCategory(Category category) const;

    void saveToFile(const std::string& filename) const;
    static DailyLog loadFromFile(const std::string& filename);

private:
    std::string date;                 // Data della giornata, formato "YYYY-MM-DD"
    std::vector<Activity> activities; // Elenco delle attività
};

#endif
