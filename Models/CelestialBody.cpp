#include "CelestialBody.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

// Constructor
CelestialBody::CelestialBody(string name, double distanceFromEarth, double gravity, string description)
    : name(name), distanceFromEarth(distanceFromEarth), gravity(gravity), description(description) {}

// Getters
string CelestialBody::getName() const { return name; }
double CelestialBody::getDistanceFromEarth() const { return distanceFromEarth; }
double CelestialBody::getGravity() const { return gravity; }
string CelestialBody::getDescription() const { return description; }

// Setters
void CelestialBody::setName(string name) { this->name = name; }
void CelestialBody::setDistanceFromEarth(double distance) {
    if (distance < 0) {
        cerr << "Error: Distance cannot be negative.\n";
        return;
    }
    this->distanceFromEarth = distance;
}
void CelestialBody::setGravity(double gravity) {
    if (gravity < 0) {
        cerr << "Error: Gravity cannot be negative.\n";
        return;
    }
    this->gravity = gravity;
}
void CelestialBody::setDescription(string description) { this->description = description; }

// Display info (can be overridden by subclasses)
void CelestialBody::displayInfo() const {
    cout << "[ " << getType() << " ] " << name << "\n";
    cout << "  Distance from Earth : " << distanceFromEarth << " million km\n";
    cout << "  Gravity             : " << gravity << " m/s²\n";
    cout << "  Description         : " << description << "\n";
    cout << "  Hazard Level        : " << getHazardLevel() << "/10\n";
}