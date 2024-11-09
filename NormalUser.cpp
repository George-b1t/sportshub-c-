#include "NormalUser.h"
#include "BookingSystem.h"
#include <iostream>

using namespace std;

NormalUser::NormalUser(std::string uname, std::string pwd, const UserProfile& profile, const Membership& membership)
    : User(uname, pwd, profile, membership) {}

bool NormalUser::isAdmin() const {
    return false;
}

void NormalUser::menu(BookingSystem& system) {
    int choice;
    do {
        cout << "\n=== Menu Usuário ===\n";
        cout << "1. Ver Estabelecimentos\n";
        cout << "2. Agendar Quadra\n";
        cout << "3. Cancelar Agendamento\n";
        cout << "4. Visualizar Meus Agendamentos\n";
        cout << "5. Avaliar Quadra\n";
        cout << "6. Visualizar Avaliações\n";
        cout << "7. Logout\n";
        cout << "Escolha uma opção: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system.viewEstablishments();
            break;
        case 2:
            system.bookCourt(*this);
            break;
        case 3:
            system.cancelBooking(*this);
            break;
        case 4:
            system.viewUserBookings(*this);
            break;
        case 5:
            system.addReview(*this);
            break;
        case 6:
            system.viewReviews();
            break;
        case 7:
            cout << "Logout bem-sucedido!\n";
            break;
        default:
            cout << "Opção inválida!\n";
        }
    } while (choice != 7);
}
