#include "BookingSystem.h"
#include "AdminUser.h"
#include "NormalUser.h"
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

BookingSystem::BookingSystem() {
    // Usuário admin padrão
    users.push_back(new AdminUser("admin", "admin123"));
}

BookingSystem::~BookingSystem() {
    for (auto user : users) {
        delete user;
    }
}

void BookingSystem::run() {
    int choice;
    do {
        cout << "\n=== Sistema de Agendamento de Quadras ===\n";
        cout << "1. Login\n";
        cout << "2. Registrar\n";
        cout << "3. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> choice;

        switch (choice) {
        case 1:
            login();
            break;
        case 2:
            registerUser();
            break;
        case 3:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opção inválida!\n";
        }
    } while (choice != 3);
}

void BookingSystem::login() {
    string uname, pwd;
    cout << "Nome de usuário: ";
    cin >> uname;
    // verifica se o nome de usuário n esta vazio
    if (uname == "") {
        cout << "Nome de usuário inválido!\n";
        return;
    }
    cout << "Senha: ";
    cin >> pwd;
    // verifica se a senha n esta vazia
    if (pwd == "") {
        cout << "Senha inválida!\n";
        return;
    }
    User* user = authenticate(uname, pwd);
    if (user) {
        cout << "Login bem-sucedido!\n";
        user->menu(*this);
    } else {
        cout << "Credenciais inválidas!\n";
    }
}

void BookingSystem::registerUser() {
    string uname, pwd;
    cout << "Escolha um nome de usuário: ";
    cin >> uname;
    // verifica se o nome de usuário ja foi cadastrado
    for (auto user : users) {
        if (user->getUsername() == uname) {
            cout << "Nome de usuário já cadastrado!\n";
            return;
        }
    }

    cout << "Escolha uma senha: ";
    cin >> pwd;

    // Coleta de informações do perfil
    string fullName, email, phone;
    cin.ignore();
    cout << "Nome completo: ";
    getline(cin, fullName);
    cout << "Email: ";
    getline(cin, email);
    cout << "Telefone: ";
    getline(cin, phone);

    UserProfile profile(fullName, email, phone);

    // Escolha do tipo de membro
    int memberChoice;
    cout << "Tipo de Membro:\n";
    cout << "1. Normal\n";
    cout << "2. VIP\n";
    cout << "Escolha uma opção: ";
    cin >> memberChoice;
    MembershipType memberType = (memberChoice == 2) ? MembershipType::VIP : MembershipType::NORMAL;
    Membership membership(memberType);

    users.push_back(new NormalUser(uname, pwd, profile, membership));
    cout << "Usuário registrado com sucesso!\n";
}

User* BookingSystem::authenticate(std::string uname, std::string pwd) {
    for (auto user : users) {
        if (user->getUsername() == uname && user->getPassword() == pwd) {
            return user;
        }
    }
    return nullptr;
}

void BookingSystem::addEstablishment() {
    string name;
    cout << "Nome do Estabelecimento: ";
    cin.ignore();
    getline(cin, name);
    establishments.push_back(Establishment(name));
    cout << "Estabelecimento cadastrado com sucesso!\n";
}

void BookingSystem::addCourt() {
    if (establishments.empty()) {
        cout << "Nenhum estabelecimento cadastrado!\n";
        return;
    }

    // Exibir lista de estabelecimentos e solicitar uma escolha válida
    cout << "Selecione o Estabelecimento:\n";
    for (size_t i = 0; i < establishments.size(); ++i) {
        cout << i + 1 << ". " << establishments[i].name << "\n";
    }

    int choice;
    cout << "Digite o número do estabelecimento: ";
    while (!(cin >> choice) || choice < 1 || choice > (int)establishments.size()) {
        cout << "Escolha inválida. Por favor, digite um número entre 1 e " << establishments.size() << ": ";
        cin.clear();                // Limpa a flag de erro do cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada
    }
    cin.ignore(); // Limpa o buffer após a leitura de `choice`

    string courtName;
    cout << "Nome da Quadra: ";
    getline(cin, courtName); // Lê o nome da quadra corretamente

    Court court(courtName);

    int numDates;
    cout << "Quantos dias disponíveis para esta quadra? ";
    while (!(cin >> numDates) || numDates <= 0) {
        cout << "Por favor, insira um número válido de dias: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); // Limpa o buffer após a leitura de `numDates`

    for (int i = 0; i < numDates; ++i) {
        string date;
        cout << "Data " << i + 1 << " (DD/MM/AAAA): ";
        getline(cin, date);

        int numTimes;
        cout << "Quantos horários disponíveis para esta data? ";
        while (!(cin >> numTimes) || numTimes <= 0) {
            cout << "Por favor, insira um número válido de horários: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(); // Limpa o buffer após a leitura de `numTimes`

        for (int j = 0; j < numTimes; ++j) {
            string time;
            cout << "Horário " << j + 1 << " (HH:MM): ";
            getline(cin, time);
            court.addAvailableTime(date, time);
        }
    }

    establishments[choice - 1].addCourt(court);
    cout << "Quadra cadastrada com sucesso!\n";
}

void BookingSystem::viewEstablishments() {
    if (establishments.empty()) {
        cout << "Nenhum estabelecimento cadastrado!\n";
        return;
    }
    for (auto& est : establishments) {
        cout << "\nEstabelecimento: " << est.name << "\n";
        for (auto& court : est.courts) {
            cout << "  Quadra: " << court.name << "\n";
            cout << "    Horários disponíveis:\n";
            for (const auto& dateSchedule : court.getSchedule()) {
                string date = dateSchedule.first;
                cout << "      Data: " << date << "\n";
                for (const auto& time : dateSchedule.second) {
                    string bookingID = est.name + "|" + court.name + "|" + date + "|" + time;
                    if (bookings.find(bookingID) == bookings.end()) {
                        cout << "        " << time << "\n";
                    }
                }
            }
        }
    }
}

void BookingSystem::viewUserPayments(User& user) {
    const auto& userPayments = user.getPayments();
    if (userPayments.empty()) {
        std::cout << "Você não tem pagamentos registrados.\n";
        return;
    }

    std::cout << "\n=== Meus Pagamentos ===\n";
    for (const auto& payment : userPayments) {
        std::cout << "ID do Pagamento: " << payment.paymentID << "\n";
        std::cout << "ID da Reserva: " << payment.bookingID << "\n";
        std::cout << "Valor: R$" << payment.amount << "\n";
        std::cout << "Método: ";
        switch (static_cast<int>(payment.method)) {
            case static_cast<int>(PaymentMethod::CREDIT_CARD):
                std::cout << "Cartão de Crédito\n";
                break;
            case static_cast<int>(PaymentMethod::DEBIT_CARD):
                std::cout << "Cartão de Débito\n";
                break;
            case static_cast<int>(PaymentMethod::PIX):
                std::cout << "PIX\n";
                break;
            case static_cast<int>(PaymentMethod::BOLETO):
                std::cout << "Boleto\n";
                break;
            default:
                std::cout << "Método de pagamento desconhecido\n";
        }
        std::cout << "Data: " << payment.date << "\n";
        std::cout << "-----------------------------\n";
    }
}

void BookingSystem::bookCourt(User& user) {
    if (establishments.empty()) {
        cout << "Nenhum estabelecimento cadastrado!\n";
        return;
    }

    // Seleção do Estabelecimento
    cout << "Selecione o Estabelecimento:\n";
    for (size_t i = 0; i < establishments.size(); ++i) {
        cout << i + 1 << ". " << establishments[i].name << "\n";
    }

    int estChoice;
    cout << "Digite o número do estabelecimento: ";
    while (!(cin >> estChoice) || estChoice < 1 || estChoice > (int)establishments.size()) {
        cout << "Escolha inválida. Por favor, digite um número entre 1 e " << establishments.size() << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); // Limpa o buffer após a leitura de `estChoice`

    Establishment& est = establishments[estChoice - 1];

    if (est.courts.empty()) {
        cout << "Nenhuma quadra cadastrada neste estabelecimento!\n";
        return;
    }

    // Seleção da Quadra
    cout << "Selecione a Quadra:\n";
    for (size_t i = 0; i < est.courts.size(); ++i) {
        cout << i + 1 << ". " << est.courts[i].name << "\n";
    }

    int courtChoice;
    cout << "Digite o número da quadra: ";
    while (!(cin >> courtChoice) || courtChoice < 1 || courtChoice > (int)est.courts.size()) {
        cout << "Escolha inválida. Por favor, digite um número entre 1 e " << est.courts.size() << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    Court& court = est.courts[courtChoice - 1];

    // Seleção da Data
    cout << "Selecione a Data (Disponíveis):\n";
    vector<string> availableDates;
    for (const auto& dateSchedule : court.getSchedule()) {
        availableDates.push_back(dateSchedule.first);
        cout << availableDates.size() << ". " << dateSchedule.first << "\n";
    }

    if (availableDates.empty()) {
        cout << "Nenhuma data disponível para esta quadra!\n";
        return;
    }

    int dateChoice;
    cout << "Digite o número da data: ";
    while (!(cin >> dateChoice) || dateChoice < 1 || dateChoice > (int)availableDates.size()) {
        cout << "Escolha inválida. Por favor, digite um número entre 1 e " << availableDates.size() << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    string selectedDate = availableDates[dateChoice - 1];

    // Seleção do Horário
    vector<string> availableTimes;
    for (const auto& time : court.getSchedule().at(selectedDate)) {
        string bookingID = est.name + "|" + court.name + "|" + selectedDate + "|" + time;
        if (bookings.find(bookingID) == bookings.end()) {  // Verifica se o horário não está reservado
            availableTimes.push_back(time);
            cout << availableTimes.size() << ". " << time << "\n";
        }
    }

    if (availableTimes.empty()) {
        cout << "Nenhum horário disponível nesta data para esta quadra!\n";
        return;
    }

    int timeChoice;
    cout << "Digite o número do horário: ";
    while (!(cin >> timeChoice) || timeChoice < 1 || timeChoice > (int)availableTimes.size()) {
        cout << "Escolha inválida. Por favor, digite um número entre 1 e " << availableTimes.size() << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    string selectedTime = availableTimes[timeChoice - 1];

    // Confirmação do Agendamento
    string bookingID = est.name + "|" + court.name + "|" + selectedDate + "|" + selectedTime;
    Booking booking(bookingID, est.name, court.name, selectedDate, selectedTime, user.getUsername());

    double price = 100.0; // Preço base
    double discount = user.getMembership().getDiscount();
    double finalPrice = price * (1 - discount);

    std::cout << "O valor a ser pago é R$" << finalPrice << "\n";

    // Escolha do método de pagamento
    PaymentMethod method = Payment::choosePaymentMethod();

    // Geração de ID único para o pagamento
    std::string paymentID = "PAY" + std::to_string(payments.size() + 1);

    // Obter data atual
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    std::stringstream ss;
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", now);
    ss << buffer;
    std::string currentDateTime = ss.str();

    // Criar objeto Payment
    Payment payment(paymentID, bookingID, user.getUsername(), finalPrice, method, currentDateTime);

    // Simulação de processamento de pagamento
    if (Payment::processPayment(booking, finalPrice)) {
        bookings[bookingID] = booking;
        payments[paymentID] = payment;
        user.addPayment(payment);

        std::string notificationMsg = "Reserva confirmada para " + selectedDate + " às " + selectedTime;
        user.addNotification(notificationMsg);
        std::cout << "Quadra agendada com sucesso!\n";
    } else {
        std::cout << "Falha no processamento do pagamento.\n";
    }
}

void BookingSystem::viewBookings() {
    if (bookings.empty()) {
        cout << "Nenhum agendamento encontrado!\n";
        return;
    }
    cout << "\n=== Agendamentos ===\n";
    for (auto& bookingPair : bookings) {
        const Booking& booking = bookingPair.second;
        cout << "ID: " << booking.bookingID << "\n";
        cout << "Usuário: " << booking.username << "\n";
        cout << "Estabelecimento: " << booking.establishmentName << "\n";
        cout << "Quadra: " << booking.courtName << "\n";
        cout << "Data: " << booking.date << "\n";
        cout << "Hora: " << booking.time << "\n";
        cout << "-----------------------------\n";
    }
}

void BookingSystem::viewUserBookings(User& user) {
    bool hasBookings = false;
    cout << "\n=== Meus Agendamentos ===\n";
    for (auto& bookingPair : bookings) {
        if (bookingPair.second.username == user.getUsername()) {
            const Booking& booking = bookingPair.second;
            cout << "ID: " << booking.bookingID << "\n";
            cout << "Estabelecimento: " << booking.establishmentName << "\n";
            cout << "Quadra: " << booking.courtName << "\n";
            cout << "Data: " << booking.date << "\n";
            cout << "Hora: " << booking.time << "\n";
            cout << "-----------------------------\n";
            hasBookings = true;
        }
    }
    if (!hasBookings) {
        cout << "Você não tem nenhum agendamento.\n";
    }
}

void BookingSystem::cancelBooking(User& user) {
    string bookingID;
    cout << "Informe o ID da reserva que deseja cancelar: ";
    cin >> bookingID;

    auto it = bookings.find(bookingID);
    if (it != bookings.end()) {
        if (it->second.username == user.getUsername() || user.isAdmin()) {
            bookings.erase(it);
            Notification::sendNotification(user.getUsername(), "Sua reserva " + bookingID + " foi cancelada.");
            cout << "Reserva cancelada com sucesso.\n";
        } else {
            cout << "Você não tem permissão para cancelar esta reserva.\n";
        }
    } else {
        cout << "Reserva não encontrada.\n";
    }
}

void BookingSystem::addReview(User& user) {
    if (establishments.empty()) {
        cout << "Nenhum estabelecimento cadastrado!\n";
        return;
    }

    // Seleção do Estabelecimento
    cout << "Selecione o Estabelecimento para Avaliação:\n";
    for (size_t i = 0; i < establishments.size(); ++i) {
        cout << i + 1 << ". " << establishments[i].name << "\n";
    }

    int estChoice;
    cout << "Digite o número do estabelecimento: ";
    while (!(cin >> estChoice) || estChoice < 1 || estChoice > (int)establishments.size()) {
        cout << "Escolha inválida. Por favor, digite um número entre 1 e " << establishments.size() << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); // Limpa o buffer após a leitura de `estChoice`

    Establishment& est = establishments[estChoice - 1];

    if (est.courts.empty()) {
        cout << "Nenhuma quadra cadastrada neste estabelecimento!\n";
        return;
    }

    // Seleção da Quadra
    cout << "Selecione a Quadra para Avaliação:\n";
    for (size_t i = 0; i < est.courts.size(); ++i) {
        cout << i + 1 << ". " << est.courts[i].name << "\n";
    }

    int courtChoice;
    cout << "Digite o número da quadra: ";
    while (!(cin >> courtChoice) || courtChoice < 1 || courtChoice > (int)est.courts.size()) {
        cout << "Escolha inválida. Por favor, digite um número entre 1 e " << est.courts.size() << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    Court& court = est.courts[courtChoice - 1];

    // Entrada da Nota
    int rating;
    cout << "Informe a nota (1 a 5): ";
    while (!(cin >> rating) || rating < 1 || rating > 5) {
        cout << "Nota inválida. Por favor, insira um valor entre 1 e 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); // Limpa o buffer após a leitura de `rating`

    // Entrada do Comentário
    string comment;
    cout << "Deixe seu comentário: ";
    cin.ignore();
    getline(cin, comment);

    // Adicionando a Avaliação
    reviews.push_back(Review(user.getUsername(), court.name, rating, comment));
    cout << "Avaliação adicionada com sucesso!\n";
}


void BookingSystem::viewReviews() {
    if (reviews.empty()) {
        cout << "Nenhuma avaliação disponível.\n";
        return;
    }
    for (const auto& review : reviews) {
        cout << "Quadra: " << review.courtName << "\n";
        cout << "Usuário: " << review.username << "\n";
        cout << "Nota: " << review.rating << "\n";
        cout << "Comentário: " << review.comment << "\n";
        cout << "-----------------------------\n";
    }
}

void BookingSystem::generateReport() {
    // Exemplo simples de relatório
    cout << "\n=== Relatório de Agendamentos ===\n";
    for (const auto& bookingPair : bookings) {
        const Booking& booking = bookingPair.second;
        cout << "ID: " << booking.bookingID << "\n";
        cout << "Usuário: " << booking.username << "\n";
        cout << "Estabelecimento: " << booking.establishmentName << "\n";
        cout << "Quadra: " << booking.courtName << "\n";
        cout << "Data: " << booking.date << "\n";
        cout << "Hora: " << booking.time << "\n";
        cout << "-----------------------------\n";
    }
}
