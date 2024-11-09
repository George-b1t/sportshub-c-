#include "Booking.h"

// Implementação do construtor padrão
Booking::Booking()
    : bookingID(""), establishmentName(""), courtName(""), date(""), time(""), username(""), amountPaid(0.0), isPaid(false) {}

// Implementação do construtor com parâmetros
Booking::Booking(const std::string& id, const std::string& estName, const std::string& courtName,
                 const std::string& date, const std::string& time, const std::string& username)
    : bookingID(id), establishmentName(estName), courtName(courtName),
      date(date), time(time), username(username), amountPaid(0.0), isPaid(false) {}

void Booking::markAsPaid(double amount) {
    amountPaid = amount;
    isPaid = true;
}
