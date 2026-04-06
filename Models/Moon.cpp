#include "Moon.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

Moon::Moon(string name, double distanceFromEarth, double gravity,
           string description, string parentPlanet, bool hasIce)
    : CelestialBody(name, distanceFromEarth, gravity, description),
      parentPlanet(parentPlanet), hasIce(hasIce) {}

// Getters
string Moon::getParentPlanet() const { return parentPlanet; }
bool Moon::getHasIce() const { return hasIce; }

// Setters
void Moon::setParentPlanet(string planet) { this->parentPlanet = planet; }
void Moon::setHasIce(bool hasIce) { this->hasIce = hasIce; }

// Moons are generally hazardous due to low gravity and no atmosphere
double Moon::getHazardLevel() const {
    double hazard = 3.0; // base hazard for any moon
    if (getGravity() < 1.0)  hazard += 2.0; // very low gravity
    if (getHasIce())         hazard += 1.0; // icy terrain = tricky landing
    return min(hazard, 10.0);
}

string Moon::getType() const { return "Moon"; }

void Moon::displayInfo() const {
    CelestialBody::displayInfo();
    cout << "  Parent Planet       : " << parentPlanet << "\n";
    cout << "  Has Ice             : " << (getHasIce() ? "Yes" : "No") << "\n";
}