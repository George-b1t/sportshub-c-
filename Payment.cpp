#include "Payment.h"
#include <iostream>
#include <limits>

Payment::Payment(const std::string& paymentID, const std::string& bookingID, const std::string& username,
                 double amount, PaymentMethod method, const std::string& date)
    : paymentID(paymentID), bookingID(bookingID), username(username), amount(amount), method(method), date(date) {}

PaymentMethod Payment::choosePaymentMethod() {
    int choice;
    std::cout << "Escolha o método de pagamento:\n";
    std::cout << "1. Cartão de Crédito\n";
    std::cout << "2. Cartão de Débito\n";
    std::cout << "3. PIX\n";
    std::cout << "4. Boleto\n";
    std::cout << "Opção: ";
    while (!(std::cin >> choice) || choice < 1 || choice > 4) {
        std::cout << "Escolha inválida. Por favor, digite um número entre 1 e 4: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore();

    switch (choice) {
    case 1:
        return PaymentMethod::CREDIT_CARD;
    case 2:
        return PaymentMethod::DEBIT_CARD;
    case 3:
        return PaymentMethod::PIX;
    case 4:
        return PaymentMethod::BOLETO;
    default:
        return PaymentMethod::CREDIT_CARD; // Padrão
    }
}

bool Payment::processPayment(Booking& booking, double amount) {
    // Simulação de processamento de pagamento
    std::cout << "Processando pagamento de R$" << amount << " para a reserva " << booking.bookingID << "...\n";
    // Aqui poderia ser implementada a integração com um sistema de pagamento real
    booking.markAsPaid(amount);
    std::cout << "Pagamento realizado com sucesso!\n";
    return true;
}
