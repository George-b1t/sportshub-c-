#include "User.h"

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
