#include "ui.h"
#include <iostream>
#include <string>
#include <vector>

std::string getLogin() {
    std::string login;
    std::cout << "Логин: ";
    std::cin >> login;
    return login;
}

std::string getPassword() {
    std::string pass;
    std::cout << "Пароль: ";
    std::cin >> pass;
    return pass;
}

void displayMenu(const std::string& role) {
    std::cout << "=== Меню ===\n";
    std::cout << "1. Просмотр статистики вертолетов\n";
    if (role == "commander") {
        std::cout << "2. Добавить рейс\n";
        std::cout << "3. Рассчитать заработок экипажа\n";
    } else {
        std::cout << "2. Просмотр моих рейсов\n";
    }
    std::cout << "0. Выход\n";
}

void showFlightStats(const std::string& start_date, const std::string& end_date) {
    std::cout << "Статистика за период " << start_date << " - " << end_date << ":\n";
    // Реализация вывода данных
}

void showCrewEarnings(int crew_id, const std::string& start_date, const std::string& end_date) {
    std::cout << "Заработок экипажа " << crew_id << " за " << start_date << "-" << end_date << ":\n";
    // Реализация вывода
}

void showCrewFlights(const std::vector<Flight>& flights) {
    std::cout << "Рейсы экипажа:\n";
    for (const auto& f : flights) {
        std::cout << f.date << " | " << f.flight_code << " | " << f.cost << " руб.\n";
    }
}

void showCrewInfo(const std::vector<CrewMember>& crew) {
    std::cout << "Члены экипажа:\n";
    for (const auto& c : crew) {
        std::cout << c.name << " (ID: " << c.id << ")\n";
    }
}