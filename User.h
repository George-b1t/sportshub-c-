#ifndef USER_H
#define USER_H

#include <string>
#include "UserProfile.h"
#include "Membership.h"

class BookingSystem;

class User {
protected:
    std::string username;
    std::string password;
    UserProfile profile;
    Membership membership;

public:
    User(std::string uname, std::string pwd, const UserProfile& profile, const Membership& membership);
    virtual ~User() {}

    std::string getUsername() const;
    std::string getPassword() const;
    UserProfile& getProfile();
    Membership& getMembership();

    virtual bool isAdmin() const = 0;
    virtual void menu(BookingSystem& system) = 0;
};

#endif // USER_H
