#include "CelestialBody.hpp"
#include <iostream>
#include <algorithm>

// Constructor
CelestialBody::CelestialBody(std::string name, double distanceFromEarth, double gravity, std::string description)
    : name(name), distanceFromEarth(distanceFromEarth), gravity(gravity), description(description) {}

// Getters
std::string CelestialBody::getName() const { return name; }
double CelestialBody::getDistanceFromEarth() const { return distanceFromEarth; }
double CelestialBody::getGravity() const { return gravity; }
std::string CelestialBody::getDescription() const { return description; }

// Setters
void CelestialBody::setName(std::string name) { this->name = name; }
void CelestialBody::setDistanceFromEarth(double distance) {
    if (distance < 0) {
        std::cerr << "Error: Distance cannot be negative.\n";
        return;
    }
    this->distanceFromEarth = distance;
}
void CelestialBody::setGravity(double gravity) {
    if (gravity < 0) {
        std::cerr << "Error: Gravity cannot be negative.\n";
        return;
    }
    this->gravity = gravity;
}
void CelestialBody::setDescription(std::string description) { this->description = description; }

// Display info (can be overridden by subclasses)
void CelestialBody::displayInfo() const {
    std::cout << "[ " << getType() << " ] " << name << "\n";
    std::cout << "  Distance from Earth : " << distanceFromEarth << " million km\n";
    std::cout << "  Gravity             : " << gravity << " m/s²\n";
    std::cout << "  Description         : " << description << "\n";
    std::cout << "  Hazard Level        : " << getHazardLevel() << "/10\n";
}