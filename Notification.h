#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>

class Notification {
public:
    static void sendNotification(const std::string& username, const std::string& message);
};

#endif // NOTIFICATION_H
