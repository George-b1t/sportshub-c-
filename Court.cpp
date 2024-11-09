#include "Court.h"

Court::Court(std::string n) : name(n) {}

void Court::addAvailableTime(const std::string& date, const std::string& time) {
    schedule[date].push_back(time);
}

const std::map<std::string, std::vector<std::string> >& Court::getSchedule() const {
    return schedule;
}
