#include "Payment.h"
#include <iostream>

bool Payment::processPayment(Booking& booking, double amount) {
    // Simulação de processamento de pagamento
    std::cout << "Processando pagamento de R$" << amount << " para a reserva " << booking.bookingID << "...\n";
    // Aqui poderia ser implementada a integração com um sistema de pagamento real
    booking.markAsPaid(amount);
    std::cout << "Pagamento realizado com sucesso!\n";
    return true;
}
