#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include "Booking.h"

enum class PaymentMethod {
    CREDIT_CARD,
    DEBIT_CARD,
    PIX,
    BOLETO
};

class Payment {
public:
    std::string paymentID;
    std::string bookingID;
    std::string username;
    double amount;
    PaymentMethod method;
    std::string date;

    Payment() : paymentID(""), bookingID(""), username(""), amount(0.0), method(PaymentMethod::CREDIT_CARD), date("") {}

    Payment(const std::string& paymentID, const std::string& bookingID, const std::string& username,
            double amount, PaymentMethod method, const std::string& date);

    static PaymentMethod choosePaymentMethod();

    static bool processPayment(Booking& booking, double amount);
};

#endif // PAYMENT_H
