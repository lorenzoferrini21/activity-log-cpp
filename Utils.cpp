#include "Utils.h"
#include <sstream>

Category stringToCategory(const std::string& s) {
    if (s == "Study") return Category::Study;
    if (s == "Work") return Category::Work;
    if (s == "Sport") return Category::Sport;
    if (s == "Leisure") return Category::Leisure;
    return Category::Other;
}

Time parseTime(const std::string& s) {
    int h, m;
    char colon;
    std::istringstream iss(s);
    iss >> h >> colon >> m;
    return Time(h, m);
}
