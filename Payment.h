#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include "Booking.h"

class Payment {
public:
    static bool processPayment(Booking& booking, double amount);
};

#endif // PAYMENT_H
