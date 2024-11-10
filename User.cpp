#include "User.h"
#include <iostream>
#include "Payment.h"

User::User(std::string uname, std::string pwd, const UserProfile& profile, const Membership& membership)
    : username(uname), password(pwd), profile(profile), membership(membership) {}

UserProfile& User::getProfile() {
    return profile;
}

Membership& User::getMembership() {
    return membership;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

void User::addPayment(const Payment& payment) {
    payments.push_back(payment);
}

const std::vector<Payment>& User::getPayments() const {
    return payments;
}

void User::addNotification(const std::string& message) {
    notifications.emplace_back(message);
}

void User::viewNotifications() {
    if (notifications.empty()) {
        std::cout << "Você não tem notificações.\n";
        return;
    }

    std::cout << "\n=== Minhas Notificações ===\n";
    for (const auto& notification : notifications) {
        std::cout << notification.message << "\n";
        std::cout << "Data: " << notification.date << "\n";
        std::cout << "-----------------------------\n";
    }
    notifications.clear();
}
