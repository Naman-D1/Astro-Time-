#include "Moon.hpp"
#include <iostream>
#include <algorithm>

Moon::Moon(std::string name, double distanceFromEarth, double gravity,
           std::string description, std::string parentPlanet, bool hasIce)
    : CelestialBody(name, distanceFromEarth, gravity, description),
      parentPlanet(parentPlanet), hasIce(hasIce) {}

// Getters
std::string Moon::getParentPlanet() const { return parentPlanet; }
bool Moon::getHasIce() const { return hasIce; }

// Setters
void Moon::setParentPlanet(std::string planet) { this->parentPlanet = planet; }
void Moon::setHasIce(bool hasIce) { this->hasIce = hasIce; }

// Moons are generally hazardous due to low gravity and no atmosphere
double Moon::getHazardLevel() const {
    double hazard = 3.0; // base hazard for any moon
    if (getGravity() < 1.0)  hazard += 2.0; // very low gravity
    if (getHasIce())         hazard += 1.0; // icy terrain = tricky landing
    return std::min(hazard, 10.0);
}

std::string Moon::getType() const { return "Moon"; }

void Moon::displayInfo() const {
    CelestialBody::displayInfo();
    std::cout << "  Parent Planet       : " << parentPlanet << "\n";
    std::cout << "  Has Ice             : " << (getHasIce() ? "Yes" : "No") << "\n";
}