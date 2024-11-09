#include "Establishment.h"

Establishment::Establishment(std::string n) : name(n) {}

void Establishment::addCourt(Court court) {
    courts.push_back(court);
}
