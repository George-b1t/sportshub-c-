#include "AdminUser.h"
#include "BookingSystem.h"
#include <iostream>

using namespace std;

AdminUser::AdminUser(std::string uname, std::string pwd)
    : User(uname, pwd, UserProfile(), Membership(MembershipType::NORMAL)) {}

bool AdminUser::isAdmin() const {
    return true;
}

void AdminUser::menu(BookingSystem& system) {
    int choice;
    do {
        cout << "\n=== Menu Admin ===\n";
        cout << "1. Cadastrar Estabelecimento\n";
        cout << "2. Cadastrar Quadra\n";
        cout << "3. Visualizar Agendamentos\n";
        cout << "4. Cancelar Agendamento\n";
        cout << "5. Gerar Relatório\n";
        cout << "6. Visualizar Avaliações\n";
        cout << "7. Logout\n";
        cout << "Escolha uma opção: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system.addEstablishment();
            break;
        case 2:
            system.addCourt();
            break;
        case 3:
            system.viewBookings();
            break;
        case 4:
            system.cancelBooking(*this);
            break;
        case 5:
            system.generateReport();
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
