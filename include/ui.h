#ifndef UI_H
#define UI_H

#include <string>
#include <vector>

struct CrewMember {
    int id;
    std::string name;
    int helicopter_id;
};

struct Flight {
    std::string date;
    int helicopter_id;
    std::string flight_code;
    double cargo_weight;
    int passengers;
    double duration_hours;
    double cost;
    bool is_special;
};

std::string getLogin();
std::string getPassword();
void displayMenu(const std::string& role);
void showFlightStats(const std::string& start_date, const std::string& end_date);
void showCrewEarnings(int crew_id, const std::string& start_date, const std::string& end_date);
void showCrewFlights(const std::vector<Flight>& flights);
void showCrewInfo(const std::vector<CrewMember>& crew);

#endif // UI_H