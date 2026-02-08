#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "Category.h"
#include "Time.h"

Category stringToCategory(const std::string& s);
Time parseTime(const std::string& s);

#endif
