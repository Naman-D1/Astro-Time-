#include "Mission.hpp"
#include <iostream>

Mission::Mission(std::string missionName,
                 std::shared_ptr<Spacecraft> spacecraft,
                 std::shared_ptr<CelestialBody> destination)
    : missionName(missionName), spacecraft(spacecraft),
      destination(destination), status("Planned") {}

// Getters
std::string Mission::getMissionName() const { return missionName; }
std::string Mission::getStatus() const { return status; }
std::shared_ptr<Spacecraft>    Mission::getSpacecraft() const { return spacecraft; }
std::shared_ptr<CelestialBody> Mission::getDestination() const { return destination; }

// Setters
void Mission::setMissionName(std::string name) { this->missionName = name; }
void Mission::setStatus(std::string status) {
    if (status != "Planned" && status != "Ongoing" &&
        status != "Completed" && status != "Aborted") {
        std::cerr << "Error: Invalid status.\n";
        return;
    }
    this->status = status;
}

// Travel time = distance / speed (converted to days)
double Mission::calculateTravelTime() const {
    double distanceKm  = destination->getDistanceFromEarth() * 1e6; // convert million km to km
    double speedKmPerS = spacecraft->getSpeed();
    double seconds     = distanceKm / speedKmPerS;
    double days        = seconds / 86400.0; // 86400 seconds in a day
    return days;
}

// Delegate fuel calculation to spacecraft
double Mission::calculateFuelNeeded() const {
    double distanceKm = destination->getDistanceFromEarth() * 1e6;
    return spacecraft->calculateFuelNeeded(distanceKm);
}

void Mission::displaySummary() const {
    std::cout << "\n====================================\n";
    std::cout << "  Mission  : " << missionName << "\n";
    std::cout << "  Type     : " << getMissionType() << "\n";
    std::cout << "  Status   : " << status << "\n";
    std::cout << "  Ship     : " << spacecraft->getName()
              << " (" << spacecraft->getType() << ")\n";
    std::cout << "  Target   : " << destination->getName()
              << " (" << destination->getType() << ")\n";
    std::cout << "------------------------------------\n";
    std::cout << "  Travel Time  : " << calculateTravelTime()  << " days\n";
    std::cout << "  Fuel Needed  : " << calculateFuelNeeded()  << " tonnes\n";
    std::cout << "  Risk Score   : " << calculateRiskScore()   << "/10\n";
    std::cout << "  Min Crew     : " << getMinCrewRequired()   << "\n";
    std::cout << "====================================\n";
}