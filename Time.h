#ifndef TIME_H
#define TIME_H

#include <string>

class Time {
public:
    Time(int hour, int minute);

    int getHour() const;
    int getMinute() const;

    bool operator<(const Time& other) const;
    bool operator<=(const Time& other) const;

    std::string toString() const;

    int toMinutes() const;


private:
    int hour;
    int minute;
};

#endif
