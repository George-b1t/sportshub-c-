#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
public:
    std::string bookingID;
    std::string establishmentName;
    std::string courtName;
    std::string date;
    std::string time;
    std::string username;
    double amountPaid;
    bool isPaid;

    // Construtor padrão
    Booking();

    // Construtor com parâmetros
    Booking(const std::string& id, const std::string& estName, const std::string& courtName,
            const std::string& date, const std::string& time, const std::string& username);

    void markAsPaid(double amount);
};

#endif // BOOKING_H
