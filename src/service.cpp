#include "service.h"
#include <sstream>

Database db("helicopter.db");

void addFlight(const Flight& flight) {
    std::stringstream ss;
    ss << "INSERT INTO flights (date, helicopter_id, flight_code, cargo_weight, passengers, duration_hours, cost, is_special) "
       << "VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
    
    sqlite3_stmt* stmt = db.prepareQuery(ss.str());
    if (!stmt) return;

    db.bindText(stmt, 1, flight.date);
    db.bindInt(stmt, 2, flight.helicopter_id);
    db.bindText(stmt, 3, flight.flight_code);
    db.bindDouble(stmt, 4, flight.cargo_weight);
    db.bindInt(stmt, 5, flight.passengers);
    db.bindDouble(stmt, 6, flight.duration_hours);
    db.bindDouble(stmt, 7, flight.cost);
    db.bindInt(stmt, 8, flight.is_special ? 1 : 0);

    if (db.step(stmt)) {
        std::cout << "Рейс добавлен\n";
    }
    db.finalize(stmt);

    // Обновление ресурса вертолета
    std::stringstream update;
    update << "UPDATE helicopters SET flight_hours_remaining = flight_hours_remaining - " << flight.duration_hours
           << " WHERE id = " << flight.helicopter_id;
    db.execute(update.str());
}

double calculateEarnings(int crew_id, const std::string& start_date, const std::string& end_date) {
    std::stringstream ss;
    ss << "SELECT SUM(f.cost * CASE WHEN f.is_special THEN 0.1 ELSE 0.05 END) "
       << "FROM flights f JOIN crew_members c ON f.helicopter_id = c.helicopter_id "
       << "WHERE c.id = " << crew_id << " AND f.date BETWEEN '" << start_date << "' AND '" << end_date << "'";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db.getHandle(), ss.str().c_str(), -1, &stmt, nullptr);
    sqlite3_step(stmt);
    double result = sqlite3_column_double(stmt, 0);
    sqlite3_finalize(stmt);
    return result;
}

std::vector<CrewMember> getCrewMembersByHelicopter(int helicopter_id) {
    std::vector<CrewMember> result;
    std::stringstream ss;
    ss << "SELECT id, name FROM crew_members WHERE helicopter_id = " << helicopter_id;
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db.getHandle(), ss.str().c_str(), -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        CrewMember cm;
        cm.id = sqlite3_column_int(stmt, 0);
        cm.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        cm.helicopter_id = helicopter_id;
        result.push_back(cm);
    }
    sqlite3_finalize(stmt);
    return result;
}

std::vector<Flight> getCrewFlights(int crew_id, const std::string& start_date, const std::string& end_date) {
    std::vector<Flight> result;
    std::stringstream ss;
    ss << "SELECT f.date, f.helicopter_id, f.flight_code, f.cargo_weight, f.passengers, f.duration_hours, f.cost, f.is_special "
       << "FROM flights f JOIN crew_members c ON f.helicopter_id = c.helicopter_id "
       << "WHERE c.id = " << crew_id << " AND f.date BETWEEN '" << start_date << "' AND '" << end_date << "'";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db.getHandle(), ss.str().c_str(), -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Flight f;
        f.date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        f.helicopter_id = sqlite3_column_int(stmt, 1);
        f.flight_code = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        f.cargo_weight = sqlite3_column_double(stmt, 3);
        f.passengers = sqlite3_column_int(stmt, 4);
        f.duration_hours = sqlite3_column_double(stmt, 5);
        f.cost = sqlite3_column_double(stmt, 6);
        f.is_special = sqlite3_column_int(stmt, 7) == 1;
        result.push_back(f);
    }
    sqlite3_finalize(stmt);
    return result;
}

void updateHelicopterHours(int helicopter_id, double hours) {
    std::stringstream ss;
    ss << "UPDATE helicopters SET flight_hours_remaining = flight_hours_remaining - " << hours
       << " WHERE id = " << helicopter_id;
    db.execute(ss.str());
}

void calculateTotalEarnings(const std::string& start_date, const std::string& end_date) {
    std::stringstream ss;
    ss << "SELECT c.id, SUM(f.cost * CASE WHEN f.is_special THEN 0.1 ELSE 0.05 END) AS total "
       << "FROM crew_members c JOIN flights f ON c.helicopter_id = f.helicopter_id "
       << "WHERE f.date BETWEEN '" << start_date << "' AND '" << end_date << "' "
       << "GROUP BY c.id";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db.getHandle(), ss.str().c_str(), -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int crew_id = sqlite3_column_int(stmt, 0);
        double total = sqlite3_column_double(stmt, 1);
        std::cout << "Экипаж ID " << crew_id << ": " << total << " руб.\n";
    }
    sqlite3_finalize(stmt);
}

void calculateCrewMaxFlights() {
    std::stringstream ss;
    ss << "SELECT c.id, COUNT(*) AS count "
       << "FROM crew_members c JOIN flights f ON c.helicopter_id = f.helicopter_id "
       << "GROUP BY c.id ORDER BY count DESC LIMIT 1";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db.getHandle(), ss.str().c_str(), -1, &stmt, nullptr);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int crew_id = sqlite3_column_int(stmt, 0);
        int count = sqlite3_column_int(stmt, 1);
        std::cout << "Экипаж ID " << crew_id << " выполнил " << count << " рейсов\n";
    }
    sqlite3_finalize(stmt);
}

void calculateMaxCargoFlights() {
    std::stringstream ss;
    ss << "SELECT helicopter_id, SUM(cargo_weight) AS total "
       << "FROM flights GROUP BY helicopter_id ORDER BY total DESC LIMIT 1";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db.getHandle(), ss.str().c_str(), -1, &stmt, nullptr);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int helicopter_id = sqlite3_column_int(stmt, 0);
        double total = sqlite3_column_double(stmt, 1);
        std::cout << "Вертолет ID " << helicopter_id << " перевез " << total << " кг груза\n";
    }
    sqlite3_finalize(stmt);
}