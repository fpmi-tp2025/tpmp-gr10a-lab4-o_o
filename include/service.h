#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <vector>
#include "ui.h"

extern Database db;

void addFlight(const Flight& flight);
double calculateEarnings(int crew_id, const std::string& start_date, const std::string& end_date);
std::vector<CrewMember> getCrewMembersByHelicopter(int helicopter_id);
std::vector<Flight> getCrewFlights(int crew_id, const std::string& start_date, const std::string& end_date);
void updateHelicopterHours(int helicopter_id, double hours);
void calculateTotalEarnings(const std::string& start_date, const std::string& end_date);
void calculateCrewMaxFlights();
void calculateMaxCargoFlights();

#endif // SERVICE_H