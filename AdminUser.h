#ifndef ADMINUSER_H
#define ADMINUSER_H

#include "User.h"

class AdminUser : public User {
public:
    AdminUser(std::string uname, std::string pwd);
    bool isAdmin() const override;
    void menu(BookingSystem& system) override;
};

#endif // ADMINUSER_H
