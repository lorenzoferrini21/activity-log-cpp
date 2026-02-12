#include "DailyLog.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Utils.h"
#include <chrono>
#include <ctime>
#include <iomanip>


// Costruttore
DailyLog::DailyLog(const std::string& d) : date(d) {}

// Aggiungi attività
void DailyLog::addActivity(const Activity& activity) {
    activities.push_back(activity);
    //push_back è un metodo di std::vector
    std::sort(activities.begin(),
              activities.end(),
              [](const Activity &a, const Activity &b) { return a.getStart() < b.getStart(); });
}


// Restituisci tutte le attività
const std::vector<Activity>& DailyLog::getActivities() const {
    return activities;
}

// Restituisci la data
std::string DailyLog::getDate() const {
    return date;
}

std::string DailyLog::toString() const {
    std::string result;
    for (const auto& a : activities) {
        result += a.toString() + "\n";
    }
    return result;
}

//ritorna true se ci sono sovrapposizioni di attività
bool DailyLog::hasOverlaps() const {
    for (size_t i = 1; i < activities.size(); ++i) {
        const Activity& prev = activities[i - 1];
        const Activity& curr = activities[i];

        if (curr.getStart().toMinutes() < prev.getEnd().toMinutes()) {
            return true;
        }
    }
    return false;
}

//serve per capire quanti buchi ci sono e quanto valgono in minuti
std::vector<int> DailyLog::getGapsInMinutes() const {
    std::vector<int> gaps;

    for (size_t i = 1; i < activities.size(); ++i) {
        int prevEnd = activities[i - 1].getEnd().toMinutes();
        int currStart = activities[i].getStart().toMinutes();

        if (currStart > prevEnd) {
            gaps.push_back(currStart - prevEnd);
        }
    }

    return gaps;
}
int DailyLog::totalGapTime() const {
    int total = 0;
    for (int g : getGapsInMinutes())
        total += g;
    return total;
}

std::vector<Activity> DailyLog::getActivitiesByCategory(Category category) const {
    std::vector<Activity> result;

    for (const auto& a : activities) {
        if (a.getCategory() == category) {
            result.push_back(a);
        }
    }
    return result;
}

int DailyLog::getTotalTimeByCategory(Category category) const {
    int total = 0;

    for (const auto& a : activities) {
        if (a.getCategory() == category) {
            total += a.durationMinutes();
        }
    }
    return total;
}

void DailyLog::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file) return;

    file << "DATE: " << date << "\n";
    file << "---\n";

    for (const auto& a : activities) {
        file << Activity::categoryToString(a.getCategory()) << "|"
             << a.getStart().toString() << "|"
             << a.getEnd().toString() << "|"
             << a.getDescription() << "\n";
    }
}

DailyLog DailyLog::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    std::getline(file, line); // DATE: yyyy-mm-dd
    std::string date = line.substr(6);

    DailyLog log(date);

    std::getline(file, line); // ---

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string catStr, startStr, endStr, desc;

        std::getline(iss, catStr, '|');
        std::getline(iss, startStr, '|');
        std::getline(iss, endStr, '|');
        std::getline(iss, desc);

        Activity a(
                desc,
                parseTime(startStr),
                parseTime(endStr),
                stringToCategory(catStr)
        );

        log.addActivity(a);
    }

    return log;
}

std::string DailyLog::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    std::tm local_tm;
    localtime_s(&local_tm, &now_time); // Windows

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d");

    return oss.str();
}
