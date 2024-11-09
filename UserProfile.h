#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <string>

class UserProfile {
public:
    std::string fullName;
    std::string email;
    std::string phoneNumber;

    UserProfile(const std::string& name = "", const std::string& email = "", const std::string& phone = "");
};

#endif // USERPROFILE_H
