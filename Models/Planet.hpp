#ifndef PLANET_H
#define PLANET_H

#include "CelestialBody.hpp"
using namespace std;

class Planet : public CelestialBody {
private:
    bool hasAtmosphere;
    double atmosphericPressure; // in atm (Earth = 1.0)

public:
    Planet(string name, double distanceFromEarth, double gravity,
           string description, bool hasAtmosphere, double atmosphericPressure);

    // Getters
    bool getHasAtmosphere() const;
    double getAtmosphericPressure() const;

    // Setters
    void setHasAtmosphere(bool hasAtmosphere);
    void setAtmosphericPressure(double pressure);

    // Implementing pure virtual methods
    string getType() const override;
    double getHazardLevel() const override;

    // Overriding displayInfo
    void displayInfo() const override;
};

#endif