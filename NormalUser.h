#ifndef NORMALUSER_H
#define NORMALUSER_H

#include "User.h"

class NormalUser : public User {
public:
    NormalUser(std::string uname, std::string pwd, const UserProfile& profile, const Membership& membership);
    bool isAdmin() const override;
    void menu(BookingSystem& system) override;
};

#endif // NORMALUSER_H
