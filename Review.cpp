#include "Review.h"

// Definição do construtor
Review::Review(const std::string& username, const std::string& courtName, int rating, const std::string& comment)
    : username(username), courtName(courtName), rating(rating), comment(comment) {}
