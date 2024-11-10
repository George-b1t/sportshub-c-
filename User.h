#ifndef USER_H
#define USER_H

#include <vector>
#include <string>
#include "UserProfile.h"
#include "Membership.h"
#include "Payment.h"
#include "Notification.h"

class BookingSystem;

class User {
protected:
    std::string username;
    std::string password;
    UserProfile profile;
    Membership membership;
    std::vector<Payment> payments;
    std::vector<Notification> notifications;

public:
    User(std::string uname, std::string pwd, const UserProfile& profile, const Membership& membership);
    virtual ~User() {}

    std::string getUsername() const;
    std::string getPassword() const;
    UserProfile& getProfile();
    Membership& getMembership();

    virtual bool isAdmin() const = 0;
    virtual void menu(BookingSystem& system) = 0;

    void addPayment(const Payment& payment);
    const std::vector<Payment>& getPayments() const;

    void addNotification(const std::string& message);
    void viewNotifications();
};

#endif // USER_H
