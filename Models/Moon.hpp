#ifndef MOON_H
#define MOON_H
using namespace std;

#include "CelestialBody.hpp"

class Moon : public CelestialBody {
private:
    string parentPlanet;
    bool hasIce; // some moons like Europa have subsurface ice

public:
    Moon(string name, double distanceFromEarth, double gravity,
         string description, string parentPlanet, bool hasIce);

    // Getters
    string getParentPlanet() const;
    bool getHasIce() const;

    // Setters
    void setParentPlanet(string parentPlanet);
    void setHasIce(bool hasIce);

    // Implementing pure virtual methods
    string getType() const override;
    double getHazardLevel() const override;

    // Overriding displayInfo
    void displayInfo() const override;
};

#endif