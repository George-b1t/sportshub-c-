#include "Membership.h"

Membership::Membership(MembershipType type) : type(type) {}

double Membership::getDiscount() const {
    if (type == MembershipType::VIP) {
        return 0.1; // 10% de desconto para membros VIP
    }
    return 0.0;
}
