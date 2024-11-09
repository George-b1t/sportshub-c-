#include "Notification.h"
#include <iostream>

void Notification::sendNotification(const std::string& username, const std::string& message) {
    // Simulação de envio de notificação
    std::cout << "Notificação para " << username << ": " << message << "\n";
}
