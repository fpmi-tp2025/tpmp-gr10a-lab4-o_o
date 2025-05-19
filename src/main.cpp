#include <iostream>
#include "ui.h"
#include "service.h"

int main() {
    std::string login = getLogin();
    std::string password = getPassword();

    // Аутентификация (упрощенная)
    std::string role = "commander"; // или "crew" в зависимости от пользователя

    while (true) {
        displayMenu(role);
        int choice;
        std::cin >> choice;

        if (choice == 0) break;
        else if (choice == 1) {
            std::string start_date, end_date;
            std::cout << "Введите период (YYYY-MM-DD): ";
            std::cin >> start_date >> end_date;
            calculateTotalEarnings(start_date, end_date);
        }
        else if (choice == 2 && role == "commander") {
            Flight flight;
            std::cout << "Введите данные рейса:\n";
            std::cin >> flight.date >> flight.helicopter_id >> flight.flight_code 
                    >> flight.cargo_weight >> flight.passengers >> flight.duration_hours 
                    >> flight.cost >> flight.is_special;
            addFlight(flight);
        }
        else if (choice == 3 && role == "commander") {
            int crew_id;
            std::string start_date, end_date;
            std::cout << "ID экипажа: ";
            std::cin >> crew_id;
            std::cout << "Период (YYYY-MM-DD): ";
            std::cin >> start_date >> end_date;
            double earnings = calculateEarnings(crew_id, start_date, end_date);
            std::cout << "Заработок: " << earnings << " руб.\n";
        }
        else if (choice == 2 && role == "crew") {
            int crew_id;
            std::string start_date, end_date;
            std::cout << "ID экипажа: ";
            std::cin >> crew_id;
            std::cout << "Период (YYYY-MM-DD): ";
            std::cin >> start_date >> end_date;
            std::vector<Flight> flights = getCrewFlights(crew_id, start_date, end_date);
            showCrewFlights(flights);
        }
    }

    return 0;
}