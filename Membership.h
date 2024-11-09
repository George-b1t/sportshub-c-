#ifndef MEMBERSHIP_H
#define MEMBERSHIP_H

enum class MembershipType {
    NORMAL,
    VIP
};

class Membership {
public:
    MembershipType type;

    Membership(MembershipType type = MembershipType::NORMAL);

    double getDiscount() const;
};

#endif // MEMBERSHIP_H
