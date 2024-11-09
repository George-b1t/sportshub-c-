#ifndef COURT_H
#define COURT_H

#include <string>
#include <vector>
#include <map>

class Court {
public:
    std::string name;
    // Map de datas para os horários disponíveis nesse dia
    std::map<std::string, std::vector<std::string> > schedule;

    Court(std::string n);

    void addAvailableTime(const std::string& date, const std::string& time);
    const std::map<std::string, std::vector<std::string> >& getSchedule() const;
};

#endif // COURT_H
