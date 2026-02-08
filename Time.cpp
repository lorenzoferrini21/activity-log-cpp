#include "Time.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>

Time::Time(int h, int m) : hour(h), minute(m) {
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        throw std::invalid_argument("Orario non valido");
    }
}

// Getter
int Time::getHour() const {
    return hour;
}

int Time::getMinute() const {
    return minute;
}

// Operatore <
bool Time::operator<(const Time& other) const {
    if (hour != other.hour) return hour < other.hour;
    return minute < other.minute;
}

// Operatore <=
bool Time::operator<=(const Time& other) const {
    return (*this < other) || (hour == other.hour && minute == other.minute);
}

// Converti in stringa HH:MM
std::string Time::toString() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour
        << ":"
        << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}

int Time::toMinutes() const {
    return hour * 60 + minute;
}

