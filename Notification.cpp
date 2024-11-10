#include "Notification.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

Notification::Notification(const std::string& message) : message(message) {
    // Obter data atual
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    std::stringstream ss;
    ss << std::put_time(now, "%d/%m/%Y %H:%M:%S");
    date = ss.str();
}

void Notification::sendNotification(const std::string& username, const std::string& message) {
    // Simulação de envio de notificação
    std::cout << "Notificação para " << username << ": " << message << "\n";
}
