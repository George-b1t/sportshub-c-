#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>

class Notification {
public:
    std::string message;
    std::string date;

    Notification(const std::string& message);

    static void sendNotification(const std::string& username, const std::string& message);
};

#endif // NOTIFICATION_H
