#ifndef BOOKINGSYSTEM_H
#define BOOKINGSYSTEM_H

#include <vector>
#include <unordered_map>
#include <string>
#include <list>
#include "User.h"
#include "Establishment.h"
#include "Booking.h"
#include "Payment.h"
#include "Notification.h"
#include "Review.h"
#include "Membership.h"

class BookingSystem {
private:
    std::vector<User*> users;
    std::vector<Establishment> establishments;
    // Key: Booking ID
    std::unordered_map<std::string, Booking> bookings;
    std::list<Review> reviews;

public:
    BookingSystem();
    ~BookingSystem();

    void run();

    void login();
    void registerUser();

    void addEstablishment();
    void addCourt();

    void viewEstablishments();
    void bookCourt(User& user);

    void viewBookings();
    void viewUserBookings(User& user);

    void cancelBooking(User& user);
    void addReview(User& user);
    void viewReviews();
    void generateReport();

    User* authenticate(std::string uname, std::string pwd);
};

#endif // BOOKINGSYSTEM_H
