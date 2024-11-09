#ifndef REVIEW_H
#define REVIEW_H

#include <string>

class Review {
public:
    std::string username;
    std::string courtName;
    int rating; // 1 a 5
    std::string comment;

    Review(const std::string& username, const std::string& courtName, int rating, const std::string& comment);
};

#endif // REVIEW_H
