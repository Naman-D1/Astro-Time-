#include "Planet.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

Planet::Planet(string name, double distanceFromEarth, double gravity,
               string description, bool hasAtmosphere, double atmosphericPressure)
    : CelestialBody(name, distanceFromEarth, gravity, description),
      hasAtmosphere(hasAtmosphere), atmosphericPressure(atmosphericPressure) {}

// Getters
bool Planet::getHasAtmosphere() const { return hasAtmosphere; }
double Planet::getAtmosphericPressure() const { return atmosphericPressure; }

// Setters
void Planet::setHasAtmosphere(bool hasAtmosphere) { this->hasAtmosphere = hasAtmosphere; }
void Planet::setAtmosphericPressure(double pressure) {
    if (pressure < 0) {
        cerr << "Error: Atmospheric pressure cannot be negative.\n";
        return;
    }
    this->atmosphericPressure = pressure;
}

// Hazard level based on gravity and atmosphere
double Planet::getHazardLevel() const {
    double hazard = 0.0;
    if (getGravity() > 15.0)       hazard += 4.0; // crushing gravity
    else if (getGravity() > 9.0)   hazard += 2.0;
    if (!hasAtmosphere)       hazard += 3.0; // no air = dangerous
    if (atmosphericPressure > 50.0) hazard += 3.0; // crushing atmosphere (e.g. Venus)
    return min(hazard, 10.0);
}

string Planet::getType() const { return "Planet"; }

void Planet::displayInfo() const {
    CelestialBody::displayInfo(); // call base display first
    cout << "  Atmosphere          : " << (hasAtmosphere ? "Yes" : "No") << "\n";
    cout << "  Atmospheric Pressure: " << atmosphericPressure << " atm\n";
}