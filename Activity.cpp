#include "Activity.h"
#include "Category.h"

// Costruttore
Activity::Activity(const std::string& desc, const Time& s, const Time& e,  Category category)
        : description(desc), start(s), end(e),  category (category)
{
    if (end < start) {
        throw std::invalid_argument("L'orario di fine non può essere prima dell'orario di inizio");
    }
}

// Getter
std::string Activity::getDescription() const {
    return description;
}

Time Activity::getStart() const {
    return start;
}

Time Activity::getEnd() const {
    return end;
}

Category Activity::getCategory() const {
    return category;
}


int Activity::durationMinutes() const {
    int startMinutes = start.getHour() * 60 + start.getMinute();
    int endMinutes   = end.getHour() * 60 + end.getMinute();
    return endMinutes - startMinutes;
}

std::string Activity::toString() const {
    return "[" + categoryToString(category) + "] " +
           description + " (" +
           start.toString() + " - " +
           end.toString() + ") " + "tot:" +
           std::to_string(durationMinutes()) + " min";
}
//to_string funzione della libreria standard C++: converte numero in stringa

std::string Activity::categoryToString(Category c) {
    switch (c) {
        case Category::Study:   return "Study";
        case Category::Work:    return "Work";
        case Category::Sport:   return "Sport";
        case Category::Leisure: return "Leisure";
        default:                return "Other";
    }
}

