#include "SpaceStation.hpp"
#include <iostream>
#include <algorithm>

SpaceStation::SpaceStation(std::string name, double distanceFromEarth, double gravity,
                           std::string description, int crewCapacity,
                           bool isOperational, std::string orbitingBody)
    : CelestialBody(name, distanceFromEarth, gravity, description),
      crewCapacity(crewCapacity), isOperational(isOperational), orbitingBody(orbitingBody) {}

// Getters
int SpaceStation::getCrewCapacity() const { return crewCapacity; }
bool SpaceStation::getIsOperational() const { return isOperational; }
std::string SpaceStation::getOrbitingBody() const { return orbitingBody; }

// Setters
void SpaceStation::setCrewCapacity(int capacity) {
    if (capacity < 0) {
        std::cerr << "Error: Crew capacity cannot be negative.\n";
        return;
    }
    this->crewCapacity = capacity;
}
void SpaceStation::setIsOperational(bool operational) { this->isOperational = operational; }
void SpaceStation::setOrbitingBody(std::string body) { this->orbitingBody = body; }

// Non-operational stations are extremely dangerous
double SpaceStation::getHazardLevel() const {
    double hazard = 1.0; // base hazard
    if (!isOperational) hazard += 6.0; // derelict station = very dangerous
    if (crewCapacity < 2) hazard += 2.0; // minimal support infrastructure
    return std::min(hazard, 10.0);
}

std::string SpaceStation::getType() const { return "Space Station"; }

void SpaceStation::displayInfo() const {
    CelestialBody::displayInfo();
    std::cout << "  Orbiting            : " << orbitingBody << "\n";
    std::cout << "  Crew Capacity       : " << crewCapacity << "\n";
    std::cout << "  Operational         : " << (isOperational ? "Yes" : "No") << "\n";
}