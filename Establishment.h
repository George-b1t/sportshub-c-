#ifndef ESTABLISHMENT_H
#define ESTABLISHMENT_H

#include <string>
#include <vector>
#include "Court.h"

class Establishment {
public:
    std::string name;
    std::vector<Court> courts;

    Establishment(std::string n);

    void addCourt(Court court);
};

#endif // ESTABLISHMENT_H
