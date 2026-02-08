#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>
#include "Time.h"
#include <stdexcept>
#include "Category.h"


class Activity {
public:
    // Costruttore
    Activity(const std::string& description, const Time& start, const Time& end, Category category);

    // Getter
    std::string getDescription() const;
    Time getStart() const;
    Time getEnd() const;
    Category getCategory() const;


    int durationMinutes() const;
    std::string toString() const;

    static std::string categoryToString(Category c);

private:
    std::string description;
    Time start;
    Time end;
    Category category;
};

#endif
