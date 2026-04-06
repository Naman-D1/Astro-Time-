#include "Mission.hpp"
#include <iostream>
using namespace std;

Mission::Mission(string missionName,
                 shared_ptr<Spacecraft> spacecraft,
                 shared_ptr<CelestialBody> destination)
    : missionName(missionName), spacecraft(spacecraft),
      destination(destination), status("Planned") {}

// Getters
string Mission::getMissionName() const { return missionName; }
string Mission::getStatus() const { return status; }
shared_ptr<Spacecraft>    Mission::getSpacecraft() const { return spacecraft; }
shared_ptr<CelestialBody> Mission::getDestination() const { return destination; }

// Setters
void Mission::setMissionName(string name) { this->missionName = name; }
void Mission::setStatus(string status) {
    if (status != "Planned" && status != "Ongoing" &&
        status != "Completed" && status != "Aborted") {
        cerr << "Error: Invalid status.\n";
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
    cout << "\n====================================\n";
    cout << "  Mission  : " << missionName << "\n";
    cout << "  Type     : " << getMissionType() << "\n";
    cout << "  Status   : " << status << "\n";
    cout << "  Ship     : " << spacecraft->getName()
              << " (" << spacecraft->getType() << ")\n";
    cout << "  Target   : " << destination->getName()
              << " (" << destination->getType() << ")\n";
    cout << "------------------------------------\n";
    cout << "  Travel Time  : " << calculateTravelTime()  << " days\n";
    cout << "  Fuel Needed  : " << calculateFuelNeeded()  << " tonnes\n";
    cout << "  Risk Score   : " << calculateRiskScore()   << "/10\n";
    cout << "  Min Crew     : " << getMinCrewRequired()   << "\n";
    cout << "====================================\n";
}